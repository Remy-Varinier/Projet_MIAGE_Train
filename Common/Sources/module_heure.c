#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "../Headers/module_heure.h"

int heureVersMinutes(struct Horaire h){
	int minutes = ((h.heure)*60) + (h.minutes);
	return minutes;
}