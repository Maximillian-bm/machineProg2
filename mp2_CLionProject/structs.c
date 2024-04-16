#include <stdbool.h>

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