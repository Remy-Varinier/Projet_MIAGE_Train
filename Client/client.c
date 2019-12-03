#include <stdio.h>
#include <string.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/uio.h>

#include "../Common/Headers/reseau.h"

void enleverBack(char *entree){
	int taille = strlen(entree);
	if(entree[taille-1] == '\n'){
		entree[taille-1] = '\0';
	}
}

int main(int argc,char *argv[]){
	char ville_depart[MAX];
	char ville_arrivee[MAX];
	char horaire1[MAX];
	char horaire2[MAX];
	char *param;
	char *entree;
	int echange = socketClient("localhost", PORT);
	do{
		printf("Entrez une ville de départ :\n");
		fgets(ville_depart, MAX, stdin);
		enleverBack(ville_depart);
		strcat(entree,ville_depart);
		strcat(entree,";");
		printf("Entrez une ville d'arrivée :\n");
		fgets(ville_arrivee, MAX, stdin);
		enleverBack(ville_arrivee);
		strcat(entree,ville_arrivee);
		strcat(entree,";");
		printf("Voulez-vous entrer :\n\tUn horaire de départ ? (1)\n\tUn intervalle pour l'horaire de départ ? (2)\n\tPas de préférence d'horaire ? (0)\n");
		scanf("%s",param);
		if(strcmp(param,"1") == 0){
			printf("Entrez un horaire de départ :\n");
			fgets(horaire, MAX, stdin);
			enleverBack(horaire);
			strcat(entree,ville_depart);
			strcat(entree,";");
		} else if(strcmp(param,"2") == 0){
			printf("Entrez un horaire de départ min :\n");
			fgets(horaire1, MAX, stdin);
			enleverBack(horaire1);
			strcat(entree,horaire1);
			strcat(entree,";");
			printf("Entrez un horaire de départ max :\n");
			fgets(horaire2, MAX, stdin);
			enleverBack(horaire2);
			strcat(entree,horaire2);
		}
		write(echange, entree, strlen(entree)+1);
		
	}while(strcmp(entree, "exit") != 0);
	return 0;
}
