#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>

using namespace std;

int server_init(int port_nr);

int main(int argc, char *argv[])
{
  int port_nr = 0;
  char * address;

  
  switch (argc) {
    case 2: {
      port_nr = atoi(argv[2]);
      address = argv[1];
      server_init(port_nr);
      break;
    }
    default:
      assert(argc != 3);
      printf("Wrong number of arguments, need port_nr , is %d \n", argc - 1);
      exit(EXIT_FAILURE);
      break;
  }

  printf("%s, %d\n", address, port_nr );
  return 0;
}


int server_init(int port_nr){
  int client, server;
  int buffer_size = 1024;
  char buffer[buffer_size];
  char * content = (char*)"CONNECT";

  struct sockaddr_in server_addr;
  struct sockaddr * addr_pointer = (struct sockaddr *) & server_addr; 
  socklen_t size = sizeof(server_addr);
  
  client = socket(AF_INET, SOCK_STREAM, 0 );
  if ( client   < 0  ){
      printf("\nError setting up socket\n");
      exit(EXIT_FAILURE);
    }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);
  server_addr.sin_port = htons(port_nr);

  int fail;
  
  if( ( (fail = bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0 ) ){
    printf("\nFailed to bind port: %d\n", fail);
    exit(EXIT_FAILURE);
  }
  while(1){
    printf("%s\n","start listening" );
    listen(client, 1);
  
    if( ((server = accept(client, addr_pointer, &size)) < 0 ))
      printf("Error establishing connection to client\n");
 
    printf("connected with a client waiting for message\n");

    recv(server, buffer, buffer_size,0);
    printf("Got a message %s\n", buffer);
    if (!strcmp(buffer, content)){
    
      sprintf(buffer, "ACCEPTED");
    
      send(server, buffer, buffer_size, 0);
    }
    else{

    
      sprintf(buffer, "REJECTED");
    
      send(server, buffer, buffer_size, 0);
    
    }

    printf("%s\n","Closed connection with client" );
  }
  close(client);
  
  return 0;
}
