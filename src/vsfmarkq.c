#include <stdio.h>
#include <stdlib.h>

#include "vsfmark.h"

int main(int argc, char* argv[]){

  if(argc <= 2) {
      printf("Error, not enought args\n");
      return -1;
  }

  createFilesWithSize(atoi(argv[1]),atoi(argv[2]));

  return 0;
}
