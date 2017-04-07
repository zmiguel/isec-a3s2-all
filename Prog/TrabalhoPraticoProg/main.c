#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "estruturas.h"
#include "funcoes.h"

void main(void) {
	int menuopt, nr_areas;

	Areas *zAreas = NULL;
	Animais *zAnimais = NULL;

	zAreas = malloc(sizeof(Areas));
	zAnimais = malloc(sizeof(Animais));

	dispIntro();
	printf("\n");

	zAreas = readAreas(zAreas, &nr_areas);

	printf("READY! %d\n", nr_areas);
	dispArea(zAreas);

	//menuopt = menu();

}

int menu(void){

}
