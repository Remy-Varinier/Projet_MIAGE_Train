#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "serveur.h"
#include "module_heure.h"
#include "fonctions_trains.h"

int listBonnesVilles(struct Train tabTrain[], int size, char* villeDep, char* villeAr, struct Train res[]){
	int compt = 0;
	for(int i = 0; i < size; i++){
		if(strcmp(villeDep, tabTrain[i].ville_dep) == 0 && strcmp(villeAr, tabTrain[i].ville_arr) == 0){
			res[compt] = tabTrain[i];
			compt++;
		}
	}
	return compt;
}

 void triDep(struct Train trains[], int taille)
{
   struct Horaire temp;
   
    for(int i = 0; i < taille; i++)
    {
        for(int j = 0; j < taille + 2; j++)
        {
            if(heureVersMinutes(trains[j].h_depart) > heureVersMinutes(trains[j + 1].h_depart))
            {
                temp = trains[j].h_depart;
                trains[j].h_depart = trains[j + 1].h_depart;
                trains[j + 1].h_depart = temp;
            }
        }
    }
}



int getTrainDep(struct Train tabTrain[], int size, char* villeDep, char* villeAr, struct Horaire hDep, struct Train *train){
	struct Train trains[size];
	int taille = listBonnesVilles(tabTrain, size, villeDep, villeAr, trains);
	triDep(trains, taille);
	for(int i = 0; i < taille; i++){
		if( heureVersMinutes(trains[i].h_depart) >= heureVersMinutes(hDep)){
			*train = trains[i];
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}
	
/*
int liste_trains_horaires(struct Train tab_train[], char *ville_depart, char *ville_arrivee, struct Horaire horaire_depart , struct Train tab_res[]){
    int i = 0;
    int nbres = 0;
    int h_d = heureVersMinutes(horaire_depart);
    int hTrainD;
    while(tab_train[i].ville_dep != NULL){
        if(strcmp(ville_depart, tab_train[i].ville_dep) == 0 && strcmp(ville_arrivee, tab_train[i].ville_arr) == 0){
            hTrainD = heureVersMinutes(tab_train[i].h_depart);
            if(h_d == hTrainD){
                tab_res[nbres] = tab_train[i];
                nbres++;
            }
            else if(i==0){
            }
        }
    }
    return nbres;
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
*/
