#include <stiod.h>
#include <stdlib.h>
#include <fcntl.h>

#include "vfsmark.h"

int main(){
  int fd;

  fd = open("test0",O_WRONLY);
  if(fd <0 ){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

}
