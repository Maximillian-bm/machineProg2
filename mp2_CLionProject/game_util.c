
void findAgument(char*, char*, int);
int findMethod(char*, char*, bool);
void ok(char*);
void notOK(char*);
void message(char*, int);

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
                    return 8;
                }else{
                    return 0;
                }
            case 'C':
                return 9;
            case 'F':
                return 9;
            case 'U':
                if(input[1] == '\0'){
                    return 10;
                }else{
                    return 0;
                }
            case 'R':
                if(input[1] == '\0'){
                    return 11;
                }else{
                    return 0;
                }
            case 'S':
                if(input[1] != '\0'){
                    return 12;
                }else{
                    return 0;
                }
            case 'L':
                if(input[1] != '\0'){
                    return 13;
                }else{
                    return 0;
                }
        }
    }else{
        switch (input[1]) {
            case 'D':
                if(input[0] == 'L'){
                    return 1;
                }else if(input[0] == 'S'){
                    return 5;
                }else{
                    return 0;
                }
            case 'W':
                if(input[0] == 'S' && input[2] == '\0'){
                    return 2;
                }else{
                    return 0;
                }
            case 'I':
                if(input[0] == 'S'){
                    return 3;
                }else{
                    return 0;
                }
            case 'R':
                if(input[0] == 'S' && input[2] == '\0'){
                    return 4;
                }else{
                    return 0;
                }
            case 'Q':
                if(input[0] == 'Q' && input[2] == '\0'){
                    return 6;
                }else{
                    return 0;
                }
            case '\0':
                if(input[0] == 'P'){
                    return 7;
                }else{
                    return 0;
                }
        }
    }
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

void message(char* str, int i){
    switch (i) {
        case -1:
            str[0] = 'N';
            str[1] = 'O';
            str[2] = 'T';
            str[3] = ' ';
            str[4] = 'I';
            str[5] = 'M';
            str[6] = 'P';
            str[7] = 'L';
            str[8] = 'E';
            str[9] = 'M';
            str[10] = 'E';
            str[11] = 'N';
            str[12] = 'T';
            str[13] = 'E';
            str[14] = 'D';
            str[15] = '\0';
            break;
        case 0:
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
            break;
        case 1:
            str[0] = 'O';
            str[1] = 'K';
            str[2] = '\0';
            break;
        case 2:
            str[0] = 'U';
            str[1] = 'N';
            str[2] = 'A';
            str[3] = 'B';
            str[4] = 'L';
            str[5] = 'E';
            str[6] = ' ';
            str[7] = 'T';
            str[8] = 'O';
            str[9] = ' ';
            str[10] = 'F';
            str[11] = 'I';
            str[12] = 'N';
            str[13] = 'D';
            str[14] = ' ';
            str[15] = 'F';
            str[16] = 'I';
            str[17] = 'L';
            str[18] = 'E';
            str[19] = '\0';
            break;
        case 3:
            str[0] = 'N';
            str[1] = 'O';
            str[2] = ' ';
            str[3] = 'D';
            str[4] = 'E';
            str[5] = 'C';
            str[6] = 'K';
            str[7] = ' ';
            str[8] = 'L';
            str[9] = 'O';
            str[10] = 'A';
            str[11] = 'D';
            str[12] = 'E';
            str[13] = 'D';
            str[14] = '\0';
            break;
        case 4:
            str[0] = 'N';
            str[1] = 'O';
            str[2] = 'T';
            str[3] = ' ';
            str[4] = 'A';
            str[5] = ' ';
            str[6] = 'V';
            str[7] = 'A';
            str[8] = 'L';
            str[9] = 'I';
            str[10] = 'D';
            str[11] = ' ';
            str[12] = 'M';
            str[13] = 'O';
            str[14] = 'V';
            str[15] = 'E';
            str[16] = '\0';
            break;
    }
}