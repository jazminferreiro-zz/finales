#include <stdio.h>
#include <string.h>
#include <unistd.h>

char * filename = "data.bin";


void replaceBytesInFile() {
  unsigned char buf[2];
  memset(buf, 0, 2);
  long int ocurrences = 0;

  // open file for read and update in binary mode
  FILE* file = fopen(filename, "r+b");
  if (file == NULL){
    printf("cant open file\n");
    return;
  } 

  int c;
  int current_point = 0;
  while((c = fgetc(file)) != EOF){
    current_point +=1;
    printf("read %x\n",c );
    //escribir en posicion correspondiente 
    //el caracter que acabo de leer
    if(ocurrences > 0) {
      printf("hay %li ocurrencias\n",ocurrences );
      fseek(file, - ocurrences - 1, SEEK_CUR);
      fputc(c,file); //aumentamos 1
      fseek(file, ocurrences, SEEK_CUR);
    }
    if(buf[0] == 0x34 && buf[1] == 0x43 && c == 0x44){
      ocurrences +=1;
      printf("se encontro una ocurrencia\n");
    }else{
      buf[0] = buf[1];
      buf[1] = c;
      printf("%x %x\n",buf[0],buf[1] );
    }
  }
  ftruncate(fileno(file), current_point - ocurrences);
  fclose(file);
}

int main(int argc, char const *argv[]) {
  replaceBytesInFile();
  return 0;
}