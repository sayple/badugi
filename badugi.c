#include <stdio.h>
#include <stdlib.h>
#include "cursorCon.h"
#include <stdio.h>
#include <unistd.h>
#include <termio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "badugi.h"
#include "array.h"
#define rawNum 17

void * fe(void * aa){ //사용 이후 사라지도록 pthread 실행
    gotoxy(25,0);
            pthread_detach(pthread_self());
            printf("잘못 누르셨습니다\n");
            sleep(1);
    gotoxy(25,0);
            printf("                 ");
            pthread_exit(NULL);
}
void badSign(){ //문제 발생 시 경고 발생시그널
    pthread_t bad;
    pthread_create(&bad,NULL,fe,NULL);
}

void mapSetUp(){ //기본 맵형성 단순 디자인용, 실제로 돌의 데이터로만 적용
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
void unitSetUp(int USER, char* map){  //USER를 통해 흑백 설정, 
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

int createUserList(LPARRAY* userFullList){
    int nErr = arrayCreate(&userFullList);
    if (ERR_ARRAY_OK != nErr) {
        return nErr;
    }
    USERLIST Temp = (USERLIST)malloc(sizeof(userInfo));
    strcpy(Temp->ID,"1"); strcpy(Temp->PW,"1");
    Temp->admin = 0;Temp->winLose[0] = 0; Temp->winLose[1] = 0;
    arrayAdd(userFullList,(const LPDATA) Temp);
    strcpy(Temp->ID,"2"); strcpy(Temp->PW,"2");
    arrayAdd(userFullList,(const LPDATA) Temp);
    strcpy(Temp->ID,"admin"); strcpy(Temp->PW,"1234");
    Temp->admin = 1;
    arrayAdd(userFullList,(const LPDATA) Temp);
    free(Temp);
}
void addUserList(LPARRAY* userFullList){
    USERLIST Temp = (USERLIST)malloc(sizeof(userInfo));
    printf("ID : ");
	scanf("%s",Temp->ID);
	printf("PW : ");
	scanf("%s",Temp->PW);
    Temp->admin = 0;
	Temp->winLose[0] = 0; Temp->winLose[1] = 0;
	arrayAdd(userFullList,(const LPDATA) Temp);
	free(Temp);
}
int loginGame(char* id, char* pw,LPARRAY* userFullList){
    USERLIST Temp = (USERLIST)malloc(sizeof(userInfo));
    int i=0;
	for(i=0;i<arraySize(userFullList);i++){
	    arrayGetAt(userFullList,i, (LPDATA*)&Temp);
		if(strcmp(Temp->ID,id)==0){
            if(strcmp(Temp->PW,pw)==0) return 1;
		}
	}
    return 0;
}
int createMapList(LPARRAY* mapFullList){
    int nErr = arrayCreate(&mapFullList);
    if (ERR_ARRAY_OK != nErr) {
        return nErr;
    }
    MAPLIST Temp = (MAPLIST)malloc(sizeof(mapInfo));
    for(int i=0;i<19;i++){
        for(int j=0;j<19;j++){
            Temp->map[i][j] =0;
        }
    }
    Temp->chatting_Use =0;
    strcpy(Temp->chatting,"0");
    strcpy(Temp->userID[0],""); strcpy(Temp->userID[1],"");
    strcpy(Temp->result,"");
    arrayAdd(mapFullList,(const LPDATA) Temp);
    free(Temp);
}
void initMapInfo(MAPLIST maps,char* USR1, char* USR2){
    for(int i=0;i<19;i++){
        for(int j=0;j<19;j++){
            maps->map[i][j] =0;
        }
    }
    maps->chatting_Use =0;
    strcpy(maps->chatting,"0");
    strcpy(maps->userID[0],USR1); strcpy(maps->userID[1],USR2);
    strcpy(maps->result,"");
    return;
}
void getView(MAPLIST oldGibo,MAPLIST nowGibo,int first){
    for(int i=0;i<19;i++){
        for(int j=0;j<19;j++){
            if(oldGibo->map[i][j]!=nowGibo->map[i][j])
            gotoxy(i,2*j);
            if(first==0) printf("●");
            else printf("○");
        }
    }
}
char getEnermy(MAPLIST gibo){ //우측 상단 뷰어용
    gotoxy(5,25); ////////////////////////
    printf("=====================\n");
    printf("%s vs %s\n",gibo->userID[0],gibo->userID[1]);
    printf("=====================\n");
}
void setResult(MAPLIST gibo,char* USR1){
    sprintf(gibo->result,"winner : %s\n",USR1);
}

int checkCando(int x,int y, char** mapNow){
    //삼삼 이런 기타 등등도 집어넣어야돼
    if(mapNow[x][y]==0) return 1;
    else 0;
}