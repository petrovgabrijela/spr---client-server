#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "read-from-database.h"
#include "database-connect.h"

User* readUsersFromDatabase()
{
MYSQL *connection = connectToDatabase();
if (mysql_query(connection, "SELECT * FROM User")) {
      fprintf(stderr, "%s\n", mysql_error(connection));
      return NULL;
   }

   MYSQL_RES *res = mysql_use_result(connection);

   User* head = addUsersToList(res);

   closeConnection(connection);

   return head;
}

FileInfo* readFileInfoFromDatabase()
{
MYSQL *connection = connectToDatabase();
if (mysql_query(connection, "SELECT * FROM FileInfo")) {
      fprintf(stderr, "%s\n", mysql_error(connection));
      return NULL;
   }

   MYSQL_RES *res = mysql_use_result(connection);

   FileInfo* head = addFileInfoToList(res);

   closeConnection(connection);

   return head;
}

User* addUsersToList(MYSQL_RES *res)
{

User *current = NULL;
User *head = NULL;

MYSQL_ROW row = NULL;

   while ((row = mysql_fetch_row(res)) != NULL)
{
    User* user = addUser(row);

    if(head == NULL)
    {
        head = user;
        current = head;
    }
    else
    {
        current->next = user;
        current = current->next;
    }
}
printUserListFromDatabase(head);
 mysql_free_result(res);
return head;
}

User* addUser(MYSQL_ROW row)
{
    User *user = (User*)malloc(sizeof(User));

    user->username = (char*) malloc(strlen(row[0])+1);
    strcpy(user->username, row[0]);
    user->username[strlen(row[0])] = '\0';

    user->password = (char*) malloc(strlen(row[1])+1);
    strcpy(user->password, row[1]);
    user->password[strlen(row[1])] = '\0';

    user->name = (char*) malloc(strlen(row[2])+1);
    strcpy(user->name, row[2]);
    user->name[strlen(row[2])] = '\0';

    user->next = NULL;

    return user;
}

FileInfo* addFileInfoToList(MYSQL_RES *res)
{

FileInfo *current = NULL;
FileInfo *head = NULL;

MYSQL_ROW row = NULL;

   while ((row = mysql_fetch_row(res)) != NULL)
{
    FileInfo* file = addFileInfo(row);

    if(head == NULL)
    {
        head = file;
        current = head;
    }
    else
    {
        current->next = file;
        current = current->next;
    }
}
printFileInfoListFromDatabase(head);
 mysql_free_result(res);
return head;
}

FileInfo* addFileInfo(MYSQL_ROW row)
{
    FileInfo *file = (FileInfo*)malloc(sizeof(FileInfo));
    file->fileData = (FileData*)malloc(sizeof(FileData));

    file->fileData->title = (char*) malloc(strlen(row[0])+1);
    strcpy(file->fileData->title, row[0]);
    file->fileData->title[strlen(row[0])] = '\0';

    file->fileData->author = (char*) malloc(strlen(row[1])+1);
    strcpy(file->fileData->author, row[1]);
    file->fileData->author[strlen(row[1])] = '\0';

    file->fileData->description = (char*) malloc(strlen(row[2])+1);
    strcpy(file->fileData->description, row[2]);
    file->fileData->description[strlen(row[2])] = '\0';

    file->next = NULL;

    return file;
}



int logUser(char* username, User* head)
{
  User* temp = head;
  while(temp!=NULL)
    {
      printf("TEMP USER: %s\n", temp->username);
      printf("Username db: %s", username);
    if(strcmp(temp->username, username) == 0)
    {
      printf("User found! %s", username);
      return 1;
    }
    temp=temp->next;
    }
    return 0;
}


void printUserListFromDatabase(User* head)
{
  User* temp = head;

  while(temp!=NULL)
    {
    printf("%s ",temp->name);
    printf("%s ",temp->username);
    printf("%s ",temp->password);
    printf("\n");
    temp=temp->next;
    }
}

void printFileInfoListFromDatabase(FileInfo* head)
{
  FileInfo* temp = head;

  while(temp!=NULL)
    {
    printf("%s ",temp->fileData->title);
    printf("%s ",temp->fileData->author);
    printf("%s ",temp->fileData->description);
    printf("\n");
    temp=temp->next;
    }
}
