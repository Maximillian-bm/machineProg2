#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>

struct Card{
    bool hidden;
    char suit;
    int num;
    struct Card* prevCard;
    struct Card* nextCard;
    bool created;
};

struct Board{

    struct Card deck[52];

    char aguement[21];

    char input[21];

    char output[21];

    bool playPhase;

    struct Card* c[7];

    struct Card* f[4];
};

void findAgument(struct Board*, int);
int findMethod(struct Board*);

void setDeckToDefoult(struct Board*);
void ld(struct Board*);
void sw(struct Board*);
void si(struct Board*);
void sr(struct Board*);
void sd(struct Board*);
void p(struct Board*);
void q(struct Board*);
void move(struct Board*);
void u(struct Board*);
void r(struct Board*);
void s(struct Board*);
void l(struct Board*);

void printBord(struct Board*);

char* cardAt(struct Card*,int);
char* cardAtTop(struct Card*);
char cardNumToChar(int);
int cardCharToNum(char);

void ok(struct Board*);
void notOK(struct Board*);

int main() {

    int c;
    struct Board board;
    int i = 0;
    while(i<52){
        board.deck[i].created = false;
        i++;
    }

    board.input[0] = '\0';

    board.output[0] = '\0';

    board.playPhase = false;

    bool exit = false;

    while(!exit) {
        printBord(&board);

        scanf("%20[^\n]", board.input);

        while ((c = getchar()) != '\n' && c != EOF);

        int method = findMethod(&board);

        switch (method) {
            case 1:
                findAgument(&board,1);
                ld(&board);
                break;
            case 2:
                sw(&board);
                break;
            case 3:
                findAgument(&board,3);
                si(&board);
                break;
            case 4:
                sr(&board);
                break;
            case 5:
                findAgument(&board,5);
                sd(&board);
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
                findAgument(&board,9);
                move(&board);
                break;
            case 10:
                u(&board);
                break;
            case 11:
                r(&board);
                break;
            case 12:
                findAgument(&board,12);
                s(&board);
                break;
            case 13:
                findAgument(&board,13);
                l(&board);
                break;
        }
    }
    return 0;
}

void findAgument(struct Board *board, int aguNum){
// in the "input" find and return the agument.
// in the case that the agunum is 1, 5, 12 or 13, return the filename in "input"
// in the case that agunum is 3 return the number in "input"
// in the case of 9 return the whole string of "input"
// any returns should be a char* to a new char array
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
            board->aguement[j] = board->input[j+2];
            j++;
        }
    }else if(aguNum == 12 || aguNum == 13){
        int j = 0;
        while(j<i){
            board->aguement[j] = board->input[j+2];
            j++;
        }
    }else if(aguNum == 9){
        int j = 0;
        i++;
        while(j<i){
            board->aguement[j] = board->input[j];
            j++;
        }
    }
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

void setDeckToDefoult(struct Board* board){
    int i = 0;
    while(i<52){
        board->deck[i].created = true;
        board->deck[i].hidden = true;
        if(i<13){
            board->deck[i].suit = 'C';
        }else if(i<26){
            board->deck[i].suit = 'D';
        }else if(i<39){
            board->deck[i].suit = 'H';
        }else{
            board->deck[i].suit = 'S';
        }
        board->deck[i].num = (i%13)+1;

        i++;
    }
}

