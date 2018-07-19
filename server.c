/*
   Ejemplo de un echo server.
   Este ejemplo TIENE UN BUG (en realidad son 2 combinados).

   La idea de un echo server es la siguiente:
      1) El cliente se conecta a este server y le envia un numero 
         de 2 digitos (en texto) que representa la longitud del 
         mensaje que le sigue.
      2) El cliente luego envia ese mensaje de esa longitud
      3) El server lee ese mensaje y luego se lo reenvia al cliente.

   Se compila con 
      gcc -std=c99 -o echoserver echoserver.c 

   Se ejecuta como
      ./echoserver PORT PASSWORD

   donde PORT es el nombre de un servicio ("http" por ejemplo) o el numero
   de puerto directamente (80 por ejemplo) 
   PASSWORD es un string que representa algo secreto. No tiene nada que
   ver con el echo server y es borrado de la memoria con free
   Asi que no deberia haber ningun problema en, por ejemplo, que pongas 
   tu password de facebook/clave bancaria, no?
*/

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>



#define CHUNK_LEN 5

void send_file(int skt, char * filename){
  
   FILE* file = fopen(filename, "r");
   if (file == NULL){
      printf("cant open file\n");
      return;
   } 

   fseek(file,0,SEEK_END);
   int file_len = ftell(file);
   
   rewind(file);
   
   int bytes_sent = 0;
   int total_sent = 0;
   char request[CHUNK_LEN+1];
   while (total_sent < file_len){
      memset(request, 0, CHUNK_LEN+1);
      fread((void*) &request, CHUNK_LEN, 1, file);
      printf("se leyo: '%s'\n",request);
      if(feof(file)){
         break;
      }
    
      int request_len = CHUNK_LEN;
      if (file_len - total_sent < CHUNK_LEN){
            request_len = file_len - total_sent;
      }  

      bytes_sent = send(skt, &request, request_len, MSG_NOSIGNAL);
      printf("se envio %i\n", bytes_sent);
      if (bytes_sent < 0){
         printf("cerraron el socket\n");
         break;
      }
      total_sent += bytes_sent;
   }
   printf("se leyo todo el archivo\n");
}

int main(int argc, char *argv[]) {
   if(argc <2){
      printf("1° parametro nombre del file\n");
   }

   struct addrinfo hints;
   struct addrinfo *addr_info;
   
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
   hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
   hints.ai_flags = AI_PASSIVE;     /* AI_PASSIVE for server           */

   int s = getaddrinfo(NULL, "8080", &hints, &addr_info);

   if (s != 0) { 
      printf("Error in getaddrinfo: %s\n", gai_strerror(s));
      return 1;
   }

   int skt = socket(addr_info->ai_family, addr_info->ai_socktype, addr_info->ai_protocol);

   if (skt == -1) {
      printf("Error in creation: %s\n", strerror(errno));
      freeaddrinfo(addr_info);
      return 1;
   }


   s = bind(skt, addr_info->ai_addr, addr_info->ai_addrlen);
   if (s == -1) {
      printf("Error in bind : %s\n", strerror(errno));
      close(skt);
      freeaddrinfo(addr_info);
      return 1;
   }

   freeaddrinfo(addr_info);


   s = listen(skt, -4);
   if (s == -1) {
      printf("Error in listen : %s\n", strerror(errno));
      close(skt);
      return 1;
   }


   bool continue_running = true;
   int peerskt = 0;
   while (continue_running) {
      peerskt = accept(skt, NULL, NULL);   // aceptamos un cliente
      if (peerskt == -1) {
         printf("Error in accept: %s\n", strerror(errno));
      }
      else {
         printf("New client\n");
         send_file(peerskt, argv[1]);

      }
      continue_running = false;
   }
   
   shutdown(skt, SHUT_RDWR);
   close(skt);
}




