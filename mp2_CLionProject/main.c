#include <string.h>
#include "commands.c"
#include "game_util.c"

int main() {

    //tests for findAgument
    printf("findAgument tests: \n");
    char *cmdStr = "LD1";
    char rtnStr[21];
    findAgument(cmdStr, rtnStr, 1);
    if (rtnStr[0] == '1' ){
        printf("Load deck test passed\n");
    } else {
        printf("Load deck test failed\n");
    }

    cmdStr = "SI20";
    findAgument(cmdStr, rtnStr, 3);
    if (rtnStr[0] == '2' && rtnStr[1] == '0') {
        printf("Split test passed\n");
    }else {
        printf("Split test failed\n");
    }

    cmdStr = "SD1";
    findAgument(cmdStr, rtnStr, 5);
    if (rtnStr[0] == '1'){
        printf("Safe file test passed\n");
    } else {
        printf("Safe file test failed\n");
    }

    cmdStr = "C1:AH->F1";
    findAgument(cmdStr, rtnStr, 9);
    if (rtnStr[0] == 'C' && rtnStr[1] == '1' && rtnStr[2] == ':' && rtnStr[3] == 'A' && rtnStr[4] == 'H' && rtnStr[5] == '-' && rtnStr[6] == '>' && rtnStr[7] == 'F' && rtnStr[8] == '1'){
        printf("Move test passed\n\n");
    } else {
        printf("Move test failed\n\n");
    }


    // Tests for findMethod
    printf("findMethod test: \n");
    char *input = "LD";
    bool playPhase = false;
    if (findMethod(input, playPhase) == 1){
        printf("Load deck test passed\n");
    } else {
        printf("Load deck test failed\n");
    }

    input = "SW";
    if (findMethod(input, playPhase) == 2){
        printf("Display cards test passed\n");
    } else {
        printf("Display cards test failed\n");
    }

    input = "SI";
    if (findMethod(input, playPhase) == 3){
        printf("Split test passed\n");
    } else{
        printf("Split test failed\n");
    }

    input = "SR";
    if (findMethod(input, playPhase) == 4){
        printf("Shuffle test passed\n");
    } else {
        printf("Shuffle test failed\n");
    }

    input = "SD";
    if (findMethod(input, playPhase) == 5){
        printf("Safe deck test passed\n");
    } else {
        printf("Safe deck test failed\n");
    }

    input = "P";
    if (findMethod(input, playPhase) == 7){
        printf("Play Phase test passed\n");
    } else {
        printf("Play phase test failed\n");
    }

    input = "KT";
    if (findMethod(input, playPhase) == 0) {
        printf("Startphase wrong input test passed\n");
    } else {
        printf("Startphase wrong input test failed\n");
    }

    playPhase = true;
    input = "QQ";
    if (findMethod(input, playPhase) == 6){
        printf("Exit game test passed\n");
    } else {
        printf("Exit game test failed\n");
    }

    input = "Q";
    if (findMethod(input, playPhase) == 8) {
        printf("Start phase test passed\n");
    } else {
        printf("Start phase test failed\n");
    }

    input = "C";
    if (findMethod(input, playPhase) == 9) {
        printf("Move test passed\n");
    } else {
        printf("Move test failed\n");
    }

    input = "F";
    if (findMethod(input, playPhase) == 9) {
        printf("Move test passed\n");
    } else {
        printf("Move test failed\n");
    }

    input = "U";
    if (findMethod(input, playPhase) == 10) {
        printf("Undo test passed\n");
    } else {
        printf("Undo test failed\n");
    }

    input = "R";
    if (findMethod(input, playPhase) == 11) {
        printf("Redo test passed\n");
    } else {
        printf("Redo test failed\n");
    }

    input = "S";
    if (findMethod(input, playPhase) == 12) {
        printf("Safe state test passed\n");
    } else {
        printf("Safe state test failed\n");
    }

    input = "L";
    if (findMethod(input, playPhase) == 13) {
        printf("Load state test passed\n");
    } else {
        printf("Load state test failed\n");
    }

    input = "KT";
    if (findMethod(input, playPhase) == 0) {
        printf("Playphase wrong input test passed\n\n");
    } else {
        printf("Playphase wrong input test failed\n\n");
    }

    // Tests for structs_util
    printf("structs_util tests: \n");
    struct Card card = {.num = 7, .suit = 'H', .hidden = false, .nextCard = NULL};
    char cardPointer[3];
    char expectedCard[] = "7H";

    cardAt(&card, 0, cardPointer);
    if (strcmp(cardPointer, expectedCard) == 0) {
        printf("CardAt test passed\n");
    } else {
        printf("CardAt test failed\n");
    }

    card.hidden = true;
    char expectedHiddenCard[] = "[]";

    cardAt(&card, 0, cardPointer);
    if (strcmp(cardPointer, expectedHiddenCard) == 0) {
        printf("CardAt test passed\n");
    } else {
        printf("CardAt test failed\n");
    }

    //negative test, should give an error
    cardAt(&card, -1, cardPointer);

    cardAtTop(&card, cardPointer);
    if (strcmp(cardPointer, expectedCard) == 0) {
        printf("CardAtTop test passed\n");
    } else {
        printf("CardAtTop test failed\n");
    }


    bool test_passed = true;

    for (int i = 1; i <= 13; i++) {
        char result = cardNumToChar(i);
        switch (result) {
            case 'A':
            case 'T':
            case 'J':
            case 'Q':
            case 'K':
                break;
            default:
                if (result != (char)(i + '0')) {
                    test_passed = false;
                    printf("Test failed for value %d\n", i);
                }
        }
    }

    if (test_passed) {
        printf("cardNumtoChar test passed\n");
    } else {
        printf("cardNumtoChar test failed\n");
    }

    for (int i = 1; i <= 13; i++) {
        int result;
        switch (i) {
            case 1:
                result = cardCharToNum('A');
                break;
            case 10:
                result = cardCharToNum('T');
                break;
            case 11:
                result = cardCharToNum('J');
                break;
            case 12:
                result = cardCharToNum('Q');
                break;
            case 13:
                result = cardCharToNum('K');
                break;
            default:
                result = cardCharToNum(cardNumToChar(i));
        }

        if (result != i) {
            test_passed = false;
            printf("cardCharToNum test failed for value %d\n", i);
        }
    }

    if (test_passed) {
        printf("cardChartoNum test passed\n");
    } else {
        printf("cardChartoNum test failed\n");
    }



    return 1;
}