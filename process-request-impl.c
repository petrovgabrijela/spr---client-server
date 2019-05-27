#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "process-request.h"

void processRequest(int sockfd)
{
    UserFile* userFile = malloc(sizeof(UserFile));
    Response* response = malloc(sizeof(Response));
    char buff[MAX];
    int log = 0;

    int connfd;

    struct sockaddr_in servaddr, cli;

    char username[20];
    char address[50];
    char directory[150];
    char *port;
    char *fileName;

    printf("Enter address of a file: ");
    scanf("%s", address);

    strtok_r (address, "/", &fileName);

    strtok_r (address, ":", &port);

    int portNumber;
    sscanf(port, "%d", &portNumber);

    printf("Address: %s\n", address);

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(address);
    servaddr.sin_port = htons(portNumber);

    connfd = connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

    // connect the client socket to server socket
    if (connfd != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    for (;;) {

        if(log == 0) {
          bzero(username, strlen(username));
          write(1, "Enter your username: ", 22);
          read(0, username, 20);
          username[strlen(username)-1] = '\0';
          printf("Username:    %s ", username);
          response = sendReceiveData(username, fileName, userFile, response, sockfd, buff);
          if(strcmp(response->status, "OK")==0)
          {
            log = 1;
            saveFile(response);
          }
        }
        else {

          printf("Enter address of a file: ");
          scanf("%s", address);

          strtok_r (address, "/", &fileName);

          response = sendReceiveData(username, fileName, userFile, response, sockfd, buff);
          if(strcmp(response->status, "OK")==0)
          {
            saveFile(response);
          }

          /*// assign IP, PORT
          servaddr.sin_family = AF_INET;
          servaddr.sin_addr.s_addr = inet_addr(address);
          servaddr.sin_port = htons(PORT);*/

          // connect the client socket to server socket
          /*connfd = connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
          if (connfd != 0) {
              printf("connection with the server failed...\n");
              exit(0);
          }
          else
              printf("connected to the server..\n");*/
        }

        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

Response* sendReceiveData(char* username, char* fileName, UserFile* userFile, Response* response, int sockfd, char* buff)
{
  bzero(buff, MAX);
  strcpy(userFile->fileName, fileName);
  strcpy(userFile->username, username);

  memcpy(buff, userFile, MAX);

  write(sockfd, buff, MAX);
  bzero(buff, MAX);
  read(sockfd, buff, MAX);

  memcpy(response, buff, MAX);
  if(strcmp(response->status, "OK")==0)
  {
    printf("From Server 2: %s %s\n", response->message, response->title);
  }
  else
  printf("From Server 3: %s %s\n", response->message, response->status);
  return response;
}
