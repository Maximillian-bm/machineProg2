#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

struct Card{
    bool hidden;
    char suit;
    int num;
    struct Card* prevCard;
    struct Card* nextCard;
};

struct CardInDeck{
    bool hidden;
    bool created;
    char suit;
    char num;
};

struct Board{

    char input[20];

    char output[20];

    bool playPhase;

    struct CardInDeck deck[52];

    struct Card* c[7];

    struct Card* f[4];
};

char* findAgument(struct Board*, int);
int findMethod(struct Board*);

void ld(struct Board*, char*);
void sw(struct Board*);
void si(struct Board*, char*);
void sr(struct Board*);
void sd(struct Board*, char*);
void p(struct Board*);
void q(struct Board*);
void move(struct Board*, char*);
void u(struct Board*);
void r(struct Board*);
void s(struct Board*, char*);
void l(struct Board*, char*);

void printBord(struct Board);

char* cardAt(struct Card*,int);
char* cardAtTop(struct Card*);
char cardNumToChar(int value);

void ok(struct Board*);
void notOK(struct Board*);

int main() {

    struct Board board;
    int i = 0;
    while(i<52){
        board.deck[i].created = false;
        i++;
    }

    board.playPhase = false;

    bool exit = false;

    while(!exit) {
        printBord(board);

        scanf("%20s", board.input);

        int method = findMethod(&board);

        switch (method) {
            case 1:
                ld(&board, findAgument(&board,1));
                break;
            case 2:
                sw(&board);
                break;
            case 3:
                si(&board, findAgument(&board,3));
                break;
            case 4:
                sr(&board);
                break;
            case 5:
                sd(&board, findAgument(&board,5));
                break;
            case 6:
                exit = true;
                break;
            case 7:
                p(&board);
                break;
            case 8:
                q(&board);
                break;
            case 9:
                move(&board,findAgument(&board,9));
                break;
            case 10:
                u(&board);
                break;
            case 11:
                r(&board);
                break;
            case 12:
                s(&board,findAgument(&board,12));
                break;
            case 13:
                l(&board,findAgument(&board,13));
                break;
        }
    }
    return 0;
}

