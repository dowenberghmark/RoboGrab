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
#include "robolib.h"

#define MAXLINE 4096 /*max text line length*/

int main(int argc, char **argv)
{
  if (argc != 3) {
    printf("Invalid number of arguments\n");
    exit(1);
  }

  int sockfd, server_port;
  char sendline[MAXLINE], recvline[MAXLINE], server_ip[25];
  struct sockaddr_in servaddr;

  strcpy(server_ip, argv[1]);
  server_port = atoi(argv[2]);

  //Create a socket for the client
  //If sockfd<0 there was an error in the creation of the socket
  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
    perror("Problem in creating the socket\n");
    exit(2);
  }
    
  //Creation of the socket
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr= inet_addr(server_ip);
  servaddr.sin_port =  htons(server_port); //convert to big-endian order
  
  //Connection of the client to the socket 
  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
    perror("Problem in connecting to the server\n");
    exit(3);
  }

  init_robot();
  
  move_right();
 
  move_left();
  
  strcpy(server_ip, inet_ntoa(servaddr.sin_addr));
  while (recv(sockfd, recvline, MAXLINE,0) > 0){
    Msg msg = getMsg(recvline);
    memset(recvline, 0, sizeof(recvline));
    printf("%s: %s\n", msg.type, msg.content);
    int size;
    char **dirs = getDirs(msg.content, &size);
    for (int i = 0; i < size; i++) {
      if (strcmp(dirs[i], UP) == 0)
	move_forward();
      else if (strcmp(dirs[i], DOWN) == 0)
	move_backward();
      else if (strcmp(dirs[i], LEFT) == 0)
	move_left();
      else if (strcmp(dirs[i], RIGHT) == 0)
	move_right();	 
    }
  }
  printf("Process terminated\n");
  uninit_robot();
  exit(0);
}
