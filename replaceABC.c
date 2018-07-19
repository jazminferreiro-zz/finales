#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int get_ocurrences(char *A, char * B){
	int ocurrences = 0;
	int i = 0;
	while(i < strlen(A)){
		if(strncmp(&A[i], B, strlen(B)) == 0){
			ocurrences +=1;
			i += strlen(B);
		}else{
			i++;
		}
	}
	return ocurrences;
}

void replace(char * A, char * B, char * C){
	int ocurrences = get_ocurrences(A,B);
	int new_len = strlen(A) + ocurrences * (strlen(C) - strlen(B));
	
	char D[new_len];

	int len = strlen(B);
	int read_pos = 0;
	int write_pos = 0;

	while(read_pos < strlen(A)){
		if(strncmp(&A[read_pos],B, len) == 0){
				for(int i = 0; i < strlen(C); i++){
					D[write_pos++] = C[i];
				}
			read_pos += (len);
		} else {
			D[write_pos++] = A[read_pos++];
		}

	}
	D[write_pos] = 0;
	printf("---> %s\n",D);
	
}

int main(int argc, char * argv[]){
	replace(argv[1], argv[2],argv[3]);
	return 0;
}