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
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include "cursorCon.h"
#include "allfunction.h"
#include "badugi.h"
#define BACKLOG 100
#define MAXCLIENT 5
int main(){
    int sockfd, new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sin_size;
    int n,i;
    struct epoll_event ev, *client_list;
    int efd;
    char buf[256];
    struct custinfo {
    	int socksd;
    } cust[MAXCLIENT]={ -1, -1, -1,-1,-1 };
    int count=0;
    //load사용자데이타
    //loadmapdata();
    //로그인();
    nclear();
    mapSetUp();
    gotoxy(8,4);
    printf("===============\n");
    printf("|ID :         =\n");
    printf("|PW :")

    

    client_list = (struct epoll_event *)malloc(sizeof(*client_list) * MAXCLIENT);
	if((efd=epoll_create(100))<0){
		perror("epoll_create");
		return 1;
	}

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
       perror("socket");
       exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(60000);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(server_addr.sin_zero), '\0', 8);
    if(bind(sockfd, (struct sockaddr *)&server_addr,
		   sizeof(struct sockaddr))==-1) {
       perror("bind");
       exit(1);
    }
    if(listen(sockfd, BACKLOG) == -1) {
       perror("listen");
       exit(1);
   }
    ev.events =EPOLLIN;
    ev.data.fd= sockfd;
    epoll_ctl(efd,EPOLL_CTL_ADD,sockfd,&ev); //epoll 본인 추가
    while(1){
        if((n= epoll_wait(efd,client_list,MAXCLIENT,-1))==-1){
			perror("epoll_wait");}
        for (i = 0;i < n; i++){
            if (client_list[i].data.fd == sockfd) {
                //클라이언트 입장 시 해당 구조 진행
                sin_size=sizeof(struct sockaddr_in);
                new_fd = accept(sockfd, (struct sockaddr *)&client_addr, & sin_size);
                //커넥션 연결시 
				ev.data.fd=new_fd;
				epoll_ctl(efd,EPOLL_CTL_ADD,new_fd,&ev);
                if(count<MAXCLIENT)
                	cust[count++].socksd=new_fd;
            }  else {
                int readn = read(client_list[i].data.fd, buf, 255);
                buf[readn]='\0';
                if(readn <= 0){
					epoll_ctl(efd,EPOLL_CTL_DEL,client_list[i].data.fd,client_list);
			                    close(client_list[i].data.fd);
                    printf("Close fd\n");
                } else {
                    //printf("read data %s\n", buf);
                    int j;
                    for(j=0; j<MAXCLIENT; j++) {
                    	if(cust[j].socksd==-1) continue;
                    	if(cust[j].socksd==client_list[i].data.fd) continue;
                    	write(cust[j].socksd, buf, readn);
                    }

                }
            }   // else-end
         } // for-end
    }
    return 0;
}