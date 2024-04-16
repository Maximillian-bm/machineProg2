#include <stdio.h>
#include "structs_util.c"

void printBord(struct Board*);
void findAgument(char*, char*, int);
int findMethod(char*, char*, bool);
void ok(char*);
void notOK(char*);

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

void findAgument(char *cmdStr, char *rtnStr, int aguNum){
// in the "input" find and return the agument.
// in the case that the agunum is 1, 5, 12 or 13, return the filename in "input"
// in the case that agunum is 3 return the number in "input"
// in the case of 9 return the whole string of "input"
// any returns should be a char* to a new char array
    int i = 0;
    while(true){
        if(cmdStr[i] == '\0'){
            break;
        }
        i++;
    }

    if(aguNum == 1 || aguNum == 3 || aguNum == 5){
        int j = 0;
        i--;
        while(j<i){
            rtnStr[j] = cmdStr[j+2];
            j++;
        }
    }else if(aguNum == 12 || aguNum == 13){
        int j = 0;
        while(j<i){
            rtnStr[j] = cmdStr[j+2];
            j++;
        }
    }else if(aguNum == 9){
        int j = 0;
        i++;
        while(j<i){
            rtnStr[j] = cmdStr[j];
            j++;
        }
    }
}

int findMethod(char *input, char *output, bool playPhase){
// return the number assotiated with the command saved in "input"
// if input is not valid return 0
    if(playPhase){
        switch(input[0]){
            case 'Q':
                if(input[1] == '\0'){
                    ok(output);
                    return 8;
                }else{
                    notOK(output);
                    return 0;
                }
            case 'C':
                ok(output);
                return 9;
            case 'F':
                ok(output);
                return 9;
            case 'U':
                if(input[1] == '\0'){
                    ok(output);
                    return 10;
                }else{
                    notOK(output);
                    return 0;
                }
            case 'R':
                if(input[1] == '\0'){
                    ok(output);
                    return 11;
                }else{
                    notOK(output);
                    return 0;
                }
            case 'S':
                if(input[1] != '\0'){
                    ok(output);
                    return 12;
                }else{
                    notOK(output);
                    return 0;
                }
            case 'L':
                if(input[1] != '\0'){
                    ok(output);
                    return 13;
                }else{
                    notOK(output);
                    return 0;
                }
        }
    }else{
        switch (input[1]) {
            case 'D':
                if(input[0] == 'L'){
                    ok(output);
                    return 1;
                }else if(input[0] == 'S'){
                    ok(output);
                    return 5;
                }else{
                    notOK(output);
                }
            case 'W':
                if(input[0] == 'S' && input[2] == '\0'){
                    ok(output);
                    return 2;
                }else{
                    notOK(output);
                    return 0;
                }
            case 'I':
                if(input[0] == 'S'){
                    ok(output);
                    return 3;
                }else{
                    notOK(output);
                    return 0;
                }
            case 'R':
                if(input[0] == 'S' && input[2] == '\0'){
                    ok(output);
                    return 4;
                }else{
                    notOK(output);
                    return 0;
                }
            case 'Q':
                if(input[0] == 'Q' && input[2] == '\0'){
                    ok(output);
                    return 6;
                }else{
                    notOK(output);
                    return 0;
                }
            case '\0':
                if(input[0] == 'P'){
                    ok(output);
                    return 7;
                }else{
                    notOK(output);
                    return 0;
                }
        }
    }
    notOK(output);
    return 0;
}

void ok(char* str){
    str[0] = 'O';
    str[1] = 'K';
    str[2] = '\0';
}

void notOK(char* str){
    str[0] = 'N';
    str[1] = 'O';
    str[2] = 'T';
    str[3] = ' ';
    str[4] = 'V';
    str[5] = 'A';
    str[6] = 'L';
    str[7] = 'I';
    str[8] = 'D';
    str[9] = '\0';
}