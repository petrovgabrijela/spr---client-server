#include "service.h"
#define MAX 2000

void processData(int sockfd, User* headOfUsers, Combinations *headOfCombinations, BadUsers *headOfBadUsers, FileInfo *headOfFileInfo);

Combinations* loadUserFileCombinations();

void printUserFileCombinations(Combinations* head);

BadUsers* loadBadUsers();

void printBadUsers(BadUsers* head);
