#include <mysql/mysql.h>
#include "common.h"
typedef struct Response {
    char message[500];
    char status[5];
} Response;



Response* readFile(char* fileName, Response* response, FileInfo* headOfFileInfo);

typedef struct User{
    char* name;
    char* username;
    char* password;
    struct User* next;
} User;



FileInfo* addFileInfo(MYSQL_ROW row);

FileInfo* addFileInfoToList(MYSQL_RES *res);

void printFileInfoListFromDatabase(FileInfo* head);

User* addUser(MYSQL_ROW row);

User* addUsersToList(MYSQL_RES *res);

void printUserListFromDatabase(User* head);

User* readUsersFromDatabase();

FileInfo* readFileInfoFromDatabase();

int logUser(char* username, User* head);