void ld(struct Board *board){
    printf("\nld() have been called with the argument:%s", board->aguement);
    setDeckToDefoult(board);
}
void sw(struct Board *board){
    printf("\nsw() have been called");
    bool valid = false;
    int i = 0;
    while(i<52) {
        if(board->deck[i].created) {
            board->deck[i].hidden = false;
            valid = true;
        }
        i++;
    }
    if(!valid){
        notOK(board);
    }
}
void si(struct Board *board){
    printf("\nsi() have been called with the argument:%s", board->aguement);
    int i = 0;
    int split = 26;
    if(board->aguement[0] == ' '){
        i = 1;
    }
    if(board->aguement[0] == '\0'){
        split = (rand()%50) + 1;
    }else if(board->aguement[i+1] != '\0' && board->aguement[i+2] != '\0'){
        notOK(board);
        return;
    }else if(board->aguement[i+1] == '\0'){
        split = board->aguement[i]-'0';
    }else{
        split = (board->aguement[i+1]-'0')+(10*(board->aguement[i]-'0'));
    }
    if(split < 1 || split > 51){
        notOK(board);
        return;
    }

    i = 0;
    struct Card pile1[split];
    struct Card pile2[52-split];
    while(i < 52){
        if(i > 51-split){
            pile2[i] = board->deck[i];
        }else{
            pile1[i-(52-split)] = board->deck[i];
        }
        i++;
    }

    int p1 = 0;
    int p2 = 0;
    i = 0;
    while(i < 52){
        if(i < split*2 && i < ((52-split)*2)+1){
            if(i%2 == 0){
                board->deck[i] = pile1[i/2];
                p1 = i/2;
            }else{
                board->deck[i] = pile2[(i-1)/2];
                p2 = (i-1)/2;
            }
        }else if(split>52-split){
            p1++;
            board->deck[i] = pile1[p1];
        }else{
            p2++;
            board->deck[i] = pile2[p2];
        }
        i++;
    }
}
void sr(struct Board *board){
    printf("\nsr() have been called");
}
void sd(struct Board *board){
    printf("\nsd() have been called with the argument:%s", board->aguement);
}
void p(struct Board *board){
    printf("\np() have been called");

    int k = 0;

    while(k < 52){
        if(board->deck[k].created != true){
            notOK(board);
            return;
        }
        k++;
    }

    board->c[0] = &board->deck[0];
    board->c[1] = &board->deck[1];
    board->c[2] = &board->deck[2];
    board->c[3] = &board->deck[3];
    board->c[4] = &board->deck[4];
    board->c[5] = &board->deck[5];
    board->c[6] = &board->deck[6];

    board->f[0] = NULL;
    board->f[1] = NULL;
    board->f[2] = NULL;
    board->f[3] = NULL;

    board->deck[0].hidden = false;
    board->deck[0].nextCard = NULL;
    board->deck[0].prevCard = NULL;

    int i;
    int pile = 1;

    while(pile < 7){
        i = 0;
        while(i < 5+pile){
            int j = 0;
            int p = 0;
            int t = 0;
            int n = 0;
            while(j < i-4){
                j++;
                p = t;
                t = n;
                n = n + j;
            }
            int preOffset = ((i-1) * 6) + pile - p;
            int offset = (i * 6) + pile - t;
            int nextOffset = ((i+1) * 6) + pile - n;

            if(i > 0 && i < 4+pile) {
                board->deck[offset].prevCard = &board->deck[preOffset];
                board->deck[offset].nextCard = &board->deck[nextOffset];
            }else if(i == 0) {
                board->deck[offset].prevCard = NULL;
                board->deck[offset].nextCard = &board->deck[nextOffset];
            }else if(i == 4+pile){
                board->deck[offset].prevCard = &board->deck[preOffset];
                board->deck[offset].nextCard = NULL;
            }

            if(i < pile){
               board->deck[offset].hidden = true;
            }else{
                board->deck[offset].hidden = false;
            }
            i++;
        }
        pile++;
    }

    board->playPhase = true;

}
void q(struct Board *board){
    printf("\nq() have been called");
}
void move(struct Board *board){
    printf("\nmove() have been called with the argument:%s", board->aguement);
}
void u(struct Board *board){
    printf("\nu() have been called");
}
void r(struct Board *board){
    printf("\nr() have been called");
}
void s(struct Board *board){
    printf("\ns() have been called with the argument:%s", board->aguement);
}
void l(struct Board *board){
    printf("\nl() have been called with the argument:%s", board->aguement);
}
void printBord(struct Board *board){
    printf("\n");
    if(board->playPhase){
        printf("C1   C2   C3   C4   C5   C6   C7\n\n");
        int i = 0;
        bool done = false;
        while(!done){
            done = true;
            int j = 0;
            while(j<7){
                char* card = cardAt(board->c[j], i);
                printf("%s   ", card);
                if(*card != ' '){
                    done = false;
                }
                j++;
            }
            printf("      ");

            if(i == 0){
                printf("%s F1", cardAtTop(board->f[0]));
            }else if(i == 2){
                printf("%s F2", cardAtTop(board->f[1]));
            }else if(i == 4){
                printf("%s F3", cardAtTop(board->f[2]));
            }else if(i == 6){
                printf("%s F4", cardAtTop(board->f[3]));
            }

            printf("\n");

            i++;
        }
        printf("LAST Command:%s\n", board->input);
        printf("Message:%s\n", board->output);
        printf("INPUT>");
    }else{
        printf("C1    C2    C3    C4    C5    C6    C7\n\n");
        int i = 0;
        while(i<8){
            int j = 0;
            while(j<7){
                if(j+(7*i)<52 && board->deck[j+(7*i)].created && !board->deck[j+(7*i)].hidden){
                    printf("%c%c    ", cardNumToChar(board->deck[j+(7*i)].num),board->deck[j+(7*i)].suit);
                }else if(j+(7*i)<52 && board->deck[j+(7*i)].created && board->deck[j+(7*i)].hidden){
                    printf("[]    ");
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
        printf("LAST Command:%s\n", board->input);
        printf("Message:%s\n", board->output);
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
            return (char)(value+'0');
    }
}

int cardCharToNum(char value) {

    switch (value) {
        case 'A':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'T':
            return 10;
        case 'J':
            return 11;
        case 'D':
            return 12;
        case 'K':
            return 13;
        default:
            printf("Error: Value not valid: %c\n", value);
            return 0;
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
