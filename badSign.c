#include <stdio.h>
#include "cursorCon.h"
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#define rawNum 20

void * fe(void * aa){
    gotoxy(25,0);
            pthread_detach(pthread_self());
            printf("잘못 누르셨습니다\n");
            sleep(1);
    gotoxy(25,0);
            printf("                 ");
            pthread_exit(NULL);
}
void badSign(){
    pthread_t bad;
    pthread_create(&bad,NULL,fe,NULL);
}
