#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "serveur.h"
#include "fonctions_trains.h"

/* récupère les trains ayant pour ville de départ villeDep 
 * et pour ville d'arrivée villeAr
*/
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

/* fonction qui trie les trains dans l'ordre croissant en fonction de l'horaire de départ */
void triDep(struct TabTrain *trains){
	struct Train temp;
    for(int i = 0; i < trains->taille; i++){
        for(int j = 0; j < trains->taille; j++){
            if(heureVersMinutes(trains->trains[i].h_depart) < heureVersMinutes(trains->trains[j].h_depart)){
                temp = trains->trains[i];
                trains->trains[i] = trains->trains[j];
                trains->trains[j] = temp;
            }
        }
    }
}

/* fonction qui renvoit un train satisfaisant certains critères 
 * ou qui renvoit à défaut le premier train possible à partir de l'horaire de départ demandé
*/
int getTrainDep(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire hDep, struct TabTrain *train){
	struct TabTrain trains;
	listBonnesVilles(tabTrain, villeDep, villeAr, &trains);
	triDep(&trains);
	for(int i = 0; i < trains.taille; i++){
		
		if(heureVersMinutes(trains.trains[i].h_depart) >= heureVersMinutes(hDep)){
			train->trains[0] = trains.trains[i];
			train->taille = 1;
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

/* fonction qui récupère les trains ayant une ville de départ, une ville d'arrivée, 
 * et une tranche horaire de départ 
*/
int getTrainDepArr(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire hDep, struct Horaire hDep2, struct TabTrain* bonTrain){
	struct TabTrain trains;
	listBonnesVilles(tabTrain, villeDep, villeAr, &trains);
	triDep(&trains);
	int k=0;
	for(int i = 0; i < trains.taille; i++){
		if(heureVersMinutes(trains.trains[i].h_depart) >= heureVersMinutes(hDep) && heureVersMinutes(trains.trains[i].h_depart) <= heureVersMinutes(hDep2) ){
			bonTrain->trains[k] = trains.trains[i];
			k++;
		}
	}
	bonTrain->taille = k;
	return EXIT_SUCCESS;;
}
	
/* fonction qui calcule le nouveau prix en fonction de l'option demandé:
 * REDUC -> baisse le prix de 20%
 * SUPPL -> augmente le prix de 10%
 */
double option(struct Train train){
	double prix, nv_prix;
	if (strcmp("REDUC",train.option) == 0){
		prix = train.prix;
		nv_prix = prix * (80.0/100);
	}else{
		if (strcmp("SUPPL",train.option) == 0){
			prix = train.prix;
			nv_prix = prix + (prix * (10.0/100));
		}else{
			nv_prix = train.prix;
		}
	}
	return nv_prix;
}

/* fonction qui permet de trouver quel est le train qui est le moins cher pour le trajet */
struct TabTrain meilleur_prix(struct TabTrain tab_train){
	int i = 1;
	struct Train train = tab_train.trains[0];
	while(i<tab_train.taille){
		if (train.prix > tab_train.trains[i].prix){
			train = tab_train.trains[i];
		}
		i++;
	}
	struct TabTrain t;
	t.taille = 1;
	t.trains[0] = train;
	return t;
}

/* fonction qui calcule la durée d'un train */
int duree(struct Train train){
	int duree = 0;
	int h1,h2;
	h1 = heureVersMinutes(train.h_depart);
	h2 = heureVersMinutes(train.h_arrivee);
	duree = h2 - h1;
	return duree;
}

/*struct Train duree_optimum(struct TabTrain tab_train){
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
*/

/* fonction qui permet de trouver quel est le train qui met le moins de temps pour le trajet */
struct TabTrain duree_optimum(struct TabTrain tab_train){
	int i=1;
	int dh1,dh2;
	struct Train train = tab_train.trains[0];
	while(i<tab_train.taille){
		dh1 = duree(train);
		dh2 = duree(tab_train.trains[i]);
		if(dh1>dh2){
			train = tab_train.trains[i];
		}
		i++;
	}
	struct TabTrain t;
	t.taille = 1;
	t.trains[0] = train;
	return t;
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

/*
 * void listHoraire(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire horaire_depart, struct TabTrain *res){
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
*/
