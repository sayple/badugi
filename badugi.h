#ifndef _BADUGI_H
#define _BADUGI_H

typedef struct{
    char ID[20];
    char PW[20];
    int winLose[2];
    int admin;
} userInfo, *USERLIST;

typedef struct{
    char map[19][19];
    int chatting_Use;
    char chatting[80];
    char userID[2][20];
    char result[60];
}mapInfo, *MAPLIST;
void badSign();
void mapSetUp();
void unitSetUp(int USER, char* map);
int createUserList(LPARRAY* userFullList);
int loginGame(char* id, char* pw,LPARRAY* userFullList);
void addUserList(LPARRAY* userFullList);
int createMapList(LPARRAY* mapFullList);
void initMapInfo(mapInfo* maps,char* USR1, char*);
void getView(MAPLIST oldGibo,MAPLIST nowGibo,int first);
char getEnermy(MAPLIST gibo);
void setResult(MAPLIST gibo,char* USR1);
int checkCando(int x,int y, char** mapNow);

#endif


