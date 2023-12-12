#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "vfsmark.h"

int fd;
void * dir;
int writeCounter;
char pathnameBufferWrite[100];

void writeFiles(int numberFiles, int bytesToWriteOn){
  char buff [10];
  for(writeCounter=0;writeCounter<numberFiles;writeCounter++){
    strcpy(pathnameBufferWrite, "test");
    sprintf(buff,"%d",writeCounter);
    strcat(pathnameBufferWrite,buff);
    writeFile(bytesToWriteOn);
    printf("%d bytes written to the file number %d\n",bytesToWriteOn,writeCounter);
  }
}
void writeFile(int bytesToWriteOn){ 
  
  int wrBytes;

  fd = open(pathnameInput,O_RDONLY,0666);
  if (fd <0 ){
    perror("Error opening the file\n");
    exit(EXIT_FAILURE);
  }

  dir = mmap(NULL,bytesToWriteOn,PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0L); 

  if(dir == MAP_FAILED ){
    perror("Error in mmap");
    exit(EXIT_FAILURE);
  }


  fd = open(pathnameBufferWrite,O_WRONLY,0666);
  if(fd<0){
    perror("Cannot open file to write on\n");
    perror(EXIT_FAILURE);
  }

  do{
    wrBytes = write(fd,dir,sizeof(char));
    printf("%c",*(char*)dir);
    dir++;
  }while(wrBytes != 0);
  
  free(dir);



  
}
