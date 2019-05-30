#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include "services-client.h"

void saveFile(Response* response, char* username)
{
  char directory[30] = {0};
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
  int fd = open(fullPath, O_RDWR | O_CREAT);
  if(fd == -1)
  {
    printf("Cannot save file.\n");
  }
  write(fd, response->message, strlen(response->message));

close(fd);

writeToAllDownloadedFilesFile(response, username);

}

void writeToAllDownloadedFilesFile(Response* response, char* username)
{
  char* home = getenv("HOME");
  char* path = malloc(strlen(home) + strlen(username) + 16);
  strcpy(path, home);
  strcat(path, "/");
  strcat(path, username);
  strcat(path, "/downloads.txt");
  int fd = open(path, O_RDWR | O_CREAT | O_APPEND);
  int lenTitle = strlen(response->title);
  int lenAuthor = strlen(response->author);
  int lenDescription = strlen(response->description);
  write(fd, response->title, lenTitle);
  write(fd, response->author, lenAuthor);
  write(fd, response->description, lenDescription);
}
