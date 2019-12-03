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
	char entree[MAX];
	int echange = socketClient("localhost", PORT);
	do{
		printf("Entrez une ville :\n");
		fgets(entree, MAX, stdin);
		int taille = strlen(entree);
		if(entree[taille-1] == '\n'){
			entree[taille-1] = '\0';
		}
		printf("Ville : %s\n", entree);
		write(echange, entree, strlen(entree)+1);
		
	}while(strcmp(entree, "exit") != 0);
	return 0;
}
