#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "estruturas.h"
#include "func_areas.h"
#include "func_animais.h"
#include "funcoes.h"
#include "util.h"

void main(void) {
	int menuopt, last_id, last_animal_id, tType=-1, tCap, tNR=0, t1=-1, t2=-2, t3=-3, valid1=0, valid2=0, valid3=0, id=0;

	Areas *zAreas = NULL;
	Animais *zAnimais = NULL;

	zAreas = malloc(sizeof(Areas));
	zAnimais = malloc(sizeof(Animais));

	dispIntro();
	printf("\n");

	zAreas = readAreas(zAreas);
	last_id = getLastAreaID(zAreas);
	zAnimais = readAnimais(zAnimais);
	last_animal_id = getLastAnimalID(zAnimais);

	printf("READY!\n");

	for(;;){
		dispArea(zAreas);
		dispAnimais(zAnimais);
		menuopt = menu();
		if(menuopt == 0) break;
		if(menuopt == 11){
			last_id++;
			tType=tNR=t1=t2=t3=-1; //reset vars
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
					while(t1 >= last_id || t1 < 1){
						printf("ID fronteira 1: ");
						scanf("%d", &t1);
					}
					if(nrFront(zAreas, t1) >= 3){
						printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
					}else{
						valid1=1;
					}
				}
				zAreas = addAreaEnd(zAreas, last_id, tType, tCap, tNR, t1, -1, -1);
				zAreas = addFronteira(zAreas, t1, last_id);
				valid1=0;
			}else if(tNR == 2){
				while (valid1 != 1) {
					while(t1 >= last_id || t1 < 1){
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
					while(t2 >= last_id || t2 < 1 || t2 == t1){
						printf("ID fronteira 2: ");
						scanf("%d", &t2);
					}
					if(nrFront(zAreas, t2) >= 3){
						printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
					}else{
						valid2=1;
					}
				}
				zAreas = addAreaEnd(zAreas, last_id, tType, tCap, tNR, t1, t2, -1);
				zAreas = addFronteira(zAreas, t1, last_id);
				zAreas = addFronteira(zAreas, t2, last_id);
				valid1=0;
				valid2=0;
			}else if(tNR == 3){
				while (valid1 != 1) {
					while(t1 >= last_id || t1 < 1){
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
					while(t2 >= last_id || t2 < 1 || t2 == t1){
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
					while(t3 >= last_id || t3 < 1 || t3 == t1 && t3 == t2){
						printf("ID fronteira 2: ");
						scanf("%d", &t3);
					}
					if(nrFront(zAreas, t3) >= 3){
						printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
					}else{
						valid3=1;
					}
				}
				zAreas = addAreaEnd(zAreas, last_id, tType, tCap, tNR, t1, t2, t3);
				zAreas = addFronteira(zAreas, t1, last_id);
				zAreas = addFronteira(zAreas, t2, last_id);
				zAreas = addFronteira(zAreas, t3, last_id);
				valid1=0;
				valid2=0;
				valid3=0;
			}
			printf("Area Adicionada!!\n");
		}
		if(menuopt == 12){
			valid1=0;
			do{
				printf("ID da area a remover: ");
				scanf("%d", &id);
				if(pesoActArea(zAreas, id)!=0){
					printf("Area selecionada ainda tem animais!\n");
					valid1=0;
				}else{
					valid1=1;
				}
			}while (valid1!=1);
			zAreas = rmArea(zAreas, id);
			zAreas = rmFronteira(zAreas, id);
			last_id = getLastAreaID(zAreas);
		}
		if(menuopt == 211){//adicionar animal via ficheiro
			printf("falta implementar!\n");
		}
		if(menuopt == 212){//adicionar animal via terminal
			fflush(stdin);
			int aID, aPeso, aPai, aMae, Afilho, aLoc;
			char anome[100], aespecie[100];
			printf("\nNome do animal: ");
			gets(anome);
			printf("Especie do animal: ");
			gets(aespecie);
			printf("Peso do animal: ");
			scanf("%d", &aPeso);
			printf("Localizacao do animal: ");
			scanf("%d", &aLoc);
			zAnimais = addAnimaisEnd(zAnimais,last_animal_id+1,aespecie,anome,aPeso,aLoc,-1,-1,-1);
			last_animal_id++;
			printf("Animal adicionado!\n\n");
		}
		if(menuopt == 22){//remover animal
			printf("falta implementar!\n");
		}
	}

	saveAreas(zAreas);
	saveAnimais(zAnimais);
}

int menu(void){
	int res;

	printf("\nMenu:\n\t1 - Gerir Areas\n\t2 - Gerir Animais\n\t0 - Sair\n");
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
	}else if(res == 2){
		printf("\n\t1 - Adicionar Animal\n\t2 - Remover Animal\n");
		printf("Escolha: ");
		fflush(stdin);
		scanf("%d", &res);
		if(res == 1){
			printf("\n\t1 - Adicionar via ficheiro\n\t2 - Adicionar via terminal\n\t3 - Cancelar\n");
			printf("Escolha: ");
			fflush(stdin);
			scanf("%d", &res);
			if(res == 1) return 211;
			if(res == 2) return 212;
			if(res == 3) return -1;
		};
		if(res == 2) return 22;
	}
}
