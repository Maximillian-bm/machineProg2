package machineprog2.kortspilgui.controller;

import com.fasterxml.jackson.core.type.TypeReference;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.geometry.Bounds;
import javafx.geometry.Point2D;
import javafx.scene.effect.InnerShadow;
import javafx.scene.input.KeyCode;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;
import com.fasterxml.jackson.databind.ObjectMapper;
import machineprog2.kortspilgui.model.*;

import java.io.InputStream;
import java.net.URL;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

public class Controller implements Initializable {
    private final List<Observer> observers;

    @FXML
    private Pane mainMenu;
    @FXML
    private HBox columnsHBox;
    @FXML
    private AnchorPane rootPane;

    private static Point2D dragOffset;
    private static VBox dragVBox;
    private Card draggedCard;
    private static InnerShadow innerShadowEffect;

    private final List<CardColumn> cardColumns = new ArrayList<>();

    private static final Random random = new Random();

    public Controller() {
        this.observers = new ArrayList<>();
        innerShadowEffect = getInnerShadowEffect();
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        mainMenu.setVisible(true);
        AtomicInteger columnNumber = new AtomicInteger(0);
        columnsHBox.getChildren().stream()
                .filter(node -> node instanceof VBox)
                .map(node -> (VBox) node)
                .forEach(node -> cardColumns.addLast(new CardColumn(node, columnNumber.getAndIncrement())));

        dragVBox = new VBox();
        rootPane.getChildren().add(dragVBox);
        initializeRootPaneEventListeners();
    }

    public void keyPressed(KeyCode keyCode) {
        if (keyCode == KeyCode.ESCAPE) {
            setMainMenuVisible(!mainMenu.isVisible()); // toggling
        }
    }

    private void setMainMenuVisible(boolean isVisible) {
        mainMenu.setVisible(isVisible);
    }

    @FXML
    private void event_newGame() {
        System.out.println("Start new game");

        try {
            InputStream inputStream = getClass().getResourceAsStream("/machineprog2/kortspilgui/card_columns_structure.json");
            List<CardColumnsWrapper> cardColumnsData = new ObjectMapper().readValue(inputStream, new TypeReference<>() {
            });
            assert inputStream != null;
            inputStream.close();

            for (int i = 0; i < cardColumns.size(); i++) {
                for (int j = 0; j < cardColumnsData.get(i).face_down; j++) {
                    Card newCard = new Card(randomEnum(Suit.class), random.nextInt(1, 14), false, this);
                    cardColumns.get(i).addCard(newCard);
                }
                for (int j = 0; j < cardColumnsData.get(i).face_up; j++) {
                    Card newCard = new Card(randomEnum(Suit.class), random.nextInt(1, 14), true, this);
                    cardColumns.get(i).addCard(newCard);
                }
            }

            setMainMenuVisible(false);
        } catch (Exception e) {
            System.out.println("Error in importing .json. Output: " + e.getMessage());
        }
    }

    @FXML
    private void event_loadGame() {
        System.out.println("Load a game");
    }

    @FXML
    private void event_save() {
        System.out.println("Save game");
        // If save-file, override it.
        // No save-file? Call event_saveAs();
    }

    @FXML
    private void event_saveAs() {
        System.out.println("Start new game");
    }

    @FXML
    private void event_quitAndSave() {
        System.out.println("Start new game");
    }

    private static Card topMostHoveredCard = null;

    public void initializeCardEventListeners(Card card) {
        card.getStackPane().setOnMouseEntered(event -> {
            topMostHoveredCard = card;
            if (card.getVisible()) {
                for (Card cardInStack : card.getColumn().getCardsOnTop(card)) {
                    cardInStack.getStackPane().setEffect(innerShadowEffect);
                }
            }
        });
        card.getStackPane().setOnMouseExited(event -> {
            if (topMostHoveredCard == card) {
                topMostHoveredCard = null;
                for (Card cardInStack : card.getColumn().getCardsOnTop(card)) {
                    cardInStack.getStackPane().setEffect(null);
                }
            }
        });
    }

