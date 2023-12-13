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

void writeFile(int bytesToWriteOn);


void writeFiles(int numberFiles, int bytesToWriteOn){
  char buff [10];
  int fd;

  // Open the file and map it to memory

  fd = open(pathnameInput,O_RDONLY,0666);
  if (fd <0 ){
    perror("Error opening the file\n");
    exit(EXIT_FAILURE);
  }

  dir = mmap(NULL,bytesToWriteOn,PROT_READ  | PROT_WRITE, MAP_PRIVATE, fd, 0L); 

  if(dir == MAP_FAILED ){
    perror("Error in mmap");
    exit(EXIT_FAILURE);
  }

  // Call the write function n number of numberFiles
  
  for(writeCounter=0;writeCounter<numberFiles;writeCounter++){
    strcpy(pathnameBufferWrite, "test");
    sprintf(buff,"%d",writeCounter);
    strcat(pathnameBufferWrite,buff);
    printf("Starting to write at file %s\n",pathnameBufferWrite);
    writeFile(bytesToWriteOn);
    printf("%d bytes written to the file number %d\n",bytesToWriteOn,writeCounter);
  }
}

void writeFile(int bytesToWriteOn){ 
  
  int wrBytes;
  int errorcheck;

  wrBytes=0;

  fd = open(pathnameBufferWrite,O_RDWR,0666);
  if(fd<0){
    perror("Cannot open file to write on\n");
    perror(EXIT_FAILURE);
  }
  
  for(wrBytes=0;wrBytes<bytesToWriteOn;wrBytes++){
    //printf("%d\n",wrBytes);
//    printf("%d\n",bytesToWriteOn);
    errorcheck = write(fd,dir,1);
    dir= dir+1;
//    printf("%c",*(char*)dir);
    if(errorcheck < 0){
      perror("Error writing to file %s\n");
      exit(EXIT_FAILURE);
    }
  }
  close(fd);
}
