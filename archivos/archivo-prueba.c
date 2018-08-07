#include <stdio.h>
#include <unistd.h>
#include <string.h>

char * filename = "data.txt";


void replaceBytesInFile() {
  unsigned char buf[2] = "00";
  long int ocurrences = 0;

  // open file for read and update in binary mode
  FILE* file = fopen(filename, "r+b");
  if (file == NULL){
    printf("cant open file\n");
    return;
  } 
  int n = 0;
  int c;
  while((c = fgetc(file)) != EOF){
    printf("read %c\n",c );
    n++;
  }
  ftruncate(fileno(file), (n -1) - 2);
  fclose(file);
}

void lenght(){
  char line[] = "hola\nchau";
  printf(" >>> %li\n",strlen(line));
}

int main(int argc, char const *argv[]) {
  //replaceBytesInFile();
  lenght();
  return 0;
}