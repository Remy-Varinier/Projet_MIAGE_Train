#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "serveur.h"
#include "module_heure.h"
#include "fonctions_trains.h"

void listBonnesVilles(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct TabTrain *res){
	int compt = 0;
	for(int i = 0; i < tabTrain.taille; i++){
		if(strcmp(villeDep, tabTrain.trains[i].ville_dep) == 0 && strcmp(villeAr, tabTrain.trains[i].ville_arr) == 0){
			(*res).trains[compt] = tabTrain.trains[i];
			compt++;
		}
	}
	(*res).taille = compt;
}

void listHoraire(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire horaire_depart, struct TabTrain *res){
	int compt = 0;
	for(int i = 0; i < tabTrain.taille; i++){
		if(strcmp(villeDep, tabTrain.trains[i].ville_dep) == 0 && strcmp(villeAr, tabTrain.trains[i].ville_arr) == 0){
			(*res).trains[compt] = tabTrain.trains[i];
			compt++;
		}
	}
	(*res).taille = compt;
}

void listTrancheHoraire(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire horaire1, struct Horaire horaire2, struct TabTrain *res){
	int compt = 0;
	for(int i = 0; i < tabTrain.taille; i++){
		if(strcmp(villeDep, tabTrain.trains[i].ville_dep) == 0 && strcmp(villeAr, tabTrain.trains[i].ville_arr) == 0){
			(*res).trains[compt] = tabTrain.trains[i];
			compt++;
		}
	}
	(*res).taille = compt;
}

 void triDep(struct TabTrain *trains){
	struct Horaire temp;
    for(int i = 0; i < trains->taille; i++){
        for(int j = 0; j < trains->taille + 2; j++){
            if(heureVersMinutes(trains->trains[j].h_depart) > heureVersMinutes(trains->trains[j + 1].h_depart)){
                temp = trains->trains[j].h_depart;
                trains->trains[j].h_depart = trains->trains[j + 1].h_depart;
                trains->trains[j + 1].h_depart = temp;
            }
        }
    }
}



int getTrainDep(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire hDep, struct Train *train){
	struct TabTrain trains;
	listBonnesVilles(tabTrain, villeDep, villeAr, &trains);
	triDep(&trains);
	for(int i = 0; i < trains.taille; i++){
		if(heureVersMinutes(trains.trains[i].h_depart) >= heureVersMinutes(hDep)){
			*train = trains.trains[i];
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}
	
double option(struct Train train){
	double prix, nv_prix;
	if (strcmp("REDUC",train.option) == 0){
		prix = train.prix;
		nv_prix = prix * (80/100);
	}else{
		if (strcmp("SUPPL",train.option) == 0){
			prix = train.prix;
			nv_prix = prix + (prix * (10/100));
		}else{
			nv_prix = train.prix;
		}
	}
	return nv_prix;
}

struct Train meilleur_prix(struct TabTrain tab_train){
	int i = 1;
	struct Train train = tab_train.trains[0];
	while(i<tab_train.taille){
		if (train.prix > tab_train.trains[i].prix){
			train = tab_train.trains[i];
		}
		i++;
	}
	return train;
}

struct Train duree_optimum(struct TabTrain tab_train){
	int i=1;
	int h1,h2,h3,h4,dh1,dh2;
	struct Train train = tab_train.trains[0];
	while(i<tab_train.taille){
		h1 = heureVersMinutes(train.h_depart);
		h2 = heureVersMinutes(train.h_arrivee);
		dh1 = h2 - h1;
		h3 = heureVersMinutes(tab_train.trains[i].h_depart);
		h4 = heureVersMinutes(tab_train.trains[i].h_arrivee);
		dh2 = h4 - h3;
		if(dh1>dh2){
			train = tab_train.trains[i];
		}
		i++;
	}
	return train;
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
