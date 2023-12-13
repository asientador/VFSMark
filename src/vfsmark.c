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

  printf("\n* Enter a command *\n");
  printf("0. exit\n");
  printf("1. read\n");
  printf("2. write\n->");

  opt = getchar();

  while(opt!='0'){
    switch(opt){
      case '0':
        printf("See you\n");
        break;
      case '1':
        printf("** READ TEST **\n");
        printf("1. SequentialRead\n2. BlockRead\n");
        opt = getchar();
        opt = getchar();
        total_time = g_readFromFile(atoi(argv[1]),opt-'0');
        printf("--------TOTAL TIME -> %f-----------\n",total_time);
        opt = '0';
        break;
      case '2':
        printf("\n***** WRITE TEST *******\n");
        printf("1. SequentialWrite\n->");
        opt = getchar();
        opt = getchar();
        if(opt=='1'){
        writeFiles(atoi(argv[1]),atoi(argv[2]));  
        opt = '0';
        break;
        }
        else{
          opt='0';
          break;
        }
      default : 
        printf("Select a valid option\n");
    }
  }


  return 0;
}