    private void initializeRootPaneEventListeners() { // Checking for all cards individually in scene. If not done like this, .setOnMouseDragged on cards would only get the top node at the mouse position
        rootPane.setOnMousePressed(event -> {
            if (topMostHoveredCard == null) return;

            if (topMostHoveredCard.getVisible()) {
                draggedCard = topMostHoveredCard;
            } else return;

            //System.out.println("Picked up : " + draggedCard);
            StackPane cardStackPane = draggedCard.getStackPane();
            CardColumn column = draggedCard.getColumn();

            // Get the offset from the card to the mouse
            Bounds localBounds = cardStackPane.getBoundsInLocal();
            Bounds sceneBounds = cardStackPane.localToScene(localBounds);
            dragOffset = new Point2D(event.getSceneX() - sceneBounds.getMinX(), event.getSceneY() - sceneBounds.getMinY());

            // Stack cards
            List<Card> cardStack = column.getCardsOnTop(draggedCard); // Includes this card as index 0
            for (Card cardInStack : cardStack) {
                StackPane stackPane = cardInStack.getStackPane();
                column.getVBox().getChildren().remove(stackPane);
                dragVBox.getChildren().add(stackPane);
            }
            updateDragVBoxPosition(event); // Call update position, since .setOnMouseDragged only gets called when the mouse is moved
        });

        rootPane.setOnMouseDragged(event -> {
            if (draggedCard == null) return; // When dragging
            // Update dragged cards position
            updateDragVBoxPosition(event);
            // Clear effect
            for (Card cardInScene : getCards()) {
                cardInScene.getStackPane().setEffect(null);
                if (draggedCard != null || cardInScene != topMostHoveredCard) { // Clear if dragging. If not, don't clear the topMostHoveredCard.

                }
            }
            // Highlight the top card of column below mouse
            Card topCardOfHoveredColumn = null;
            for (Card cardAtMouse : getCardsAtMouse(event)) {
                if (!cardAtMouse.getColumn().getCards().contains(draggedCard)) {
                    topCardOfHoveredColumn = cardAtMouse.getColumn().getTopCard();
                    break;
                }
            }
            // Return if we didn't find a column different from the dragging stack
            if (topCardOfHoveredColumn == null) return;
            // If it's a legal move, highlight the card
            if (true) { // TODO: Replace "true" with a check if dragged card is allowed on top of topCardOfHoveredColumn
                topCardOfHoveredColumn.getStackPane().setEffect(innerShadowEffect);
            }
        });

        rootPane.setOnMouseReleased(event -> {
            // Return if we're not holding a card
            if (draggedCard == null) return;
            // Get top card
            Card topCardOfHoveredColumn = null;
            for (Card cardAtMouse : getCardsAtMouse(event)) {
                if (!cardAtMouse.getColumn().getCards().contains(draggedCard)) {
                    topCardOfHoveredColumn = cardAtMouse.getColumn().getTopCard();
                    break;
                }
            }
            // Determine where to put all dragged cards
            List<Card> draggedCards = draggedCard.getColumn().getCardsOnTop(draggedCard);
            CardColumn fromColumn = draggedCard.getColumn();
            CardColumn toColumn = draggedCard.getColumn();
            if (topCardOfHoveredColumn == null) { // TODO: Handle what happens visuallyg at the different scenarios
                //System.out.println("Couldn't find column to place cards at. Putting cards back to column " + cardColumns.indexOf(toColumn));
            } else if (true) { // TODO: Replace "true" with a check if dropped card is allowed on top of topCardOfHoveredColumn
                toColumn = topCardOfHoveredColumn.getColumn();
                //System.out.println("Placing cards at column " + cardColumns.indexOf(toColumn));
            } else {
                //System.out.println("Illegal move. Putting cards back to column " + cardColumns.indexOf(toColumn));
            }
            moveCardsToColumn(draggedCards, fromColumn, toColumn);

            draggedCard = null;
        });
    }

    private void moveCardsToColumn(List<Card> cardsToMove, CardColumn fromColumn, CardColumn toColumn) {
        for (Card cardInStack : cardsToMove) {
            //System.out.println("Moving card " + cardInStack);
            StackPane stackPane = cardInStack.getStackPane();
            // Remove stackPane from dragVBox
            //System.out.println("dragVBox currently has " + dragVBox.getChildren().size() + " children. Removing " + cardInStack);
            dragVBox.getChildren().remove(stackPane);
            // Remove card from previous cardColumn
            //System.out.println("Removing " + cardInStack + " from previous cardColumn " + cardColumns.indexOf(fromColumn));
            fromColumn.removeCard(cardInStack);
            // Add card to new cardColumn
            //System.out.println("Adding " + cardInStack + " to new cardColumn " + cardColumns.indexOf(toColumn));
            toColumn.addCard(cardInStack);
        }
    }

    private List<Card> getCardsAtMouse(MouseEvent event) {
        List<Card> cardsAtMouse = new ArrayList<>();
        for (Card cardInScene : getCards()) {
            StackPane stackPane = cardInScene.getStackPane();
            Bounds localBounds = stackPane.getBoundsInLocal();
            Bounds sceneBounds = stackPane.localToScene(localBounds);

            if (sceneBounds.contains(new Point2D(event.getSceneX(), event.getSceneY()))) {
                // If mouse is within bounds of a card
                cardsAtMouse.add(cardInScene);
            }
        }
        return cardsAtMouse;
    }

    private void updateDragVBoxPosition(MouseEvent event) {
        double cardX = event.getSceneX() - dragOffset.getX();
        double cardY = event.getSceneY() - dragOffset.getY();
        dragVBox.setLayoutX(cardX);
        dragVBox.setLayoutY(cardY);
    }

    private InnerShadow getInnerShadowEffect() {
        InnerShadow effect = new InnerShadow();
        effect.setChoke(0);
        effect.setWidth(35);
        effect.setHeight(35);
        effect.setRadius(20);
        effect.setOffsetX(0);
        effect.setOffsetY(0);
        return effect;
    }

    private List<Card> getCards() {
        List<Card> cardList = new ArrayList<>();
        for (CardColumn column : cardColumns) {
            cardList.addAll(column.getCards());
        }
        return cardList;
    }

    public Controller addObserver(Observer observer) {
        observers.add(observer);
        return this;
    }

    public void notifyChange() {
        for (Observer observer : observers) {
            observer.onChange();
        }
    }

    /*
        From StackOverflow.com - https://stackoverflow.com/questions/1972392/pick-a-random-value-from-an-enum
        By user "eldelshell" - https://stackoverflow.com/users/48869/eldelshell
     */
    public static <T extends Enum<?>> T randomEnum(Class<T> classType) {
        int x = random.nextInt(classType.getEnumConstants().length);
        return classType.getEnumConstants()[x];
    }
}
