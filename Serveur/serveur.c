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

#include "../Common/Headers/reseau.h"

void fils(int echange){
	char tampon[MAX];
	do{
		printf("Echange dans fils : %d\n", echange);
		int lu = read(echange, tampon, MAX);
		printf("J'ai lu : %s, int : %d\n", tampon, lu);
	}while(strcmp(tampon,"exit") != 0);
}

int main(int argc,char *argv[]){
	pid_t id;
	do{
		int ecoute = socketServeur(PORT);
		printf("Ecoute : %d\n", ecoute);
		printf("Socketé\n");
		int echange = accept(ecoute,NULL, NULL);
		printf("Echange : %d\n", echange);
		printf("Accepté\n");
		id = fork();
		if(id == 0){
			printf("Je suis passé dans le fils \n");
			fils(echange);
			exit(0);
		}
	}while(true);
	return 0;
}
