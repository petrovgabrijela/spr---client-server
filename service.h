#include "read-from-database.h"
//#include "read-file-to-send.h"

#define FILE_NAME_COMBINATIONS "user-file.dat"
#define FILE_NAME_BAD_USERS "bad-users.dat"

typedef struct UserFile{
    char username[50];
    char fileName[50];
} UserFile;

typedef struct ListCombinations{
  UserFile* userFile;
  struct ListCombinations *next;
} Combinations;

typedef struct BadUser {
  char username[20];
  int numberOfBadRequests;
  struct BadUser *next;
} BadUsers;


Response* findFile(UserFile* userData, Combinations* headOfCombinations, BadUsers *headOfBadUsers, Response* response, FileInfo* headOfFileInfo);

void writeToBadUsersFile(char* username, BadUsers *head);

void writeToUserFileCombinationFile(UserFile* userData, Combinations* head);
