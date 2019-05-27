typedef struct FileData{
    char* title;
    char* author;
    char* description;
} FileData;


typedef struct FileInfo{
    FileData* fileData;
    struct FileInfo* next;
} FileInfo;
