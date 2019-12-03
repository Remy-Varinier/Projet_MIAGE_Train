#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "serveur.h"
#include "module_heure.h"


void liste_trains_horaires(struct Train tab_train[], char *ville_depart, char *ville_arrivee, struct Horaire horaire_depart , struct Train tab_res[]){
	int i = 0;
	int nbres = 0;
	int h_d = heureVersMinutes(horaire_depart);
	int hTrainD;
	while(tab_train[i].ville_dep != NULL){
		if(strcmp(ville_depart, tab_train[i].ville_dep) == 0 && strcmp(ville_arrivee, tab_train[i].ville_arr) == 0){
			hTrainD = heureVersMinutes(tab_train[i].h_depart);
			if(h_d-60 < hTrainD && h_d+60 > hTrainD){
				tab_res[nbres] = tab_train[i];
				nbres++;
			}
		}
	}
}

void liste_trains_tranche_horaire(struct Train tab_train[], char *ville_depart, char *ville_arrivee, struct Horaire horaire_depart1, struct Horaire horaire_depart2, struct Train tab_res[]){
	int i = 0;
	int nbres = 0;
	int h_d1 = heureVersMinutes(horaire_depart1);
	int h_d2 = heureVersMinutes(horaire_depart2);
	if(h_d1 > h_d2){
		int tmp = h_d1;
		h_d1 = h_d2;
		h_d2 = tmp;
	}
	int hTrainD;
	while(tab_train[i].ville_dep != NULL){
		if(strcmp(ville_depart, tab_train[i].ville_dep) == 0 && strcmp(ville_arrivee, tab_train[i].ville_arr) == 0){
			hTrainD = heureVersMinutes(tab_train[i].h_depart);
			if(h_d1 < hTrainD && h_d2 > hTrainD){
				tab_res[nbres] = tab_train[i];
				nbres++;
			}
		}
	}
}
void liste_trains_villes(struct Train tab_train[], char *ville_depart, char *ville_arrivee, struct Train tab_res[]){
	int i = 0;
	int nbres = 0; 
	while(tab_train[i].ville_dep != NULL){
		if(strcmp(ville_depart, tab_train[i].ville_dep) == 0 && strcmp(ville_arrivee, tab_train[i].ville_arr) == 0){
			tab_res[nbres] = tab_train[i];
			nbres++;
		}
		i++;
	}
}
