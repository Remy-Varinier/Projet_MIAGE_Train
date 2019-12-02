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
		printf("Ville : %s\n", entree);
		if(strcmp(entree, "exit") != 0){
			write(echange, entree, strlen(entree)+1);
		}
	}while(strcmp(entree, "exit") != 0);
	return 0;
}
