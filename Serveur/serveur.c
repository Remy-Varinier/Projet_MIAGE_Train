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
	printf("une co\n");
	char tampon[MAX];
	do{
		int lu = read(echange, tampon, MAX);
		printf("J'ai lu : %s, int : %d\n", tampon, lu);
	}while(strcmp(tampon,"exit") != 0);	
}

int main(int argc,char *argv[]){
	pid_t id;
	int ecoute = socketServeur(PORT);
	do{
		printf("en attente de co : \n");
		int echange = accept(ecoute,NULL, NULL);
		printf("connecté : \n");
		id = fork();
		
		if(id == 0){
			fils(echange);
			close(ecoute);
			exit(0);
		}
	}while(true);
	return 0;
}
