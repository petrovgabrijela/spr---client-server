typedef struct Response {
    char message[500];
    char status[5];
    char title[20];
    char author[20];
    char description[50];
} Response;

typedef struct FileInfo{
    char title[20];
    char author[20];
    char description[50];
    struct FileInfo* next;
} FileInfo;

void saveFile(Response* response, char* username);
void writeToAllDownloadedFilesFile(Response* response, char* username);
