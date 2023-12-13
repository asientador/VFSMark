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
enum modes actualMode;
int blockSizeParam;


void computeTime(struct timespec * start_time, struct  timespec * end_time){
  double elapsed_time;
  elapsed_time=(double)(end_time->tv_sec - start_time->tv_sec) + ((end_time->tv_nsec - start_time->tv_nsec)/1e9);

  printf("%d FILE READ TOOK -> %f(s)\n",i,elapsed_time);
  total_time+= elapsed_time;
}

double g_readFromFile(int numFiles, int mode){
  char buff [10];

  total_time = 0;
  blockSizeParam = blockSize;

  if(mode == r_sequential){
    printf("\n\t\tSequential mode \n\n");
  }
  else if (mode == r_block){
    printf("**Block read mode**\n");
    printf("Give me the block size to read from, default 1024b \n");
    scanf("%d",&blockSizeParam);
    printf("***Test running with %d blockSize***\n",blockSize);
  }else{
    printf("The mode selected is not a valid option\n");
    exit(EXIT_FAILURE);
  }

  for(i=0;i<numFiles;i++){
    strcpy(pathname_buffer,"test");
    sprintf(buff,"%d",i);
    strcat(pathname_buffer,buff);
    readFromFile(mode);
  }
  return total_time;
}

void readFromFile(int mode){

  int fd;
  int error;
  char c;
  char buff;
  char buff_block [blockSizeParam];


  //  printf("Opening file %s\n",pathname_buffer);
  fd=open(pathname_buffer,O_RDONLY);
  if(fd<0){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  error = clock_gettime(CLOCK_REALTIME,&start_time);
  //printf("Start time\n");
  if(error<0){
    perror("Error in clock_gettime");
    exit(EXIT_FAILURE);
  }
  error = 0;

  if(mode == r_sequential){
    do{
      error = read(fd,&buff,sizeof(buff)); // & en buff
      if(error<0){
        perror("Error reading from file on seq");
        exit(EXIT_FAILURE);
      }else if(error==0){
        //      printf("sequential read on %s done\n",pathname); 
        break;
      }else{
        //    printf("%c",buff);
      }
    }while(buff!=EOF);
  }
  else if (mode == r_block){
    do{
      error = read(fd,&buff_block,sizeof(buff_block)); // & en buff
      if(error<0){
        perror("Error reading from file on block mode");
        exit(EXIT_FAILURE);
      }else if(error==0){
        printf("EOF - %s\n",pathname_buffer); 
        break;
      }else{
        //        printf("%c",buff);
      }
    }while(buff_block!=EOF);
  }

  error = clock_gettime(CLOCK_REALTIME,&end_time);
  //printf("End time\n");
  if(error<0){
    perror("Error in clock_gettime");
    exit(EXIT_FAILURE);
  }
  close(fd);
  computeTime(&start_time,&end_time);

}
