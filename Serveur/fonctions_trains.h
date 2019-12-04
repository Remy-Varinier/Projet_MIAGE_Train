void listBonnesVilles(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct TabTrain *res);

void listHoraire(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire horaire_depart, struct TabTrain *res);

void listTrancheHoraire(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire horaire1, struct Horaire horaire2, struct TabTrain *res);

void triDep(struct TabTrain *trains);

int getTrainDep(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire hDep, struct Train *train);

double option(struct Train train);

struct Train meilleur_prix(struct TabTrain tab_train);

int duree(struct Train train);

struct Train duree_optimum(struct TabTrain tab_train);
