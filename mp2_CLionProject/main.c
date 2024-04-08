#include <stdio.h>
#include <stdbool.h>

struct Card{
    bool hidden;
    char suit;
    int num;
    struct Card* prevCard;
    struct Card* nextCard;
};

char input[20];

bool playPhase = false;

char deck[2][52];

struct Card* C1;
struct Card* C2;
struct Card* C3;
struct Card* C4;
struct Card* C5;
struct Card* C6;
struct Card* C7;

struct Card* F1;
struct Card* F2;
struct Card* F3;
struct Card* F4;

char* findAgument(int);
int findMethod();

bool ld(char*);
bool sw();
bool sl(char*);
void sr();
void sd(char*);
void p();
void q();
bool move(char*);
void u();
bool r();
void s(char*);
bool l(char*);

void printBord();

int main() {
    bool exit = false;
    while(!exit) {
        printBord();
        scanf("%20s", input);
        int method = findMethod();
        switch (method) {
            case 1:
                ld(findAgument(1));
                break;
            case 2:
                sw();
                break;
            case 3:
                sl(findAgument(3));
                break;
            case 4:
                sr();
                break;
            case 5:
                sd(findAgument(5));
                break;
            case 6:
                exit = true;
                break;
            case 7:
                p();
                break;
            case 8:
                q();
                break;
            case 9:
                move(findAgument(9));
                break;
            case 10:
                u();
                break;
            case 11:
                r();
                break;
            case 12:
                s(findAgument(12));
                break;
            case 13:
                l(findAgument(13));
                break;
        }
    }
    return 0;
}

char* findAgument(int aguNum){
// in the "input" find and return the agument.
// in the case that the agunum is 1, 5, 12 or 13, return the filename between < > in "input"
// in the case that agunum is 3 return the number in "input"
// in the case of 9 return the whole string of "input"
// any returns should be a char* to a new char array
}
int findMethod(){
// return the number assotiated with the command saved in "input"
// if input is not valid return 0
}

bool ld(char* filename){

}
bool sw(){

}
bool sl(char* num){

}
void sr(){

}
void sd(char* filename){

}
void p(){

}
void q(){

}
bool move(char* move){

}
void u(){

}
bool r(){

}
void s(char* filename){

}
bool l(char* filename){

}
