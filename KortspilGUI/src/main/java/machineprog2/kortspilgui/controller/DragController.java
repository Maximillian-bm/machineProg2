package machineprog2.kortspilgui.controller;

import javafx.geometry.Bounds;
import javafx.geometry.Point2D;
import javafx.scene.effect.InnerShadow;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import machineprog2.kortspilgui.model.Card;
import machineprog2.kortspilgui.model.CardColumn;
import machineprog2.kortspilgui.util.Effects;

import java.util.ArrayList;
import java.util.List;

public class DragController {
    private static Point2D dragOffset;
    private static VBox dragVBox;
    private static Card topMostHoveredCard = null;
    private static InnerShadow innerShadowEffect;
    private static Card draggedCard;
    private static AnchorPane rootPane;


    public static void initializeDragController(AnchorPane rootPane_) {
        dragVBox = new VBox();
        rootPane = rootPane_;
        rootPane.getChildren().add(dragVBox);
        innerShadowEffect = Effects.getInnerShadowEffect();
    }

    public static void initializeCardEventListeners(Card card) {
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

    public static void initializeRootPaneEventListeners() { // Checking for all cards individually in scene. If not done like this, .setOnMouseDragged on cards would only get the top node at the mouse position
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
            for (Card cardInScene : Controller.getCards()) {
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

    private static void moveCardsToColumn(List<Card> cardsToMove, CardColumn fromColumn, CardColumn toColumn) {
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

    private static List<Card> getCardsAtMouse(MouseEvent event) {
        List<Card> cardsAtMouse = new ArrayList<>();
        for (Card cardInScene : Controller.getCards()) {
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

    private static void updateDragVBoxPosition(MouseEvent event) {
        double cardX = event.getSceneX() - dragOffset.getX();
        double cardY = event.getSceneY() - dragOffset.getY();
        dragVBox.setLayoutX(cardX);
        dragVBox.setLayoutY(cardY);
    }
}
