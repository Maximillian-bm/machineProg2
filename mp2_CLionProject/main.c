#include "commands.c"
#include "game_util.c"

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

        int method = findMethod(&board.input, &board.output, board.playPhase);

        switch (method) {
            case 1:
                findAgument(&board.input, &board.aguement,1);
                if(!ld(&board)){
                    notOK(board.output);
                }
                break;
            case 2:
                if(!sw(&board)){
                    notOK(board.output);
                }
                break;
            case 3:
                findAgument(&board.input, &board.aguement,3);
                if(!si(&board)){
                    notOK(board.output);
                }
                break;
            case 4:
                if(!sr(&board)){
                    notOK(board.output);
                }
                break;
            case 5:
                findAgument(&board.input, &board.aguement,5);
                if(!sd(&board)){
                    notOK(board.output);
                }
                break;
            case 6:
                exit = true;
                break;
            case 7:
                if(!p(&board)){
                    notOK(board.output);
                }
                break;
            case 8:
                if(!q(&board)){
                    notOK(board.output);
                }
                break;
            case 9:
                findAgument(&board.input, &board.aguement,9);
                if(!move(&board)){
                    notOK(board.output);
                }
                break;
            case 10:
                if(!u(&board)){
                    notOK(board.output);
                }
                break;
            case 11:
                if(!r(&board)){
                    notOK(board.output);
                }
                break;
            case 12:
                findAgument(&board.input, &board.aguement,12);
                if(!s(&board)){
                    notOK(board.output);
                };
                break;
            case 13:
                findAgument(&board.input, &board.aguement,13);
                if(!l(&board)){
                    notOK(board.output);
                }
                break;
        }
    }
    return 0;
}