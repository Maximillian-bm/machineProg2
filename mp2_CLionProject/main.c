#include "commands.c"

int main() {

    int c;
    struct Board board;
    int i = 0;
    while(i<52){
        board.deck[i].created = false;
        i++;
    }

    board.input[0] = '\0';

    board.output[0] = '\0';

    board.playPhase = false;

    bool exit = false;

    while(!exit) {
        printBord(&board);

        scanf("%20[^\n]", board.input);

        while ((c = getchar()) != '\n' && c != EOF);

        int method = findMethod(&board);

        switch (method) {
            case 1:
                findAgument(&board.input, &board.aguement,1);
                ld(&board);
                break;
            case 2:
                sw(&board);
                break;
            case 3:
                findAgument(&board.input, &board.aguement,3);
                si(&board);
                break;
            case 4:
                sr(&board);
                break;
            case 5:
                findAgument(&board.input, &board.aguement,5);
                sd(&board);
                break;
            case 6:
                exit = true;
                break;
            case 7:
                p(&board);
                break;
            case 8:
                q(&board);
                break;
            case 9:
                findAgument(&board.input, &board.aguement,9);
                move(&board);
                break;
            case 10:
                u(&board);
                break;
            case 11:
                r(&board);
                break;
            case 12:
                findAgument(&board.input, &board.aguement,12);
                s(&board);
                break;
            case 13:
                findAgument(&board.input, &board.aguement,13);
                l(&board);
                break;
        }
    }
    return 0;
}