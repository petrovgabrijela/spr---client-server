#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "read-file-to-send.h"

Response* readFile(char* fileName, Response* response, FileInfo* headOfFileInfo){

        int fd = open(fileName, O_RDWR);

         lseek(fd, 0, SEEK_SET);

        if (fd ==-1)
        {
            strcpy(response->message, "This file does not exist here.\n");
            strcpy(response->status, "BAD");
            return response;
        }

      int readSize = read(fd, response->message, 500);


      close(fd);

        if(readSize <= 0)
        {
          strcpy(response->message, "There was a problem with your file.\n");
          strcpy(response->status, "BAD");
          return response;
        }

        FileInfo* temp = headOfFileInfo;

        while(temp!=NULL)
          {
          if(strcmp(fileName, temp->fileData->title) == 0)
          {
            strcpy(response->title, temp->fileData->title);
            strcpy(response->author, temp->fileData->author);
            strcpy(response->description, temp->fileData->description);
            break;
          }
          temp=temp->next;
          }

          strcpy(response->status, "OK");

        return response;
}
