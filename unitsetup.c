#include <stdio.h>
#include "cursorCon.h"
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>

#define rawNum 20

void unitSetUp(){
    struct termio tbuf, oldtbuf;
    if(ioctl(0, TCGETA, &tbuf) == -1) { // 현재터미널모드
        perror("ioctl");    exit(1);
    }
    oldtbuf=tbuf;
    tbuf.c_lflag &= ~ECHO;
    tbuf.c_lflag&=~ICANON;
    tbuf.c_cc[VMIN] =1;
    tbuf.c_cc[VTIME]=0;
    if(ioctl(0, TCSETAF, &tbuf)==-1) {
        perror("ioctl"); exit(1);
    }   
                                           
    int x =0;
    int y =0;
    nclear();
    while(1){
		int a;
        a = getchar();
        gotoxy(x,2*y+1);
            switch(a){
                case 'e':
                    if(x>=1)
                        x-=1;
                    break;
                case 's':
                    if(y>=2)
                        y-=1;
                    break;
                case 'd':
                    if(x+1<22)
                        x+=1;
                    break;
                case 'f':
                    if(y+1<22)
                        y+=1;
                    break;
                case '\n':
                    //if(checkCanDo())
                    gotoxy(x,2*y-1);
                    printf("●");
                    break;
                    
                default :
                    badSign();
                    break;
                    
            }
    }
    if(ioctl(0, TCSETAF, &oldtbuf)==-1) {perror("ioctl"); exit(1);}
}
