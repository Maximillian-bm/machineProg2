#include <stdio.h>
#include <stdbool.h>

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

    struct Card* f[4]
};

char* findAgument(struct Board, int);
int findMethod(struct Board);

void ld(struct Board, char*);
void sw(struct Board);
void sl(struct Board, char*);
void sr(struct Board);
void sd(struct Board, char*);
void p(struct Board);
void q(struct Board);
void move(struct Board, char*);
void u(struct Board);
void r(struct Board);
void s(struct Board, char*);
void l(struct Board, char*);

void printBord(struct Board);

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

        int method = findMethod(board);

        switch (method) {
            case 1:
                ld(board, findAgument(board,1));
                break;
            case 2:
                sw(board);
                break;
            case 3:
                sl(board, findAgument(board,3));
                break;
            case 4:
                sr(board);
                break;
            case 5:
                sd(board, findAgument(board,5));
                break;
            case 6:
                exit = true;
                break;
            case 7:
                p(board);
                break;
            case 8:
                q(board);
                break;
            case 9:
                move(board,findAgument(board,9));
                break;
            case 10:
                u(board);
                break;
            case 11:
                r(board);
                break;
            case 12:
                s(board,findAgument(board,12));
                break;
            case 13:
                l(board,findAgument(board,13));
                break;
        }
    }
    return 0;
}

char* findAgument(struct Board board, int aguNum){
// in the "input" find and return the agument.
// in the case that the agunum is 1, 5, 12 or 13, return the filename between < > in "input"
// in the case that agunum is 3 return the number in "input"
// in the case of 9 return the whole string of "input"
// any returns should be a char* to a new char array
}
int findMethod(struct Board board){
// return the number assotiated with the command saved in "input"
// if input is not valid return 0
}

void ld(struct Board board, char* filename){

}
void sw(struct Board board){

}
void sl(struct Board board, char* num){

}
void sr(struct Board board){

}
void sd(struct Board board, char* filename){

}
void p(struct Board board){

}
void q(struct Board board){

}
void move(struct Board board, char* move){

}
void u(struct Board board){

}
void r(struct Board board){

}
void s(struct Board board, char* filename){

}
void l(struct Board board, char* filename){

}
void printBord(struct Board board){
    printf("\n");
    if(board.playPhase){
        printf("C1   C2   C3   C4   C5   C6   C7\n\n");
    }else{
        printf("C1   C2   C3   C4   C5   C6   C7\n\n");
        int i = 0;
        while(i<8){
            int j = 0;
            while(j<7){
                if(j+(7*i)<52 && board.deck[j+(7*i)].created){
                    printf("%c%c ", board.deck[j+(7*i)].num,board.deck[j+(7*i)].suit);
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
