#include "services-client.h"
typedef struct UserFile{
    char username[50];
    char fileName[50];
} UserFile;


#define MAX 2000
#define SA struct sockaddr

void processRequest(int sockfd);
Response* sendReceiveData(char* username, char* fileName, UserFile* userFile, Response* response, int sockfd, char* buff);
