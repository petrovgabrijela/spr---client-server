#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "process-data.h"

void processData(int sockfd, User* headOfUsers, Combinations *headOfCombinations, BadUsers *headOfBadUsers, FileInfo *headOfFileInfo)
{
    char buff[MAX];

    UserFile* userFile = malloc(sizeof(UserFile));
    Response* response = (Response*) malloc(sizeof(Response));;
    int log = 0;
    for (;;) {
        bzero(buff, MAX);

        read(sockfd, buff, sizeof(buff));

        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }

        memcpy(userFile, buff, sizeof(buff));

        bzero(buff, MAX);

        bzero(response, sizeof(Response));

        if(log == 0)
        {
          if(logUser(userFile->username, headOfUsers)==1)
          {
              response = findFile(userFile, headOfCombinations, headOfBadUsers, response, headOfFileInfo);
              log = 1;
          }
          else
          {
            strcpy(response->message, "Wrong username!");
            strcpy(response->status, "BAD");
          }
        }
        else
        {
          response = findFile(userFile, headOfCombinations, headOfBadUsers, response, headOfFileInfo);
        }

        memcpy(buff, response, sizeof(buff));

        write(sockfd, buff, sizeof(buff));

    }
}
Combinations* loadUserFileCombinations()
{

    Combinations *current = NULL;
    Combinations *head = NULL;

    int lenFileName;
    int lenUsername;
    int readSize;

    int fd = open(FILE_NAME_COMBINATIONS, O_RDONLY);

    UserFile *userFile = (UserFile *) malloc(sizeof(UserFile));

    Combinations *combinations = (Combinations *) malloc(sizeof(Combinations));

    lseek(fd, 0, SEEK_SET);

    userFile = (UserFile *) malloc(sizeof(UserFile));
    readSize = read(fd, &lenUsername, sizeof(int));
    readSize = read(fd, &userFile->username, lenUsername);
    userFile->username[lenUsername] = '\0';
    readSize = read(fd, &lenFileName, sizeof(int));
    readSize = read(fd, &userFile->fileName, lenFileName);
    userFile->fileName[lenFileName] = '\0';

    combinations->userFile = userFile;

    combinations->next = NULL;

    head = combinations;

    current = combinations;

    while(1)
    {

      userFile = (UserFile *) malloc(sizeof(UserFile));
      readSize = read(fd, &lenUsername, sizeof(int));
      readSize = read(fd, &userFile->username, lenUsername);
      userFile->username[lenUsername] = '\0';
      readSize = read(fd, &lenFileName, sizeof(int));
      readSize = read(fd, &userFile->fileName, lenFileName);
      userFile->fileName[lenFileName] = '\0';

      if(readSize <= 0)
      {
        break;
      }

      combinations = (Combinations *) malloc(sizeof(Combinations));

      combinations->userFile = userFile;

      combinations->next = NULL;

      current->next = combinations;

      current = current->next;

    }

    close(fd);
    printUserFileCombinations(head);
    return head;
}

void printUserFileCombinations(Combinations* head)
{
  Combinations* temp = head;

  while(temp!=NULL)
    {
    printf("%s ",temp->userFile->username);
    printf("%s ",temp->userFile->fileName);
    printf("\n");
    temp=temp->next;
    }
}

BadUsers* loadBadUsers()
{
  BadUsers *current = NULL;
  BadUsers *head = NULL;

  int lenUsername;
  char username[20];
  int numberOfBadRequests;
  int readSize;

  int fd = open(FILE_NAME_BAD_USERS, O_RDONLY);

  BadUsers *badUser = (BadUsers *) malloc(sizeof(BadUsers));

  lseek(fd, 0, SEEK_SET);

  readSize = read(fd, &numberOfBadRequests, sizeof(int));
  readSize = read(fd, &lenUsername, sizeof(int));
  readSize = read(fd, &username, lenUsername);
  username[lenUsername] = '\0';

  strcpy(badUser->username, username);

  badUser->numberOfBadRequests = numberOfBadRequests;

  badUser->next = NULL;

  head = badUser;

  current = badUser;

  while(1)
  {

    badUser = (BadUsers *) malloc(sizeof(BadUsers));
    readSize = read(fd, &numberOfBadRequests, sizeof(int));
    readSize = read(fd, &lenUsername, sizeof(int));
    readSize = read(fd, &username, lenUsername);
    username[lenUsername] = '\0';

    if(readSize <= 0)
    {
      break;
    }

    strcpy(badUser->username, username);

    badUser->numberOfBadRequests = numberOfBadRequests;

    badUser->next = NULL;

    current->next = badUser;

    current = current->next;

  }
  close(fd);
  printBadUsers(head);
  return head;
}

void printBadUsers(BadUsers* head)
{
  BadUsers* temp = head;

  while(temp!=NULL)
    {
    printf("%s ",temp->username);
    printf("%d ",temp->numberOfBadRequests);
    printf("\n");
    temp=temp->next;
    }
}
