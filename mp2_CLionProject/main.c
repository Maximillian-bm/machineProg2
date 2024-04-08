#include <stdio.h>
#include <stdbool.h>

struct Card{
    bool hidden;
    char suit;
    int num;
    struct Card* prevCard;
    struct Card* nextCard;
};

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

bool ld(char[]);
bool sw();
bool sl();
void sr();
void sd(char[]);
void qq();
void p();
void q();
bool move(char[]);
void u();
bool r();
void s();
bool l();

void printBord();

int main() {
    char input[50];
    while(true){
        printBord();
        scanf("%s", input);
    }
    return 0;
}
