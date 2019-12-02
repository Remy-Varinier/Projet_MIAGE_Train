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

int main(int argc,char *argv[]){ 
	int ecoute = socketServeur(4242);
	int echange = accept(ecoute,NULL, NULL);
	printf("Un client s'est connecté \n");
	char tampon[MAX];
	read(ecoute, tampon, sizeof(ecoute));
	printf("Un client est connecté \n");
	return 0;
}
