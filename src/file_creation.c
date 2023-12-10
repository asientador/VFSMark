#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#include "vfsmark.h"

char pathnameBuff[1024];
void * direcc_map;
int fd_plain_text;

void createFilesWithSize(int numberFiles, int size){
  int i;
  char buff [10];

  fd_plain_text = open(pathnameInput,O_RDWR, 0666);

  if(fd_plain_text < 0){
    perror("Error opening plaintext file");
    exit(EXIT_FAILURE);
  }

  direcc_map = mmap(NULL,size,PROT_READ,MAP_PRIVATE,fd_plain_text,0L);

  if(direcc_map == MAP_FAILED){
    perror("Error MMAP");
    exit(EXIT_FAILURE);
  }


  for(i=0;i<numberFiles;i++){
    strcpy(pathnameBuff,"test");
    sprintf(buff,"%d",i);
    strcat(pathnameBuff,buff);
    createFileWithSize(size);
  }

  //free(direcc_map);
  printf("%d files created with %d bytes each one\n",i,size);
}

void createFileWithSize(int size){

  int fd;
  int error;
  int bytes_writen;

  fd = open(pathnameBuff,O_CREAT | O_TRUNC | O_RDWR, 0666);

  if(fd<0){
    perror("Error creating file");
    exit(EXIT_FAILURE);
  }

  error = ftruncate(fd,size);

  if(error < 0){
    perror("Error truncating file");
    exit(EXIT_FAILURE);
  }

  bytes_writen = write(fd,direcc_map,size);
  if (bytes_writen < 0){
    perror("Error writing to file");
    exit(EXIT_FAILURE);
  }

  //  printf("%d bytes writen to file\n",bytes_writen);

  close(fd);
  close(fd_plain_text);  
}
