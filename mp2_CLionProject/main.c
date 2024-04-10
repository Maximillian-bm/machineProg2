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
    char suit;
    int num;
};

struct Board{

    char input[20];

    bool playPhase;

    struct CardInDeck deck[52];

    struct Card* c[7];

    struct Card* f[4]
};

char* findAgument(struct Board, int);
int findMethod(struct Board);

bool ld(struct Board, char*);
bool sw(struct Board);
bool sl(struct Board, char*);
void sr(struct Board);
void sd(struct Board, char*);
void p(struct Board);
void q(struct Board);
bool move(struct Board, char*);
void u(struct Board);
bool r(struct Board);
void s(struct Board, char*);
bool l(struct Board, char*);

void printBord(struct Board);

int main() {

    struct Board board;

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

bool ld(struct Board board, char* filename){

}
bool sw(struct Board board){

}
bool sl(struct Board board, char* num){

}
void sr(struct Board board){

}
void sd(struct Board board, char* filename){

}
void p(struct Board board){

}
void q(struct Board board){

}
bool move(struct Board board, char* move){

}
void u(struct Board board){

}
bool r(struct Board board){

}
void s(struct Board board, char* filename){

}
bool l(struct Board board, char* filename){

}
void printBord(struct Board board){

}
