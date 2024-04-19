#include <stdio.h>
#include "structs.c"

void cardAt(struct Card*, int, char*);
void cardAtTop(struct Card*, char*);
char cardNumToChar(int);
int cardCharToNum(char);
struct Card* cardPointerAt(struct Card*, int);
struct Card* cardPointerAtTop(struct Card*);
void setDeckToDefoult(struct Card*);
void printBord(struct Board*);
bool moveAontopofB(struct Card*, struct Card*);
void saveLog(struct Board*, struct Log);
void freeLogsAbove(struct Log*);
void freeAllLogs(struct Log*);

void cardAt(struct Card* card, int at, char* cardPointer) {
    // Error handling
    if (card == NULL) {
        //printf("Error: Card pointer must not be null. Received: %p\n", card);
        return;
    } else if (at < 0) {
        printf("Error: Card position argument can not be negative. Received: %d\n", at);
        return;
    }

    // Recursive call to find card at the given position.
    if (at == 0) { // Base case
        if (card->hidden == true) {
            cardPointer[0] = '[';
            cardPointer[1] = ']';
        } else {
            snprintf(cardPointer, sizeof(cardPointer), "%c%c", cardNumToChar(card->num), card->suit); // Combine the value with the suit.
            return;
        }
    } else { // (at > 0)
        if (card->nextCard == NULL) {
            return;
        } else { // Recursive call
            cardAt(card->nextCard, at - 1, cardPointer);
            return;
        }
    }
}

void cardAtTop(struct Card* card, char* cardPointer){
    // Error handling
    if (card == NULL) {
        //printf("Error: Card pointer must not be null. Received: %p\n", card);
        return;
    }

    if (card->nextCard == NULL) { // Base case
        snprintf(cardPointer, sizeof(cardPointer), "%c%c", cardNumToChar(card->num), card->suit); // Combine the value with the suit.
        return;
    } else { // Recursive call
        cardAtTop(card->nextCard, cardPointer);
        return;
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
        case 'Q':
            return 12;
        case 'K':
            return 13;
        default:
            printf("Error: Value not valid: %c\n", value);
            return 0;
    }
}

struct Card* cardPointerAt(struct Card* card, int i){
    if(i <= 0 || card == NULL){
        return card;
    }else{
        return cardPointerAt(card->nextCard, i-1);
    }
}


struct Card* cardPointerAtTop(struct Card* card){
    if(card == NULL){
        return NULL;
    }else if(card->nextCard == NULL){
        return card;
    }else{
        return cardPointerAtTop(card->nextCard);
    }
}

void setDeckToDefoult(struct Card deck[]){
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
                char card[] = "  ";
                cardAt(board->c[j], i, card);

                printf("%s   ", card);
                if(*card != ' '){
                    done = false;
                }
                j++;
            }
            printf("      ");

            char cardPointer[] = "[]";
            if (i < 7 && i % 2 == 0) {
                cardAtTop(board->f[i / 2], cardPointer);
            }
            if(i == 0){
                printf("%s F1", cardPointer);
            }else if(i == 2){
                printf("%s F2", cardPointer);
            }else if(i == 4){
                printf("%s F3", cardPointer);
            }else if(i == 6){
                printf("%s F4", cardPointer);
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

bool moveAontopofB(struct Card *a, struct Card *b){

    if(b->nextCard != NULL){
        return false;
    }

    if(a->prevCard != NULL) {
        a->prevCard->nextCard = NULL;
        a->prevCard->hidden = false;
    }
    a->prevCard = b;
    b->nextCard = a;

    return true;

}

void saveLog(struct Board* board, struct Log l){
    freeLogsAbove(board->log);
    struct Log* log = (struct Log*)malloc(sizeof(struct Log));
    *log = l;
    log->nextLog = NULL;
    log->prevLog = board->log;
    if(board->log != NULL) board->log->nextLog = log;
    board->log = log;
}

void freeLogsAbove(struct Log* log){
    if(log != NULL){
        freeLogsAbove(log->nextLog);
        free(log->nextLog);
    }
}

void freeAllLogs(struct Log* log){
    if(log->prevLog == NULL){
        freeLogsAbove(log);
        free(log);
    }else{
        freeAllLogs(log->prevLog);
    }
}