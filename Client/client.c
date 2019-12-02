#include <stdio.h>
#include <string.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/uio.h>

#include "../Common/Headers/reseau.h"

int main(int argc,char *argv[]){
	printf("1\n");
	char entree[MAX];
	printf("2\n");
	int echange = socketClient("localhost",4242);
	printf("3\n");
	do{
		printf("Entrez une ville :\n");
		fscanf(stdin, "%s", entree);
		if(strcmp(entree, "exit") != 0){
			write(echange, entree, MAX);
		}
	}while(strcmp(entree, "exit") != 0);
		/*
	printf("Un client est connecté \n");
	char *message = "Bonjour";
	write(echange, message, strlen(message)+1);
	char tampon[MAX];
	int nbLus = read(echange, tampon, MAX);
	printf("J'ai lu '%s' \n",tampon);*/
	return 0;
}
