#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#include "vfsmark.h"

double computeTime(struct timespec * start_time, struct  timespec * end_time){
  double elapsed_time;
  elapsed_time=(double)(end_time->tv_sec - start_time->tv_sec) + ((end_time->tv_nsec - start_time->tv_nsec)/1e9);

  printf("Elapsed_time -> %f\n",elapsed_time);
  return elapsed_time;
}

int main(){
  
  int fd;
  int error;
  char c;
  char buff;
  double elapsed_time;
  
  struct timespec start_time, end_time;

  fd=open(pathname,O_RDONLY);
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
  
  elapsed_time=computeTime(&start_time,&end_time);


  return 0;
}
