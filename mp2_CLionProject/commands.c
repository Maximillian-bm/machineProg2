#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "structs_util.c"

int ld(struct Board*);
int sw(struct Board*);
int si(struct Board*);
int sr(struct Board*);
int sd(struct Board*);
int p(struct Board*);
int q(struct Board*);
int move(struct Board*);
int u(struct Board*);
int r(struct Board*);
int s(struct Board*);
int l(struct Board*);

int ld(struct Board *board){
    printf("\nld() have been called with the argument:%s ", board->aguement);
    FILE *filePointer;
    int i = 0;

    // Define buffer to store card representation
    char cards[3];

    if (board->aguement[0] == '\0') {
        setDeckToDefoult(board->deck);

        printf("Default deck has been loaded successfully.\n");
        return 1;

    } else {
        // Construct filename based on argument
        char filename[50];
        snprintf(filename, sizeof(filename), "mp2_CLionProject/SaveDeck/%s.txt", board->aguement);
        filePointer = fopen(filename, "r");
    }

    if (filePointer == NULL) {
        printf("Unable to open file.\n");
        return 2; // Return error code
    }

    bool checkDeck[52];

    while(i < 52){
        checkDeck[i] = false;
        i++;
    }
    i = 0;
    int j = 0;

    // Read each card from the file
    while (fgets(cards, sizeof(cards), filePointer) != NULL && i < 52) {
        // Skip newline characters
        if (cards[0] == '\n') {
            continue;
        }
        int num = cardCharToNum(cards[0]);
        int suit;
        switch(cards[1]){
            case 'H':
                suit = -1;
                break;
            case 'D':
                suit = 12;
                break;
            case 'C':
                suit = 25;
                break;
            case 'S':
                suit = 38;
                break;
            default:
                j = 0;
                while(j<52){
                    board->deck[j].created = false;
                   j++;
                }
                return 500+i+1;
        }
        if(num<1||num>13){
            j = 0;
            while(j<52){
                board->deck[j].created = false;
                j++;
            }
            return 500+i+1;
        }
        if(checkDeck[suit+num]){
            j = 0;
            while(j<52){
                board->deck[j].created = false;
                j++;
            }
            return 600+i+1;
        }else{
            checkDeck[suit+num] = true;
        }

        // Store the card information in board->deck[i]
        board->deck[i].created = true;
        board->deck[i].hidden = true;
        board->deck[i].num = num;
        board->deck[i].suit = cards[1];
        i++;
    }

    fclose(filePointer);

    printf("Deck loaded from file successfully.\n");

    return 1;
}

