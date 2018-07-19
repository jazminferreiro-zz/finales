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

int main(int argc, char *argv[]) {

   struct addrinfo hints;
   struct addrinfo *result;

   int skt = 0;

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
   hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
   hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */

   char hostname[] = "8.8.8.8";
   char port[] = "8192";

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
  }
  
  printf("se conecto\n");
  close(skt);
  
  freeaddrinfo(result);

}


