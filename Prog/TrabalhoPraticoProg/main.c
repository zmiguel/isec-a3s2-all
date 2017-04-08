#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "estruturas.h"
#include "funcoes.h"
#include "util.h"

void main(void) {
	int menuopt, nr_areas, tType=-1, tCap, tNR=0, t1=-1, t2=-2, t3=-3;

	Areas *zAreas = NULL;
	Animais *zAnimais = NULL;

	zAreas = malloc(sizeof(Areas));
	zAnimais = malloc(sizeof(Animais));

	dispIntro();
	printf("\n");

	zAreas = readAreas(zAreas, &nr_areas);

	printf("READY! %d\n", nr_areas);
	//dispArea(zAreas);
	printf("%d\t%d\t%d\n", nrFront(zAreas,1), nrFront(zAreas,2), nrFront(zAreas,3));

	for(;;){
		menuopt = menu();
		if(menuopt == 0) break;
		if(menuopt == 11){
			nr_areas++;
			while(tType != 0 && tType != 1){
				fflush(stdin);
				printf("Tipo de area (0 = jaula, 1 = espaco vedado): ");
				scanf("%d", &tType);
			}
			fflush(stdin);
			printf("Capacidade maxima: ");
			scanf("%d", &tCap);
			while(tNR != 1 && tNR != 2 && tNR != 3){
				fflush(stdin);
				printf("Numero de Fronteiras (1/2/3): ");
				scanf("%d", &tNR);
			}
			if(tNR == 1){
				while(t1 >= nr_areas || t1 < 1){
					printf("ID fronteira 1: ");
					scanf("%d", &t1);
				}
				zAreas = addAreaEnd(zAreas, nr_areas, tType, tCap, tNR, t1, -1, -1);
			}else if(tNR == 2){
				while(t1 >= nr_areas || t1 < 1){
					printf("ID fronteira 1: ");
					scanf("%d", &t1);
					while(t2 >= nr_areas || t2 < 1 || t2 == t1){
						printf("ID fronteira 2: ");
						scanf("%d", &t2);
					}
				}
				zAreas = addAreaEnd(zAreas, nr_areas, tType, tCap, tNR, t1, t2, -1);
			}else if(tNR == 3){
				while(t1 >= nr_areas || t1 < 1){
					printf("ID fronteira 1: ");
					scanf("%d", &t1);
					while(t2 >= nr_areas || t2 < 1 || t2 == t1){
						printf("ID fronteira 2: ");
						scanf("%d", &t2);
						while(t3 >= nr_areas || t3 < 1 || t3 == t1 && t3 == t2){
							printf("ID fronteira 2: ");
							scanf("%d", &t3);
						}
					}
				}
				zAreas = addAreaEnd(zAreas, nr_areas, tType, tCap, tNR, t1, t2, t3);
			}
			printf("Area Adicionada!!\n");
			dispArea(zAreas);
		}
	}

	saveAreas(zAreas);
}

int menu(void){
	int res;

	printf("\nMenu:\n\t1 - Gerir Areas\n\t0 - Sair\n");
	printf("Escolha: ");
	fflush(stdin);
	scanf("%d", &res);

	if(res == 0){
		return 0;
	}else if(res == 1){
		printf("\n\t1 - Adicionar Area\n\t2 - Remover Area\n");
		printf("Escolha: ");
		fflush(stdin);
		scanf("%d", &res);
		if(res == 1) return 11;
		if(res == 2) return 12;

	}
}
