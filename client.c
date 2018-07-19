//Defina una rutina en C que se conecte a la IP 8.8.8.8,
// al puerto 8192 y reciba un archivo binario. 
// El archivo recibido debe ser descargado a un archivo llamado recibido.bin
// cuidando el uso de recursos de memoria. El archivo finaliza al detectar conexion cerrada.


#define _POSIX_C_SOURCE 200112L

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


#define CHUNK_LEN 2

void recv_file(int skt, char * filename){
   FILE* file = fopen(filename, "w");
   if (file == NULL){
      printf("cant open file\n");
      return;
   } 
   
   int bytes_recv = 0;
   char chunk[CHUNK_LEN+1];
   memset(chunk, 0, CHUNK_LEN+1);

   while ((bytes_recv = recv(skt, chunk, CHUNK_LEN, MSG_NOSIGNAL)) > 0){
      printf("se recibio %s\n", chunk);
      fwrite((void *) chunk, bytes_recv, 1, file);
      memset(chunk, 0, CHUNK_LEN+1);
   }
   fclose(file);
}

int main(int argc, char *argv[]) {
    if(argc <2){
      printf("1° parametro nombre del file\n");
   }


   struct addrinfo hints;
   struct addrinfo *result;

   int skt = 0;

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
   hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
   hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */

   char hostname[] = "127.0.0.1";
   char port[] = "8080";

   printf("getaddrinfo\n");
   int s = getaddrinfo(hostname, port, &hints, &result);
  if ( s!= 0) { 
      printf("Error in getaddrinfo: %s\n", gai_strerror(s));
      return 1;
  }

  printf("creamos socket\n");
  skt = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (skt == -1) {
    printf("Error: %s\n", strerror(errno));
  }

  printf("connectamos\n");
  if (connect(skt, result->ai_addr, result->ai_addrlen)== -1) {
    printf("Error: %s\n", strerror(errno));
    close(skt);
  }else{
    printf("se conecto\n");
    recv_file(skt, argv[1]);
  }
  
  
  close(skt);
  
  freeaddrinfo(result);

}


