#include <stdio.h>
#include <stdlib.h>

#include "vfsmark.h"

int main(int argc, char* argv[]){

  char opt;
  double total_time;

  if(argc <= 2) {
      printf("Error, not enought args\n");
      return -1;
  }

  createFilesWithSize(atoi(argv[1]),atoi(argv[2]));

  printf("select 1 for sequential read tests\n");

  opt = getchar();

  switch(opt){
  
    case '1':
      printf("Sequential read test starting\n");
      total_time = readSeqFiles(atoi(argv[1]));
      printf("%f\n",total_time);
      
  }

  return 0;
}
