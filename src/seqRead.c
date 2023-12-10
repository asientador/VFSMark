#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <time.h>

#include "vfsmark.h"

struct timespec start_time, end_time;
int i;
double total_time;
char pathname_buffer [1024];

void computeTime(struct timespec * start_time, struct  timespec * end_time){
  double elapsed_time;
  elapsed_time=(double)(end_time->tv_sec - start_time->tv_sec) + ((end_time->tv_nsec - start_time->tv_nsec)/1e9);

  printf("%d FILE SEQUENTIAL READ TOOK -> %f(ms)\n",i,elapsed_time);
  total_time+= elapsed_time;
}

double readSeqFiles(int numFiles){
  char buff [10];
  
  total_time = 0;

  for(i=0;i<numFiles;i++){
    strcpy(pathname_buffer,"test");
    sprintf(buff,"%d",i);
    strcat(pathname_buffer,buff);
    readSeqFile();
  }
  return total_time;
}

void readSeqFile(){
  
  int fd;
  int error;
  char c;
  char buff;
  


  fd=open(pathname_buffer,O_RDONLY);
  if(fd<0){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  
  error = clock_gettime(CLOCK_REALTIME,&start_time);
  printf("Start time\n");
  if(error<0){
   perror("Error in clock_gettime");
   exit(EXIT_FAILURE);
  }
  error = 0;

  do{
       error = read(fd,&buff,sizeof(buff)); // & en buff
    if(error<0){
      perror("Error reading from file on seq");
      exit(EXIT_FAILURE);
    }else if(error==0){
//      printf("EOF - %s\n",pathname); 
      break;
    }else{
//      printf("%c",buff);
    }
  }while(buff!=EOF);

  error = clock_gettime(CLOCK_REALTIME,&end_time);
  printf("End time\n");
  if(error<0){
    perror("Error in clock_gettime");
    exit(EXIT_FAILURE);
  }
  close(fd);
  computeTime(&start_time,&end_time);

}