char* findAgument(struct Board *board, int aguNum){
// in the "input" find and return the agument.
// in the case that the agunum is 1, 5, 12 or 13, return the filename in "input"
// in the case that agunum is 3 return the number in "input"
// in the case of 9 return the whole string of "input"
// any returns should be a char* to a new char array
    char r[20];
    int i = 0;
    while(true){
        if(board->input[i] == '\0'){
            break;
        }
        i++;
    }

    if(aguNum == 1 || aguNum == 3 || aguNum == 5){
        int j = 0;
        i--;
        while(j<i){
            r[j] = board->input[j+2];
            j++;
        }
    }else if(aguNum == 12 || aguNum == 13){
        int j = 0;
        while(j<i){
            r[j] = board->input[j+2];
            j++;
        }
    }else if(aguNum == 9){
        int j = 0;
        i++;
        while(j<i){
            r[j] = board->input[j];
            j++;
        }
    }
    return &r;
}
int findMethod(struct Board *board){
// return the number assotiated with the command saved in "input"
// if input is not valid return 0
    if(board->playPhase){
        switch(board->input[0]){
            case 'Q':
                if(board->input[1] == '\0'){
                    ok(board);
                    return 8;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'C':
                ok(board);
                return 9;
            case 'F':
                ok(board);
                return 9;
            case 'U':
                if(board->input[1] == '\0'){
                    ok(board);
                    return 10;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'R':
                if(board->input[1] == '\0'){
                    ok(board);
                    return 11;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'S':
                if(board->input[1] != '\0'){
                    ok(board);
                    return 12;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'L':
                if(board->input[1] != '\0'){
                    ok(board);
                    return 13;
                }else{
                    notOK(board);
                    return 0;
                }
        }
    }else{
        switch (board->input[1]) {
            case 'D':
                if(board->input[0] == 'L'){
                    ok(board);
                    return 1;
                }else if(board->input[0] == 'S'){
                    ok(board);
                    return 5;
                }else{
                    notOK(board);
                }
            case 'W':
                if(board->input[0] == 'S' && board->input[2] == '\0'){
                    ok(board);
                    return 2;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'I':
                if(board->input[0] == 'S'){
                    ok(board);
                    return 3;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'R':
                if(board->input[0] == 'S' && board->input[2] == '\0'){
                    ok(board);
                    return 4;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'Q':
                if(board->input[0] == 'Q' && board->input[2] == '\0'){
                    ok(board);
                    return 6;
                }else{
                    notOK(board);
                    return 0;
                }
            case '\0':
                if(board->input[0] == 'P'){
                    ok(board);
                    return 7;
                }else{
                    notOK(board);
                    return 0;
                }
        }
    }
    notOK(board);
    return 0;
}

void ld(struct Board *board, char* filename){

}
void sw(struct Board *board){

}
void si(struct Board *board, char* num){

}
void sr(struct Board *board){

}
void sd(struct Board *board, char* filename){

}
void p(struct Board *board){

}
void q(struct Board *board){

}
void move(struct Board *board, char* move){

}
void u(struct Board *board){

}
void r(struct Board *board){

}
void s(struct Board *board, char* filename){

}
void l(struct Board *board, char* filename){

}
void printBord(struct Board board){
    printf("\n");
    if(board.playPhase){
        printf("C1   C2   C3   C4   C5   C6   C7\n\n");
        int i = 0;
        bool done = false;
        while(!done){
            done = true;
            int j = 0;
            while(j<7){
                char* card = cardAt(board.c[j], i);
                printf("%s    ", card);
                if(*card != ' '){
                    done = false;
                }
                j++;
            }
            printf("      ");

            if(i == 0){
                printf("%s F1", cardAtTop(board.f[0]));
            }else if(i == 2){
                printf("%s F2", cardAtTop(board.f[1]));
            }else if(i == 4){
                printf("%s F3", cardAtTop(board.f[2]));
            }else if(i == 6){
                printf("%s F4", cardAtTop(board.f[3]));
            }

            printf("\n");

            i++;
        }
        printf("LAST Command:%s\n", board.input);
        printf("Message:%s\n", board.output);
        printf("INPUT>");
    }else{
        printf("C1    C2    C3    C4    C5    C6    C7\n\n");
        int i = 0;
        while(i<8){
            int j = 0;
            while(j<7){
                if(j+(7*i)<52 && board.deck[j+(7*i)].created){
                    printf("%c%c    ", board.deck[j+(7*i)].num,board.deck[j+(7*i)].suit);
                }else{
                    printf("      ");
                }
                j++;
            }
            printf("      ");

            if(i == 0){
                printf("[] F1");
            }else if(i == 2){
                printf("[] F2");
            }else if(i == 4){
                printf("[] F3");
            }else if(i == 6){
                printf("[] F4");
            }
            printf("\n");
            i++;
        }
        printf("LAST Command:%s\n", board.input);
        printf("Message:%s\n", board.output);
        printf("INPUT>");
    }

}

/*
 * Function: cardAt
 * ----------------------------
 * Find the card at the given position and returns its value and suit as a string (E.g. King of Hearts: "KH" or Two of Diamonds: "2D").
 * If there is no card at the given position, the method returns: "  ".
 * If the card at the given position is hidden, the method returns: "[]".
 *
 * Parameters:
 * struct Card* card:   The pointer to the first card in a list. Must not be null.
 * int at:              The distance from card in the linked list. Must be greater than or equal to 0.
 *
 * Returns:
 * The string of the card value and suit.
 */
char* cardAt(struct Card* card, int at) {
    // Error handling
    if (card == NULL) {
        printf("Error: Card pointer must not be null. Received: %p\n", card);
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

/*
 * Function: cardAtTop
 * ----------------------------
 * Finds the card at the top of the card list from the given card and returns its value and suit as a string. (E.g. King of Hearts: "KH" or Two of Diamonds: "2D").
 * If there are no cards in the list, the method returns: "  ".
 *
 * Parameters:
 * struct Card* card:   The pointer to the first card in a list. Must not be null.
 *
 * Returns:
 * The string of the card value and suit of the top card.
 */
char* cardAtTop(struct Card* card){
    // Error handling
    if (card == NULL) {
        printf("Error: Card pointer must not be null. Received: %p\n", card);
        return "  ";
    }

    if (card->nextCard == NULL) { // Base case
        char *combinedString = malloc(2 * sizeof(char) + 1); // Allocate space for two chars and a null terminator in memory;
        snprintf(combinedString, sizeof(combinedString), "%c%c", cardNumToChar(card->num), card->suit); // Combine the value with the suit.
        return combinedString;
    } else { // Recursive call
        return cardAtTop(card->nextCard);
    }
}

/*
 * Function: cardAtTop
 * ----------------------------
 * Converts a card value to char, where 1=A, 10=T, 11=J, 12=Q and 13=K.
 *
 * Parameters:
 * int value:   The value of the card. Must be between 1 (included) and 13 (included).
 *
 * Returns:
 * The value as a string.
 */
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
            return (char)value;
    }
}

void ok(struct Board *board){
    board->output[0] = 'O';
    board->output[1] = 'K';
    board->output[2] = '\0';
}

void notOK(struct Board *board){
    board->output[0] = 'N';
    board->output[1] = 'O';
    board->output[2] = 'T';
    board->output[3] = ' ';
    board->output[4] = 'V';
    board->output[5] = 'A';
    board->output[6] = 'L';
    board->output[7] = 'I';
    board->output[8] = 'D';
    board->output[9] = '\0';
}
