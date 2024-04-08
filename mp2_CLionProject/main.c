#include <stdio.h>
#include <stdbool.h>

struct Card{
    bool hidden;
    char cardVal[2];
    struct Card* nextCard;
};

int main() {
    printf("Hello, World!\n");
    return 0;
}
