#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_TYPE_MAX_LEN 25
#define MSG_CONTENT_MAX_LEN 500
#define DIR_MAX_LEN 10
#define DIR_MAX_NO 500
#define SERVER_IP "127.0.0.1"

//Message Types:
#define DIR "DIR"
#define INVALID "INVALID"

//Direction Types:
#define LEFT "left"
#define RIGHT "right"
#define UP "up"
#define DOWN "down"

typedef struct {
  char *type;
  char *content; 
} Msg;

char *getMsgType(char *word);

Msg getMsg(char *str);

char *getDir(char * word);

char **getDirs(char *str, int *size);
