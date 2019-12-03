#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "module_heure.h"

int heureVersMinutes(struct Horaire h){
	int minutes = ((h.heure)*60) + (h.minutes);
	return minutes;
}

int compTemps(int h1, h2){
	if(h1<h2)
		return 1;
	if(h1>h2)
		return -1;
	return 0;
}
