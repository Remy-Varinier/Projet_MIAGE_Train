#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include "serveur.h"

#define MAX 100

struct Horaire decoupe_horaire(char *horaire){
	struct Horaire h;
	sscanf(horaire,"%d:%d",&h.heure,&h.minute);
	
	return h;
}

struct Train decoupe_ligne(char *ligne_train){
	char *pv=NULL;
	int i=0;
	struct Train tchouTchou;
	pv = strtok(ligne_train, ";");
	while(pv != NULL){
		switch(i){
			case 0:
				tchouTchou.num_train = atoi(pv);
				break;
			case 1:
				strcpy(tchouTchou.ville_dep,pv);
				break;
			case 2:
				strcpy(tchouTchou.ville_arr,pv);
				break;
			case 3:
				tchouTchou.h_depart = decoupe_horaire(pv);
				break;
			case 4:
				tchouTchou.h_arrivee = decoupe_horaire(pv);
				break;
			case 5:
				tchouTchou.prix = atof(pv);
				break;
			case 6:
				strcpy(tchouTchou.option,pv);
				break;
		}
		pv = strtok(NULL, ";");
		i++;
	}
	return tchouTchou;
}

int main(int argc, char *argv[]){
    FILE *fichier = NULL;
    fichier = fopen("/ext/gourdons/Bureau/Projet_MIAGE_Train/Data/Trains.txt", "r");
    if (fichier != NULL){
		// On peut lire dans le fichier
		char line [ 128 ]; /* or other suitable maximum line size */
        int i = 0;
		struct Train tab_train[50]; 
		while ( fgets ( line, sizeof line, fichier ) != NULL ) /* read a line */
		{
			 tab_train[i] = decoupe_ligne(line);
			 printf("num : %d\n", tab_train[i].num_train); 
			 printf("ville depart : %s\n", tab_train[i].ville_dep);
			 printf("ville d'arrivée : %s\n", tab_train[i].ville_arr);
			 printf("heure départ : %02d", tab_train[i].h_depart.heure);
			 printf(": %02d\n", tab_train[i].h_depart.minute);
			 printf("heure d'arrivée : %02d", tab_train[i].h_arrivee.heure);
			 printf(": %02d\n", tab_train[i].h_arrivee.minute);
			 printf("prix : %.2f\n", tab_train[i].prix);
			 printf("option : %s\n", tab_train[i].option);
			 i++;
		}
        fclose(fichier);
    }else{
        // On affiche un message d'erreur
        printf("Impossible d'ouvrir le fichier Trains.txt \n");
    }
    return 0;
}
