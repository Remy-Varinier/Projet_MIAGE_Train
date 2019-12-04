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
	strcpy(train.option,"NULL");
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
				if(strcmp(pv,"\n")!=0)
					strcpy(train.option,pv);
				break;
		}
		pv = strtok(NULL, ";");
		i++;
	}
	return train;
}

/* fonction qui lit un fichier ligne par ligne et qui applique la fonction decoupe_ligne sur chaque ligne */
int lecture_fichier(FILE *fichier, struct TabTrain *tab_train){
    int i = 0;
    fichier = fopen("Data/Trains.txt", "r"); /* ouverture du fichier */
    if (fichier != NULL){
		// On peut lire dans le fichier
		char line [128]; /* tableau du nombre de ligne maximum */
        
		while (fgets(line, sizeof(line), fichier) != NULL) { /* lire une ligne */
			 (*tab_train).trains[i] = decoupe_ligne(line);
			 struct Train *t = (*tab_train).trains;
			 printf("num : %d\n", t[i].num_train); 
			 printf("ville depart : %s\n", t[i].ville_dep);
			 printf("ville d'arrivée : %s\n", t[i].ville_arr);
			 printf("heure départ : %02d", t[i].h_depart.heure);
			 printf(": %02d\n", t[i].h_depart.minute);
			 printf("heure d'arrivée : %02d", t[i].h_arrivee.heure);
			 printf(": %02d\n", t[i].h_arrivee.minute);
			 printf("prix : %.2f\n", t[i].prix);
			printf("option : %s\n", t[i].option);
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

