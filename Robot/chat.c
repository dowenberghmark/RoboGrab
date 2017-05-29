#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <wait.h>
#include <unistd.h>
#include "protocol.h"

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

void signHandler(int signum) {
  //printf("Terminated child: %d\n", signum);
  FILE *f = fopen("log.txt", "w");
  fprintf(f, "Terminated child: %d\n", signum);
  fclose(f);
  int wstatus;
  while(waitpid(-1, &wstatus, WNOHANG) > 0) {
  }
}


int main (int argc, char **argv)
{
  int listenfd, connfd, n, sockfd;
  pid_t childpid;
  socklen_t clilen;
  char buf[MAXLINE], sendline[MAXLINE], recvline[MAXLINE];
  struct sockaddr_in cliaddr, servaddr;
  
  /*--Server--*/
  if (argc == 1) {
    //creation of the socket
    listenfd = socket (AF_INET, SOCK_STREAM, 0);
    
    //preparation of the socket address 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
    listen (listenfd, LISTENQ); 
    printf("%s\n","Chat room opened...waiting for others.");
    
    signal(SIGCHLD, signHandler);
    
    for ( ; ; ) {		
      clilen = sizeof(cliaddr);
      connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
      //Listen
      if (fork() == 0) {  
	char client[25];
	strcpy(client, inet_ntoa(cliaddr.sin_addr));
	printf("%s joined room.\n", client);
	while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
	  printf("%s: %s\n", client, buf);
	  memset(buf, 0, sizeof(buf));
	}
	if (n < 0) {
	  perror("Read error"); 
	  exit(1);
	}
	exit(0);
      }
      //Talk
      else if (fork() == 0) {
	while (fgets(sendline, MAXLINE, stdin) != NULL) {	
	  send(connfd, sendline, strlen(sendline), 0);
	  memset(sendline, 0, sizeof(sendline));
	}
      }
      close(connfd);
    }
    //close listening socket
    close (listenfd); 
  }
  
  /*--Client--*/
  else  if (argc == 2) {
    signal(SIGCHLD, signHandler);
    //Create a socket for the client
    //If sockfd<0 there was an error in the creation of the socket
    if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
      perror("Problem in creating the socket");
      exit(2);
    }
    
   //Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr= inet_addr(argv[1]);
    servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
    
    //Connection of the client to the socket 
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
      perror("Problem in connecting to the server");
      exit(3);
    }
    //Listen
    if (fork() == 0) {
      char server[25];
      strcpy(server, inet_ntoa(servaddr.sin_addr));
      while (recv(sockfd, recvline, MAXLINE,0) > 0){
	//printf("%s: %s\n", server, recvline);
	Msg msg = getMsg(recvline);
	printf("%s: %s %s\n", server, msg.type, msg.content);
        memset(recvline, 0, sizeof(recvline));
      }
    }
    //Talk
    else {
      while (fgets(sendline, MAXLINE, stdin) != NULL) {	
	send(sockfd, sendline, strlen(sendline), 0);
	memset(sendline, 0, sizeof(sendline));
      }
    }
  }
  exit(0);	
}
