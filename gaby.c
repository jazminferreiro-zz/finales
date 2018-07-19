#include <stdio.h>
#include <unistd.h>


char filename[10] = "data.bin";

int process(unsigned char buf[3]) {
  if (buf[0] == 0x34 && buf[1] == 0x43)
    return 1;
  buf[0] = buf[1];
  buf[1] = buf[2];
  return 0;
}

void replaceBytesInFile() {
  unsigned char buf[3];
  int ocurrences = 0;
  int read_pos;
  // open file for read and update in binary mode
  FILE* file = fopen(filename, "r+b");
  if (file == NULL) return;
  fread((void*) buf, 1, 3, file);
  read_pos = 3;
  while (!feof(file)) {
    ocurrences += process(buf);
    if (ocurrences > 0) {
      //escribir buf en posicion correspondiente
      fseek(file, - 2 - ocurrences, SEEK_CUR);
      fwrite((void*) buf, 1, 1, file);
      fseek(file, ocurrences + 1, SEEK_CUR);
    }
    fread((void*) buf + 2, 1, 1, file);
    read_pos += 1;
  }
  fseek(file, - 2 - ocurrences, SEEK_CUR);
  fwrite((void*) buf, 1, 2, file);
  ftruncate(fileno(file), read_pos - ocurrences - 1);
  fclose(file);
}

int main(int argc, char const *argv[]) {
  replaceBytesInFile();
  return 0;
}