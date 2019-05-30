#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "service.h"

Response* findFile(UserFile* userData, Combinations* headOfCombinations, BadUsers *headOfBadUsers, Response* response, FileInfo* headOfFileInfo)
{

  Combinations* temp = headOfCombinations;

  while(temp!=NULL)
    {
    if(strcmp(temp->userFile->username, userData->username) == 0 && strcmp(temp->userFile->fileName, userData->fileName) == 0)
    {
      writeToBadUsersFile(userData->username, headOfBadUsers);
      strcpy(response->message, "You already dowloaded this file!");
      strcpy(response->status, "BAD");
      break;
    }
    temp=temp->next;
    }

    if(strcmp("BAD", response->status) != 0)
    {
      writeToUserFileCombinationFile(userData, headOfCombinations);
      response = readFile(userData->fileName, response, headOfFileInfo);
      printf("Message: %s", response->message);
      printf("Status: %s", response->status);
    }

    return response;

}


void writeToBadUsersFile(char* username, BadUsers *head)
{
int fd = open(FILE_NAME_BAD_USERS, O_WRONLY | O_APPEND);
int numberOfBadRequests = 1;
int usernameLen = strlen(username);

if(write(fd, &numberOfBadRequests, sizeof(int)) <= 0) {
  printf("FAILED WRITING\n");
}
if(write(fd, &usernameLen, sizeof(int)) <= 0) {
  printf("FAILED WRITING\n");
}
if(write(fd, username, usernameLen) <= 0) {
  printf("FAILED WRITING\n");
}


close(fd);

}

void writeToUserFileCombinationFile(UserFile* userData, Combinations* head)
{
  int fd = open(FILE_NAME_COMBINATIONS, O_WRONLY | O_APPEND);

  int fileNameLen = strlen(userData->fileName);
  int usernameLen = strlen(userData->username);

  write(fd, &usernameLen, sizeof(int));
  write(fd, userData->username, usernameLen);
  write(fd, &fileNameLen, sizeof(int));
  write(fd, userData->fileName, fileNameLen);


  close(fd);

}
