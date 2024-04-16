#include <stdio.h>
#include <malloc.h>
#include "structs.c"

char* cardAt(struct Card*,int);
char* cardAtTop(struct Card*);
char cardNumToChar(int);
struct Card* cardPointerAt(struct Card*, int);
void setDeckToDefoult(struct Card*);

char* cardAt(struct Card* card, int at) {
    // Error handling
    if (card == NULL) {
        //printf("Error: Card pointer must not be null. Received: %p\n", card);
        return "  ";
    } else if (at < 0) {
        printf("Error: Card position argument can not be negative. Received: %d\n", at);
        return "  ";
    }

    // Recursive call to find card at the given position.
    if (at == 0) { // Base case
        if (card->hidden == true) {
            return "[]";
        } else {
            char *combinedString = malloc(2 * sizeof(char) + 1); // Allocate space for two chars and a null terminator in memory;
            snprintf(combinedString, sizeof(combinedString), "%c%c", cardNumToChar(card->num), card->suit); // Combine the value with the suit.
            return combinedString;
        }
    } else { // (at > 0)
        if (card->nextCard == NULL) {
            return "  ";
        } else { // Recursive call
            return cardAt(card->nextCard, at - 1);
        }
    }
}

char* cardAtTop(struct Card* card){
    // Error handling
    if (card == NULL) {
        //printf("Error: Card pointer must not be null. Received: %p\n", card);
        return "[]";
    }

    if (card->nextCard == NULL) { // Base case
        char *combinedString = malloc(2 * sizeof(char) + 1); // Allocate space for two chars and a null terminator in memory;
        snprintf(combinedString, sizeof(combinedString), "%c%c", cardNumToChar(card->num), card->suit); // Combine the value with the suit.
        return combinedString;
    } else { // Recursive call
        return cardAtTop(card->nextCard);
    }
}

char cardNumToChar(int value) {
    if (value < 1 || value > 13) {
        printf("Error: Value must be between 1 and 13. Received: %d\n", value);
        return '0';
    }
    switch (value) {
        case 1:
            return 'A';
        case 10:
            return 'T';
        case 11:
            return 'J';
        case 12:
            return 'Q';
        case 13:
            return 'K';
        default:
            return (char)(value+'0');
    }
}

struct Card* cardPointerAt(struct Card* card, int i){
    if(i <= 0){
        return card;
    }else{
        return cardPointerAt(card->nextCard, i-1);
    }
}

void setDeckToDefoult(struct Card *deck){
    int i = 0;
    while(i<52){
        deck[i].created = true;
        deck[i].hidden = true;
        if(i<13){
            deck[i].suit = 'C';
        }else if(i<26){
            deck[i].suit = 'D';
        }else if(i<39){
            deck[i].suit = 'H';
        }else{
            deck[i].suit = 'S';
        }
        deck[i].num = (i%13)+1;

        i++;
    }
}