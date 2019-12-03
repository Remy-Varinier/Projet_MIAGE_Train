#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

#include "serveur.h"
#include "lire_fichier.h"

#define MAX 100

// fonction qui renvoit les heures et les minutes qui sont sous cette forme:"10:25"
struct Horaire decoupe_horaire(char *horaire){
	struct Horaire h;
	sscanf(horaire,"%d:%d",&h.heure,&h.minute);
	return h;
}

// fonction qui découpe une ligne de train en fonction des ;
struct Train decoupe_ligne(char *ligne_train){
	char *pv=NULL;
	int i=0;
	struct Train train;
	pv = strtok(ligne_train, ";");
	//tant que la ligne n'est pas vide
	while(pv != NULL){
		switch(i){
			case 0:
				train.num_train = atoi(pv);
				break;
			case 1:
				strcpy(train.ville_dep,pv);
				break;
			case 2:
				strcpy(train.ville_arr,pv);
				break;
			case 3:
				train.h_depart = decoupe_horaire(pv);
				break;
			case 4:
				train.h_arrivee = decoupe_horaire(pv);
				break;
			case 5:
				train.prix = atof(pv);
				break;
			case 6:
				strcpy(train.option,pv);
				break;
		}
		pv = strtok(NULL, ";");
		i++;
	}
	return train;
}

int lecture_fichier(FILE *fichier, struct TabTrain *tab_train){
    int i = 0;
    fichier = fopen("/ext/gourdons/Bureau/Projet_MIAGE_Train/Data/Trains.txt", "r"); /* ouverture du fichier */
    if (fichier != NULL){
		// On peut lire dans le fichier
		char line [128]; /* tableau du nombre de ligne maximum */
        
		while (fgets(line, sizeof(line), fichier) != NULL) { /* lire une ligne */
			 (*tab_train).trains[i] = decoupe_ligne(line);
			 i++;
		}
        fclose(fichier); /* fermeture du fichier */
        (*tab_train).taille = i;
    }else{
        // Erreur d'ouverture de fichier
        printf("Impossible d'ouvrir le fichier Trains.txt \n");
    }
    return 0;
}

