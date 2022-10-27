#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "cursorCon.h"
#include "allfunction.h"
int main(){
    int sockfd, new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sin_size;
    int yes = 1;
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
       perror("socket");
       exit(1);
    }
    printf("sockfd : %d\n",sockfd);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(60000);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(server_addr.sin_zero), '\0', 8);
    if(bind(sockfd, (struct sockaddr *)&server_addr,
		   sizeof(struct sockaddr))==-1) {
       perror("bind");
       exit(1);
    }






    pid_t newChild;
    char map[361]={0};
    //getMap;(이전 파일정보)
    loginView();

    switch((newChild=fork())){
        case -1 :
            perror("fork()");
            exit(1);
            break;
        case 0 :
            mapSetUp();
            break;
        default :
            unitSetUp(map);
            waitpid(newChild,NULL,0);
        }

    return 0;
}