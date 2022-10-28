#include <stdio.h>
#include <stdlib.h>
#include "cursorCon.h"
#define rawNum 17
void mapSetUp(){
    nclear();                                    
    printf("┌");
    for (int i = 0; i < rawNum; i++)
        printf("─┬");
    printf("─┐\n");

    for (int i = 0; i < rawNum; i++) {
        printf("├");
        for (int j = 0; j < rawNum; j++)
            printf("─┼");
        printf("─┤\n");
    }

    printf("└");
    for (int i = 0; i < rawNum; i++)
        printf("─┴");
    printf("─┘");
    printf("\n\n");
    printf("'e' : 윗측 이동, 'd' : 아래 이동, 's' : 좌측 이동, 'ㄹ' : 우측이동 \n");
}