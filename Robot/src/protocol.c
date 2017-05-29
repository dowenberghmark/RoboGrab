#include "protocol.h"

/* List of Protocols */ 
char p_list[][MSG_TYPE_MAX_LEN] = {DIR};

/* List of Directions */
char d_list[][DIR_MAX_LEN] = {LEFT, RIGHT, UP, DOWN};

char *getMsgType(char *word) {
  int i, size = sizeof(p_list) / MSG_TYPE_MAX_LEN;
  for (i = 0; i < size; i++) {
    if (strcmp(word, p_list[i]) == 0) {
      return word;
    }
  }
  return INVALID;
}

Msg getMsg(char *str) {
  Msg msg;
  int i = 0, j = 0;
  msg.type = (char *)malloc(MSG_TYPE_MAX_LEN);
  msg.content = (char *)malloc(MSG_CONTENT_MAX_LEN);
  
  while (str[i] != ':' && str[i] != '\0' && str[i] != '\n' && i < MSG_TYPE_MAX_LEN) {
    msg.type[i] = str[i];
    i++;
  }
  msg.type[i] = '\0';

  if (i >= MSG_TYPE_MAX_LEN) {
    msg.type = INVALID;
    strcpy(msg.content, "1");
    return msg;
  }

  strcpy(msg.type, getMsgType(msg.type));
  
  if (str[i] != ':' || strcmp(msg.type, INVALID) == 0) {
    strcpy(msg.content, "");
    return msg;
  }
  
  i++;
  while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n' && j < MSG_CONTENT_MAX_LEN) {
    msg.content[j] = str[i];
    i++;
    j++;
  }
  msg.content[j] = '\0';
  
  if (j >= MSG_CONTENT_MAX_LEN || (str[i] != '\0' && str[i] != '\n')) {
    msg.type = INVALID;
    strcpy(msg.content, "2");
    return msg;
  }
  
  return msg;
}

char *getDir(char *word) {
  int i, size = sizeof(d_list) / DIR_MAX_LEN;
  for (i = 0; i < size; i++) {
    if (strcmp(word, d_list[i]) == 0) {
      return word;
    }
  }
  return INVALID;
}

char **getDirs(char *str, int *size) {
  int i = 0, j = 0;
  (*size) = 0;
  char **dirs = (char **)malloc(sizeof(char *));
  char *word = (char *)malloc(50);
  memset(word, 0, sizeof(word));
  while (str[i] != '\0') {
    if (str[i] != '|') {
      word[j] = str[i];
    }
    else {
      word[j + 1] = '\0';
      dirs = realloc(dirs, sizeof(char *) * (*size + 1));
      dirs[*size] = (char *)malloc(50);
      strcpy(dirs[*size], getDir(word));
      if (strcmp(dirs[*size], INVALID) == 0) {
	(*size) = 0;
	free(dirs);
	free(word);
	return NULL;
      }
      memset(word, 0, sizeof(word));
      (*size)++;
      j = -1;
    }
    i++;
    j++;
  }
  if (word[0] != '\0') {
    dirs = realloc(dirs, sizeof(char *) * ((*size) + 1));
    dirs[*size] = (char *)malloc(50);
    strcpy(dirs[*size], getDir(word));
    if (strcmp(dirs[*size], INVALID) == 0) {
      (*size) = 0;
      free(dirs);
      free(word);
      return NULL;
    }
    (*size)++;
  }
  return dirs;
}
