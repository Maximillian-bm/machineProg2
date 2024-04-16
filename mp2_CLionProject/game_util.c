#include <stdio.h>
#include "structs_util.c"

void printBord(struct Board*);
void findAgument(struct Board*, int);
int findMethod(struct Board*);
void setDeckToDefoult(struct Board*);
void ok(struct Board*);
void notOK(struct Board*);

void printBord(struct Board *board){
    printf("\n");
    if(board->playPhase){
        printf("C1   C2   C3   C4   C5   C6   C7\n\n");
        int i = 0;
        bool done = false;
        while(!done){
            done = true;
            int j = 0;
            while(j<7){
                char* card = cardAt(board->c[j], i);
                printf("%s   ", card);
                if(*card != ' '){
                    done = false;
                }
                j++;
            }
            printf("      ");

            if(i == 0){
                printf("%s F1", cardAtTop(board->f[0]));
            }else if(i == 2){
                printf("%s F2", cardAtTop(board->f[1]));
            }else if(i == 4){
                printf("%s F3", cardAtTop(board->f[2]));
            }else if(i == 6){
                printf("%s F4", cardAtTop(board->f[3]));
            }

            printf("\n");

            i++;
        }
        printf("LAST Command:%s\n", board->input);
        printf("Message:%s\n", board->output);
        printf("INPUT>");
    }else{
        printf("C1    C2    C3    C4    C5    C6    C7\n\n");
        int i = 0;
        while(i<8){
            int j = 0;
            while(j<7){
                if(j+(7*i)<52 && board->deck[j+(7*i)].created && !board->deck[j+(7*i)].hidden){
                    printf("%c%c    ", cardNumToChar(board->deck[j+(7*i)].num),board->deck[j+(7*i)].suit);
                }else if(j+(7*i)<52 && board->deck[j+(7*i)].created && board->deck[j+(7*i)].hidden){
                    printf("[]    ");
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
        printf("LAST Command:%s\n", board->input);
        printf("Message:%s\n", board->output);
        printf("INPUT>");
    }

}

void findAgument(struct Board *board, int aguNum){
// in the "input" find and return the agument.
// in the case that the agunum is 1, 5, 12 or 13, return the filename in "input"
// in the case that agunum is 3 return the number in "input"
// in the case of 9 return the whole string of "input"
// any returns should be a char* to a new char array
    int i = 0;
    while(true){
        if(board->input[i] == '\0'){
            break;
        }
        i++;
    }

    if(aguNum == 1 || aguNum == 3 || aguNum == 5){
        int j = 0;
        i--;
        while(j<i){
            board->aguement[j] = board->input[j+2];
            j++;
        }
    }else if(aguNum == 12 || aguNum == 13){
        int j = 0;
        while(j<i){
            board->aguement[j] = board->input[j+2];
            j++;
        }
    }else if(aguNum == 9){
        int j = 0;
        i++;
        while(j<i){
            board->aguement[j] = board->input[j];
            j++;
        }
    }
}
int findMethod(struct Board *board){
// return the number assotiated with the command saved in "input"
// if input is not valid return 0
    if(board->playPhase){
        switch(board->input[0]){
            case 'Q':
                if(board->input[1] == '\0'){
                    ok(board);
                    return 8;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'C':
                ok(board);
                return 9;
            case 'F':
                ok(board);
                return 9;
            case 'U':
                if(board->input[1] == '\0'){
                    ok(board);
                    return 10;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'R':
                if(board->input[1] == '\0'){
                    ok(board);
                    return 11;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'S':
                if(board->input[1] != '\0'){
                    ok(board);
                    return 12;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'L':
                if(board->input[1] != '\0'){
                    ok(board);
                    return 13;
                }else{
                    notOK(board);
                    return 0;
                }
        }
    }else{
        switch (board->input[1]) {
            case 'D':
                if(board->input[0] == 'L'){
                    ok(board);
                    return 1;
                }else if(board->input[0] == 'S'){
                    ok(board);
                    return 5;
                }else{
                    notOK(board);
                }
            case 'W':
                if(board->input[0] == 'S' && board->input[2] == '\0'){
                    ok(board);
                    return 2;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'I':
                if(board->input[0] == 'S'){
                    ok(board);
                    return 3;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'R':
                if(board->input[0] == 'S' && board->input[2] == '\0'){
                    ok(board);
                    return 4;
                }else{
                    notOK(board);
                    return 0;
                }
            case 'Q':
                if(board->input[0] == 'Q' && board->input[2] == '\0'){
                    ok(board);
                    return 6;
                }else{
                    notOK(board);
                    return 0;
                }
            case '\0':
                if(board->input[0] == 'P'){
                    ok(board);
                    return 7;
                }else{
                    notOK(board);
                    return 0;
                }
        }
    }
    notOK(board);
    return 0;
}

void setDeckToDefoult(struct Board* board){
    int i = 0;
    while(i<52){
        board->deck[i].created = true;
        board->deck[i].hidden = true;
        if(i<13){
            board->deck[i].suit = 'C';
        }else if(i<26){
            board->deck[i].suit = 'D';
        }else if(i<39){
            board->deck[i].suit = 'H';
        }else{
            board->deck[i].suit = 'S';
        }
        board->deck[i].num = (i%13)+1;

        i++;
    }
}

void ok(struct Board *board){
    board->output[0] = 'O';
    board->output[1] = 'K';
    board->output[2] = '\0';
}

void notOK(struct Board *board){
    board->output[0] = 'N';
    board->output[1] = 'O';
    board->output[2] = 'T';
    board->output[3] = ' ';
    board->output[4] = 'V';
    board->output[5] = 'A';
    board->output[6] = 'L';
    board->output[7] = 'I';
    board->output[8] = 'D';
    board->output[9] = '\0';
}