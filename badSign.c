#include <stdio.h>
#include "cursorCon.h"
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#include <sys/types.h>
#include <sys/wait.h>
#define rawNum 20

void badSign(){
    switch(fork()){
        case -1 :
            perror("fork()!");
        case 0 :
            gotoxy(25,0);
            printf("잘못 누르셨습니다\n");
            sleep(1);
        default :
            wait(NULL);
            gotoxy(25,0);
            printf("                       ");

    

    }
}
