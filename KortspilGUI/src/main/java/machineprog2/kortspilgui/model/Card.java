package machineprog2.kortspilgui.model;

import javafx.scene.image.Image;
import javafx.scene.layout.StackPane;
import machineprog2.kortspilgui.controller.Controller;

import java.util.Objects;

public class Card {
    private final Suit suit;
    private final int value;
    private final CardJavaFX cardJavaFX;
    private final static Image image_cardBack = new Image(Objects.requireNonNull(Card.class.getResourceAsStream("/machineprog2/kortspilgui/art/cardback.png")));
    private final Image image_card;

    private boolean visible = false;
    private CardColumn column;

    public Card(Suit suit, int value, boolean visible, Controller ctrl) {
        //System.out.println("Making new card with suit " + suit + " and value " + value);
        this.suit = suit;
        this.value = value;
        this.visible = visible;

        image_card = getCardImage();
        cardJavaFX = new CardJavaFX();

        updateImageFromVisibility();

        ctrl.initializeCardEventListeners(this);
    }

    public void setCardColumn(CardColumn column) {
        this.column = column;
    }

    private Image getCardImage() {
        String imagePath = "/machineprog2/kortspilgui/art/" + suit.toString() + value + ".png";
        return new Image(Objects.requireNonNull(Card.class.getResourceAsStream(imagePath)));
    }

    public StackPane getStackPane() {
        return cardJavaFX.stackPane;
    }

    public boolean getVisible() {
        return visible;
    }

    public void setVisible(boolean visible) {
        this.visible = visible;
        updateImageFromVisibility();
    }

    public int getValue() {
        return value;
    }

    public Suit getSuit() {
        return suit;
    }

    public CardColumn getColumn() {
        return column;
    }

    private void updateImageFromVisibility() {
        if (visible) {
            cardJavaFX.imageView.setImage(image_card);
        } else {
            cardJavaFX.imageView.setImage(image_cardBack);
        }
    }

    @Override
    public String toString() {
        return "{" + value + " of " + suit + "}";
    }
}
