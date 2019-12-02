#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/uio.h>

#define MAX 100

int main(int argc,char *argv[]){ 
	/*int ecoute = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(7777);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(ecoute, (struct sockaddr *)&sin, sizeof(sin));
	listen(ecoute,5);//écoute de la socket*/
	int ecoute = socketServeur("localhost",4242);
	int echange = accept(ecoute,NULL, NULL);
	printf("Un client s'est connecté \n");
	char tampon[MAX];
	read(ecoute, tampon, sizeof(ecoute));
	printf("Un client est connecté \n");
	return 0;
}