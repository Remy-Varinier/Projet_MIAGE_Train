#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "serveur.h"


// Conversion des heures en minutes
int heureVersMinutes(struct Horaire h){
	int minutes = ((h.heure)*60) + (h.minute);
	return minutes;
}
