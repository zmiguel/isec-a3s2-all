#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "estruturas.h"
#include "util.h"
#include "func_areas.h"
#include "func_animais.h"
#include "funcoes.h"

void main(void) {
	int menuopt, last_id, last_animal_id, tType=-1, tCap, tNR=0, t1=-1, t2=-2, t3=-3, valid1=0, valid2=0, valid3=0, id=0;

	Areas *zAreas = NULL;
	Animais *zAnimais = NULL;

	zAreas = malloc(sizeof(Areas));
	zAnimais = malloc(sizeof(Animais));

	dispIntro();
	printf("\n");

	zAreas = readAreas(zAreas);
	zAreas = linkAreas(zAreas);
	last_id = getLastAreaID(zAreas);
	zAnimais = readAnimais(zAnimais, zAreas);
	last_animal_id = getLastAnimalID(zAnimais);

	printf("READY!\n");

	for(;;){
		dispArea(zAreas);
		dispAnimais(zAnimais);
		last_id = getLastAreaID(zAreas);
		last_animal_id = getLastAnimalID(zAnimais);
		menuopt = menu();
		if(menuopt == 0) break;
		if(menuopt == 11){//adicionar area
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
		if(menuopt == 12){//remover area por id
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
		if(menuopt == 13) dispArea(zAreas);
		if(menuopt == 211){//adicionar animal via ficheiro
			fflush(stdin);
			printf("[NOTA] O ficheiro tem de estar na mesma pasta que o .exe deste programa!!\n");
			printf("[NOTA] O ficheor deve estar no formato:\n\tESPECIE <tab> NOME <tab> PESO <tab> AREA_ID\n\n");
			printf("Indique nome do ficheiro a importar: ");
			char nfile[100];
			scanf("%s", nfile);
			zAnimais = importAnimaisFile(zAnimais, nfile, zAreas);
		}
		if(menuopt == 212){//adicionar animal via terminal
			fflush(stdin);
			int aID, aPeso, aPai, aMae, Afilho, aLoc;
			char anome[100], aespecie[100];
			printf("\nNome do animal: ");
			scanf("%s", anome);
			printf("Especie do animal: ");
			scanf("%s", aespecie);
			printf("Peso do animal: ");
			scanf("%d", &aPeso);
			printf("Localizacao do animal: ");
			scanf("%d", &aLoc);
			zAnimais = addAnimaisEnd(zAnimais,zAreas,last_animal_id+1,aespecie,anome,aPeso,aLoc,-1);
			printf("Animal adicionado!\n\n");
		}
		if(menuopt == 221){//remover animal por id
			int aID;
			printf("ID do animal a remover: ");
			scanf("%d", &aID);
			rmAnimalID(zAnimais, zAreas, aID);
		}
		if(menuopt == 222){//remover animal por nome
			char nome[100];
			printf("Nome do animal a remover: ");
			scanf("%s", nome);
			rmAnimalNome(zAnimais, zAreas, nome);
		}
		if(menuopt == 231){//Lista dodos os animais
			dispAnimais(zAnimais);
		}
		if(menuopt == 232){//Lista dodos os animais na area X
			fflush(stdin);
			int aID;
			printf("\nID da area a procurar: ");
			scanf("%d", &aID);
			dispAnimaisArea(zAnimais, zAreas, aID);
		}
		if(menuopt == 233){//Lista dodos os animais da especia X
			fflush(stdin);
			char aespecie[100];
			printf("\nEspecie a procurar: ");
			scanf("%s", aespecie);
			dispAnimaisEspecie(zAnimais, aespecie);
		}
		if(menuopt == 241){//info animal por id
			fflush(stdin);
			int aID;
			printf("\nID do animal: ");
			scanf("%d", &aID);
			dispAnimalID(zAnimais, aID);
		}
		if(menuopt == 242){//info animal por nome
			fflush(stdin);
			char nome[100];
			printf("\nNome do animal: ");
			scanf("%s", nome);
			dispAnimalNome(zAnimais, nome);
		}
		if(menuopt == 25){//transferir animal por ID
			int aID, destID;
			fflush(stdin);
			printf("ID do animal a transferir: ");
			scanf("%d", &aID);
			printf("ID da area destino: ");
			scanf("%d", &destID);
			transfAnimal(zAnimais, zAreas, aID, destID);
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
		printf("Areas:\n\t1 - Adicionar Area\n\t2 - Remover Area\n\t3 - Listagem todas as areas\n\t4 - Cancelar\n");
		printf("Escolha: ");
		fflush(stdin);
		scanf("%d", &res);
		if(res == 1) return 11;
		if(res == 2) return 12;
		if(res == 3) return 13;
		if(res == 4) return -1;
	}else if(res == 2){
		printf("Animais:\n\t1 - Adicionar Animal\n\t2 - Remover Animal\n\t3 - Listagem Animais\n\t4 - Info\n\t5 - Transferir animal\n\t6 - Cancelar\n");
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
		if(res == 2){
			printf("Remover animal por:\n\t1 - ID\n\t2 - Nome\n\t3 - Cancelar\n");
			printf("Escolha: ");
			fflush(stdin);
			scanf("%d", &res);
			if(res == 1) return 221;
			if(res == 2) return 222;
			if(res == 3) return -1;
		}
		if(res == 3){
			printf("Listagem de:\n\t1 - Todos os animais\n\t2 - Animais na Area X\n\t3 - Animais da especie X\n\t4 - Cancelar\n");
			printf("Escolha: ");
			fflush(stdin);
			scanf("%d", &res);
			if(res == 1) return 231;
			if(res == 2) return 232;
			if(res == 3) return 233;
			if(res == 4) return -1;
		}
		if(res == 4){
			printf("Info:\n\t1 - Animal por ID\n\t2 - Animais por nome\n\t3 - Cancelar\n");
			printf("Escolha: ");
			fflush(stdin);
			scanf("%d", &res);
			if(res == 1) return 241;
			if(res == 2) return 242;
			if(res == 3) return -1;
		}
		if(res == 5) return 25;
		if(res == 6) return -1;
	}
}