int sw(struct Board *board){
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
        return 3;
    }
    return 1;
}
int si(struct Board *board){
    printf("\nsi() have been called with the argument:%s", board->aguement);
    int i = 0;
    int split = 26;
    if(board->aguement[0] == ' '){
        i = 1;
    }
    if(board->aguement[0] == '\0'){
        srand(time(0));
        split = (rand()%50) + 1;
    }else if(board->aguement[i+1] != '\0' && board->aguement[i+2] != '\0'){
        return 0;
    }else if(board->aguement[i+1] == '\0'){
        split = board->aguement[i]-'0';
    }else{
        split = (board->aguement[i+1]-'0')+(10*(board->aguement[i]-'0'));
    }
    if(split < 1 || split > 51){
        return 0;
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
    return 1;
}
int sr(struct Board *board){
    printf("\nsr() have been called");

    struct Card b;
    struct Card t;
    b.prevCard = NULL;
    b.nextCard = &board->deck[51];
    t.prevCard = &board->deck[51];
    t.nextCard = NULL;
    board->deck[51].nextCard = &t;
    board->deck[51].prevCard = &b;

    int i = 50;

    while(i >= 0){
        srand(time(0));
        int r = rand()%(-i+52);
        struct Card* card = cardPointerAt(&b, r);
        board->deck[i].prevCard = card;
        board->deck[i].nextCard = card->nextCard;
        card->nextCard->prevCard = &board->deck[i];
        card->nextCard = &board->deck[i];

        i--;
    }

    struct Card temp[52];
    i = 0;
    while(i < 52){
        temp[i] = *cardPointerAt(b.nextCard, i);
        i++;
    }
    i = 0;
    while(i < 52){
        board->deck[i] = temp[i];
        i++;
    }
    return 1;
}
int sd(struct Board *board){
    printf("\nsd() have been called with the argument:%s", board->aguement);

    FILE *filePointer;
    int i = 0;
    char suit[52];
    char num[52];

    while(i<52){
        suit[i] = board->deck[i].suit;
        num[i] = cardNumToChar(board->deck[i].num);
        i++;
    }

// fopen opens the file: syntax fopen(fileName, editMode)
    if(board->aguement[0] == '\0') {
        filePointer = fopen("mp2_CLionProject/SaveDeck/cards.txt", "w");
    }else{
        char filename[50];
        snprintf(filename, sizeof(filename), "mp2_CLionProject/SaveDeck/%s.txt", board->aguement);
        filePointer = fopen(filename, "w");
    }

// Check if the file opened successfully
    if (filePointer == NULL) {
        printf("Unable to open file.\n");
        return 2; // Return error code
    }

// Write each suit and number to the file
    for (i = 0; i < 52; i++) {
        fprintf(filePointer, "%c%c\n", num[i], suit[i]);
    }

// Close the file
    fclose(filePointer);

    printf("\nDeck has been saved successfully.");

    return 1;
}
int p(struct Board *board){
    printf("\np() have been called");

    int k = 0;

    while(k < 52){
        if(board->deck[k].created != true){
            return 3;
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
    return 1;
}
int q(struct Board *board){
    printf("\nq() have been called");
    int i = 0;
    while(i < 52){
        board->deck[i].hidden = true;
        i++;
    }
    board->playPhase = false;
    freeAllLogs(board->log);
    board->log = NULL;
    return 1;
}
int move(struct Board *board){
    printf("\nmove() have been called with the argument:%s", board->aguement);
    struct Card *from;
    struct Card *to;
    bool fromF = false;
    int pileNr = 0;
    char dc = '\0';
    int dn = 0;
    char suit = '\0';
    int num = 0;

    if(board->aguement[0] == 'C' && board->aguement[2] == ':' && board->aguement[5] == '-' && board->aguement[6] == '>'){
        pileNr = board->aguement[1]-'0';
        pileNr--;
        num = cardCharToNum(board->aguement[3]);
        suit = board->aguement[4];
        dc = board->aguement[7];
        dn = board->aguement[8]-'0';

        if(num < 1 || num > 13 || (suit != 'H' && suit != 'D' && suit != 'C' && suit != 'S')){
            return 4;
        }

        int i = 0;
        while(true){
            from = cardPointerAt(board->c[pileNr], i);
            if(from == NULL){
                return 4;
            }else if(from->num == num && from->suit == suit){
                break;
            }
            i++;
        }

    }else if(board->aguement[0] == 'F' && board->aguement[2] == '-' && board->aguement[3] == '>'){
        pileNr = board->aguement[1]-'0';
        pileNr--;
        dc = board->aguement[4];
        dn = board->aguement[5]-'0';
        fromF = true;

        from = cardPointerAtTop(board->f[pileNr]);

        if(from == NULL){
            return 4;
        }
    }else{
        return 4;
    }

    dn--;

    if(dn == pileNr && ((dc == 'C' && !fromF)||(dc == 'F' && fromF))){
        return 4;
    }

    if(dc == 'C'){
        if((board->c[dn] == NULL && from->num != 13) || dn < 0 || dn > 6){
            return 4;
        }else if(board->c[dn] == NULL){
            struct Log thisMove;
            thisMove.moved = from;
            thisMove.from = from->prevCard;
            thisMove.to = NULL;
            if(fromF){
                thisMove.cfFrom = 'F';
            }else{
                thisMove.cfFrom = 'C';
            }
            thisMove.pileFrom = pileNr;
            thisMove.cfTo = dc;
            thisMove.pileTo = dn;
            thisMove.hidden = false;
            saveLog(board, thisMove);
            board->c[dn] = from;
            if(fromF && from->prevCard == NULL){
                board->f[pileNr] = NULL;
            }else if(!fromF && from->prevCard == NULL){
                board->c[pileNr] = NULL;
            }else{
                from->prevCard->nextCard = NULL;
                from->prevCard = NULL;
            }
            return 1;
        }else{
            to = cardPointerAtTop(board->c[dn]);
            if(from->suit != to->suit && from->num+1 == to->num){
                struct Log thisMove;
                thisMove.moved = from;
                thisMove.from = from->prevCard;
                thisMove.to = to;
                if(fromF){
                    thisMove.cfFrom = 'F';
                }else{
                    thisMove.cfFrom = 'C';
                }
                thisMove.pileFrom = pileNr;
                thisMove.cfTo = dc;
                thisMove.pileTo = dn;
                thisMove.hidden = false;
                if(from->prevCard != NULL){
                    thisMove.hidden = from->prevCard->hidden;
                }
                saveLog(board, thisMove);
                if(from->prevCard == NULL && fromF) board->f[pileNr] = NULL;
                if(from->prevCard == NULL && !fromF) board->c[pileNr] = NULL;
                return moveAontopofB(from, to);
            }else{
                return 4;
            }
        }
    }else if(dc == 'F'){
        if(from->nextCard != NULL) return 4;
        if((board->f[dn] == NULL && from->num != 1)|| dn < 0 || dn > 3){
            return 4;
        }else if(board->f[dn] == NULL) {
            struct Log thisMove;
            thisMove.moved = from;
            thisMove.from = from->prevCard;
            thisMove.to = NULL;
            if(fromF){
                thisMove.cfFrom = 'F';
            }else{
                thisMove.cfFrom = 'C';
            }
            thisMove.pileFrom = pileNr;
            thisMove.cfTo = dc;
            thisMove.pileTo = dn;
            thisMove.hidden = false;
            saveLog(board, thisMove);
            board->f[dn] = from;
            if (fromF && from->prevCard == NULL) {
                board->f[pileNr] = NULL;
            } else if (!fromF && from->prevCard == NULL) {
                board->c[pileNr] = NULL;
            }else{
                from->prevCard->nextCard = NULL;
                from->prevCard = NULL;
            }
            return 1;
        }else{
            to = cardPointerAtTop(board->f[dn]);
            if(from->suit == to->suit && from->num == to->num+1){
                struct Log thisMove;
                thisMove.moved = from;
                thisMove.from = from->prevCard;
                thisMove.to = to;
                if(fromF){
                    thisMove.cfFrom = 'F';
                }else{
                    thisMove.cfFrom = 'C';
                }
                thisMove.pileFrom = pileNr;
                thisMove.cfTo = dc;
                thisMove.pileTo = dn;
                thisMove.hidden = false;
                if(from->prevCard != NULL){
                    thisMove.hidden = from->prevCard->hidden;
                }
                saveLog(board, thisMove);
                if(from->prevCard == NULL && fromF) board->f[pileNr] = NULL;
                if(from->prevCard == NULL && !fromF) board->c[pileNr] = NULL;
                return moveAontopofB(from, to);
            }else{
                return 4;
            }
        }
    }else{
        return 4;
    }
}
int u(struct Board *board){
    printf("\nu() have been called");
    return -1;
}
int r(struct Board *board){
    printf("\nr() have been called");
    return -1;
}
int s(struct Board *board){
    printf("\ns() have been called with the argument:%s", board->aguement);
    return -1;
}
int l(struct Board *board){
    printf("\nl() have been called with the argument:%s", board->aguement);
    return -1;
}