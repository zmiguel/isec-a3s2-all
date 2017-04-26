#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "estruturas.h"
#include "funcoes.h"
#include "util.h"

void main(void) {
	int menuopt, last_id, tType=-1, tCap, tNR=0, t1=-1, t2=-2, t3=-3, valid1=0, valid2=0, valid3=0, id=0;

	Areas *zAreas = NULL;
	Animais *zAnimais = NULL;

	zAreas = malloc(sizeof(Areas));
	zAnimais = malloc(sizeof(Animais));

	dispIntro();
	printf("\n");

	zAreas = readAreas(zAreas, &last_id);
	last_id = getLastAeraID(zAreas);

	printf("READY!\n");
	dispArea(zAreas);

	for(;;){
		menuopt = menu();
		if(menuopt == 0) break;
		if(menuopt == 11){
			last_id++;
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
				while(valid1 != 1){
					while(t1 >= nr_areas || t1 < 1){
						printf("ID fronteira 1: ");
						scanf("%d", &t1);
					}
					if(nrFront(zAreas, t1) >= 3){
						printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
					}else{
						valid1=1;
					}
				}
				zAreas = addAreaEnd(zAreas, nr_areas, tType, tCap, tNR, t1, -1, -1);
				zAreas = addFronteira(zAreas, t1, nr_areas);
				valid1=0;
			}else if(tNR == 2){
				while (valid1 != 1) {
					while(t1 >= nr_areas || t1 < 1){
						printf("ID fronteira 1: ");
						scanf("%d", &t1);
					}
					if(nrFront(zAreas, t1) >= 3){
						printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
					}else{
						valid1=1;
					}
				}
				while (valid2 != 1) {
					while(t2 >= nr_areas || t2 < 1 || t2 == t1){
						printf("ID fronteira 2: ");
						scanf("%d", &t2);
					}
					if(nrFront(zAreas, t2) >= 3){
						printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
					}else{
						valid2=1;
					}
				}
				zAreas = addAreaEnd(zAreas, nr_areas, tType, tCap, tNR, t1, t2, -1);
				zAreas = addFronteira(zAreas, t1, nr_areas);
				zAreas = addFronteira(zAreas, t2, nr_areas);
				valid1=0;
				valid2=0;
			}else if(tNR == 3){
				while (valid1 != 1) {
					while(t1 >= nr_areas || t1 < 1){
						printf("ID fronteira 1: ");
						scanf("%d", &t1);
					}
					if(nrFront(zAreas, t1) >= 3){
						printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
					}else{
						valid1=1;
					}
				}
				while (valid2 != 1) {
					while(t2 >= nr_areas || t2 < 1 || t2 == t1){
						printf("ID fronteira 2: ");
						scanf("%d", &t2);
					}
					if(nrFront(zAreas, t2) >= 3){
						printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
					}else{
						valid2=1;
					}
				}
				while (valid3 != 1) {
					while(t3 >= nr_areas || t3 < 1 || t3 == t1 && t3 == t2){
						printf("ID fronteira 2: ");
						scanf("%d", &t3);
					}
					if(nrFront(zAreas, t3) >= 3){
						printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
					}else{
						valid3=1;
					}
				}
				zAreas = addAreaEnd(zAreas, nr_areas, tType, tCap, tNR, t1, t2, t3);
				zAreas = addFronteira(zAreas, t1, nr_areas);
				zAreas = addFronteira(zAreas, t2, nr_areas);
				zAreas = addFronteira(zAreas, t3, nr_areas);
				valid1=0;
				valid2=0;
				valid3=0;
			}
			printf("Area Adicionada!!\n");
			dispArea(zAreas);
		}
		if(menuopt == 12){
			do{
				printf("ID da area a remover: ");
				scanf("%d", %id);
			}while (pesoActArea(id)!=0);
			zAreas = rmArea(zAreas, id);
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
