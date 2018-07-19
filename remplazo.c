#include <stdio.h>
#include<string.h>

void replace(char * A, char * B, char * C){
	int len = strlen(B);
	int read_pos = 0;
	int write_pos = 0;
	while(read_pos < strlen(A)){
		if(strncmp(&A[read_pos],B, len) == 0){
				for(int i = 0; i < strlen(C); i++){
					A[write_pos++] = C[i];
				}
			read_pos += (len-1);
		} else {
			if(read_pos != write_pos){
				A[write_pos] = A[read_pos];
			}
			write_pos++;
			read_pos++;
		}

	}
	printf("---> %s\n",A);
	
}

int main(int argc, char * argv[]){
	replace(argv[1], argv[2],argv[3]);
	return 0;
}