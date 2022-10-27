#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "cursorCon.h"

void mapSetUp();
void unitSetUp();

int main(){
    pid_t newChild;
    switch((newChild=fork())){
        case -1 :
            perror("fork()");
            exit(1);
            break;
        case 0 :
            mapSetUp();
            break;
        default :
            unitSetUp();
            waitpid(newChild,NULL,0);
        }

    return 0;
}