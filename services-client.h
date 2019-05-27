typedef struct Response {
    char message[500];
    char status[5];
    char title[20];
    char author[20];
    char description[50];
} Response;

void saveFile(Response* response);
