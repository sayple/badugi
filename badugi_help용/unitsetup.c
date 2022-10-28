#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#include "cursorCon.h"
#include "allfunction.h"
#define USER '1'
#define rawNum 20

void unitSetUp(int fd, char* map){
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
    char a;
    char oldA;
    while(1){
        //데이터 저장.
        //이기는거 확인
        //3x3여부
        scanf("%c",&a);
        gotoxy(x,2*y+1);
            switch(a){
                case 'e':
                    if(x>=1)
                        x-=1;
                    fflush(stdin);
                    oldA=a;
                    break;
                case 's':
                    if(y>=0)
                        y-=1;
                    fflush(stdin);
                    oldA=a;
                    break;
                case 'd':
                    if(x+1<20)
                        x+=1;
                    fflush(stdin);
                    oldA=a;
                    break;
                case 'f':
                    if(y+1<19)
                        y+=1;
                    fflush(stdin);
                    oldA=a;
                    break;
                case '\n':
                    if(checkCanDo(x,y,map)==0){
                        badSign();
                        break;
                        }
                    map[y*x+y+1] = USER;
                    switch(oldA){
                        case 'e':
                        gotoxy(x+1,2*y+1);
                        if(USER=='1')
                            printf("●");
                        else
                            printf("○");  
                        break;
                        case 's':
                        gotoxy(x,2*y+3);
                        if(USER=='1')
                            printf("●");
                        else
                            printf("○");  
                        break;
                        case 'd':
                        gotoxy(x-1,2*y+1);
                        if(USER=='1')
                            printf("●");
                        else
                            printf("○");   
                        break;

                        case 'f':
                        gotoxy(x,2*y-1);
                        if(USER=='1')
                            printf("●");
                        else
                            printf("○"); 
                        break;
                    }
                    break;
                    
                default :
                    badSign();
                    break;
                    
            }
    }
    if(ioctl(0, TCSETAF, &oldtbuf)==-1) {perror("ioctl"); exit(1);}
}
