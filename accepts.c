//Escriba un programa que escuche conexiones TCP en el puerto 3280
// y guarde en disco con nombres correlativos (1.html, 2.html , ...) 
//cada uno de los HTML recibidos.

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include  <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/typed.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stderror.h>

#define CHUNK_LEN 256
#define PORT 3280

recive_html(int peerskt, int n){
	char file_name[5]; 
	sprintf(file_name, "html.%i", n);
	FILE * file = fopen(file_name, "w+b")
	if(file == NULL){
		printf("error al crear el archivo %s\n", file_name);
	}

	int bytes_recv = 0;
	char chunk[CHUNK_LEN];
	memset(chunk, 0, CHUNK_LEN);
	while((bytes_recv = recv(peerskt, &chunk,CHUNK_LEN, MSG_NOSIGNAL)) > 0){
		fwrite((void *) chunk,bytes_recv,1, file);
		memset(chunk, 0, CHUNK_LEN);
	}

	fclose(file);
}

int main(int argc, char* argv[]){

	struct addrinfo hints;
	struct addrinfo * addr_info;

	memset(&hints, 0, sizeof(hints));

	addr_info.ai_family = AF_INET;
	addr_info.ai_sockettype = STREAM_SOCKET;
	addr_info.ai_flags = AI_PASSIVE;

	int s = getaddrinfo(NULL, PORT, &hints, &addr_info);
	if(s != 0){
		printf("Error en getaddrinfo %s", gai_strerror(s));
		return 1;
	}

	int skt = socket(addr_info->ai_family, addr_info->ai_sockettype, addr_info->ai_protocol);
	if(skt == -1){
		printf("Error en socket creation %s", strerror(errno));
		freeaddrinfo(addr_info);
	}

	s = bind(skt, addr_info->ai_addr, addr_info->ai_addrlen);
	if(s == -1){
		printf("Error en bind %s", strerror(errno));
		close(skt);
		freeaddrinfo(addr_info);
	}

	listen(skt, 20);

	int n = 0;
	int peerskt;
	while(n < 3){
		peerskt= accept(skt,NULL,NULL);
		if(s ==-1){
			continue;
		}else{
			recive_html(peerskt, n);
			n++;
		}
	}

	shutdown(skt, SHUT_RDWR);
	close(skt);

	

}