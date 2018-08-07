#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <ctype.h>

char * filename = "sumarize.bin";


void sumarize() {
  // open file for read and update in binary mode
  FILE* file = fopen(filename, "r+b");
  if (file == NULL){
    printf("cant open file\n");
    return;
  } 

  int delimiter = 0xffffffff;

  int num = 0;
  int sum = 0;

  int read_point = 0;
  int write_point = 0;

  while(!feof(file)){
    
    fread((void*) &num, 4, 1, file);
    if(feof(file)){
      break;
    }
    if(num == delimiter){
      sum = htonl(sum);
      read_point = ftell(file);
      fseek(file,write_point,SEEK_SET);
      fwrite((void*) &sum, 1, 4, file);
      fwrite((void*) &delimiter, 1, 4, file);
      write_point = ftell(file);
      fseek(file,read_point, SEEK_SET);
      sum = 0;
    }
    else{
      num = ntohl(num);
      sum += num;
    }
  }
  printf("write_point %i\n",write_point );
  ftruncate(fileno(file), write_point);
  fclose(file);
}

int main(int argc, char const *argv[]) {
  sumarize();
  return 0;
}