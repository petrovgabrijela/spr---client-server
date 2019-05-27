#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include "services-client.h"

void saveFile(Response* response)
{
  char directory[20];
  printf("Enter directory: ");
  getchar();
  scanf("%s", directory);
  char* fileName = (char*) malloc(20);
  strcpy(fileName, response->title);
  char* home = getenv("HOME");
  char *fullPath = malloc(strlen(home) + strlen(directory) + strlen(fileName));
  strcpy(fullPath, home);
  strcat(fullPath, directory);
  strcat(fullPath, fileName);
  printf("%s  PATH ", fullPath);
  int fd = open(fullPath, O_RDWR | O_CREAT);
  if(fd == -1)
  {
    printf("Cannot save file.\n");
  }
  write(fd, response->message, strlen(response->message));

close(fd);

//  writeToAllDownloadedFilesFile();
}
