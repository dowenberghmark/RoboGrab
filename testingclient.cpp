#include <stdio.h>
#include <string>
//#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

int main(int argc, char *argv[])
{
  
  int client;
  int portNum = 1500; // NOTE that the port number is same for both client and server
  int buffer_size = 1024;
  char buffer[buffer_size];
  char* ip = "127.0.0.1";

  struct sockaddr_in server_addr;

  client = socket(AF_INET, SOCK_STREAM, 0);

  if (client < 0) 
  {
    printf( "\nError establishing socket...\n");
    exit(1);
  }

 
  printf("\n=> Socket client has been created...\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(portNum);
  inet_pton(AF_INET, ip ,&server_addr.sin_addr);
  
  if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
    
  sprintf(buffer, argv[1]);
  send(client, buffer, buffer_size, 0);
  recv(client, buffer, buffer_size, 0);
  printf("%s\n", buffer );
  close(client);
  return 0;
}
