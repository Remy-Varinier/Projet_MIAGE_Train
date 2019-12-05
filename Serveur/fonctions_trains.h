void listBonnesVilles(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct TabTrain *res);

void listHoraire(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire horaire_depart, struct TabTrain *res);

void listTrancheHoraire(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire horaire1, struct Horaire horaire2, struct TabTrain *res);

void triDep(struct TabTrain *trains);

int getTrainDep(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire hDep, struct TabTrain *train);

int getTrainDepArr(struct TabTrain tabTrain, char* villeDep, char* villeAr, struct Horaire hDep, struct Horaire hDep2, struct TabTrain *train);

double option(struct Train train);

struct TabTrain meilleur_prix(struct TabTrain tab_train);

int duree(struct Train train);

struct TabTrain duree_optimum(struct TabTrain tab_train);
