#define MAX_CAR 256		      /* Nombre maximum de caractères possible*/

struct Horaire{
	int heure; 
	int minute; 
} ;

struct Train{ 
	int num_train;            /* numéro du train */
	char ville_dep[MAX_CAR];  /* ville de départ */
	char ville_arr[MAX_CAR];  /* ville d'arrivée */
	struct Horaire h_depart;  /* heure de départ */
	struct Horaire h_arrivee; /* heure d'arrivée */
	double prix;               /* prix usuel */
	char option[5];          /* champ optionnel:
								 REDUC si le train bénéficie d'une remise de 20%
								 SUPPL si le train fait l'objet d'un supplément de 10%
							   */
};

