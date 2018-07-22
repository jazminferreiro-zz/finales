//Escriba un pequeño programa que, sin validar errores, 
//acepte una única conexión TCP en el puerto 1972 y reciba paquetes de no mas de 600 bytes,
// terminado en '0x00'. Cada paquete recibido debe ser devuelto con todos sus bits negados. 
//Terminar al recibir un paquete nulo.

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<errno.h>

#define CHUNK_LEN 600

#define PORT 1972


void send_neg(int peerskt, char * buffer, int request_len){
	int bytes_sent = 0;
	int total_sent = 0
	while((bytes_sent = send(peerskt, buffer[toal_sent],request_len -total_sent, MS_NOSIGNAL)) > 0){
		total_sent + = bytes_sent;
		if(peerskt <= 0){
			return;
		}
	}
}

int main(){

	struct addrinfo hints;
	struct addrinfo * addr_info;
	memset(&hinsts, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_sockettype = SOCKT_STRAM;
	hints.ai_flags = AI_PASSIVE;

	int s = getaddrinfo(NULL,PORT,&hints, &addr_info);

	int skt = soket(addr_info->ai_family, addr_info-> sockettype, addr_info->protocol);

	s = bind(skt, addr_info->ai_addr, addr->ai_addrlen);

	s = listen(skt, 2);

	freeaddrinfo(add_info);

	int peerskt = connect(skt, NULL, NULL);

	char chunk[CHUNK_LEN];
	memset(chunk, 0, CHUNK_LEN);


	int bytes_recv = 0;
	int total = 0
	int i = 0;


	while(( byetes_recv = recv(peerskt,chunk,CHUNK_LEN, MS_NOSIGNAL)) > 0) {
		send_neg(peerskt, ~request, bytes_recv);
	}



	shutdown(skt, SHUTDOWN_RDWR);
	close(skt);
}
