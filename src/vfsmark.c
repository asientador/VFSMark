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

  printf("\n******* Select 1 for READ ********\n");

  opt = getchar();
  
  switch(opt){
  
    case '1':
      printf("\n***** READ TEST ******\n");
      printf("****** Choose ********\n\t------------- 1> Sequential read \n\t------------- 2> Block read \n");
      opt = getchar();
      opt = getchar();
      total_time = g_readFromFile(atoi(argv[1]),opt-'0');
      printf("--------TOTAL TIME -> %f-----------\n",total_time);
      
  }

  return 0;
}
