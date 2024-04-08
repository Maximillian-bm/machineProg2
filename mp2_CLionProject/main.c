#include <stdio.h>
#include <stdbool.h>

struct Card{
    bool hidden;
    char suit;
    int num;
    struct Card* prevCard;
    struct Card* nextCard;
};

int main() {
    printf("Hello, World!\n");
    return 0;
}
