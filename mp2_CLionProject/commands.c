#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "game_util.c"

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
        notOK(board->output);
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
        srand(time(0));
        split = (rand()%50) + 1;
    }else if(board->aguement[i+1] != '\0' && board->aguement[i+2] != '\0'){
        notOK(board->output);
        return;
    }else if(board->aguement[i+1] == '\0'){
        split = board->aguement[i]-'0';
    }else{
        split = (board->aguement[i+1]-'0')+(10*(board->aguement[i]-'0'));
    }
    if(split < 1 || split > 51){
        notOK(board->output);
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
}
void sd(struct Board *board){
    printf("\nsd() have been called with the argument:%s", board->aguement);
}
void p(struct Board *board){
    printf("\np() have been called");

    int k = 0;

    while(k < 52){
        if(board->deck[k].created != true){
            notOK(board->output);
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
    int i = 0;
    while(i < 52){
        board->deck[i].hidden = true;
        i++;
    }
    board->playPhase = false;
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