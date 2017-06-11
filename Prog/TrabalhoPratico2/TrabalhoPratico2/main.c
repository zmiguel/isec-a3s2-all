/*
José Miguel Dias Valdeviesso Alves
a21240042@alunos.isec.pt
P11 - Programação
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "estruturas.h"
#include "util.h"
#include "func_areas.h"
#include "func_animais.h"
#include "funcoes.h"

int main(void) {
  int menuopt, nrAreas, last_animal_id, tType = -1, tCap, tNR = 0, valid1 = 0, valid2 = 0, valid3 = 0, id = 0;
  char ch, t1[100], t2[100], t3[100], arID[100];
  bool compActive = false;
  Areas *zAreas = malloc(sizeof(Areas));
  Animais *zAnimais = NULL;

  zAnimais = malloc(sizeof(Animais));

  dispIntro();
  printf("\n");
  //compActive = checkComp();
  if (compActive) printf("Incompatibilidade entre animais LIGADA!\n");
  zAreas = readAreas(zAreas, &nrAreas);
  zAnimais = readAnimais(zAnimais, zAreas, nrAreas, compActive);
  linkAnimais(zAnimais);
  last_animal_id = getLastAnimalID(zAnimais);

  printf("READY!\n");

  for (;;) {
	//dispArea(zAreas, nrAreas);
	//dispAnimais(zAnimais);
	//printf("nrAreas: %d\n", nrAreas);
	last_animal_id = getLastAnimalID(zAnimais);
	menuopt = menu();
	if (menuopt == 0) break;
	if (menuopt == 11) {//adicionar area
	  tType = tNR = -1; //reset vars
	  do {
		printf("ID da area a adicionar: ");
		scanf("%s", &arID);
	  } while (areaExiste(zAreas, arID, nrAreas));
	  while (tType != 0 && tType != 1) {
		while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
		printf("Tipo de area (0 = jaula, 1 = espaco vedado): ");
		scanf("%d", &tType);
	  }
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  printf("Capacidade maxima: ");
	  scanf("%d", &tCap);
	  while (tNR != 1 && tNR != 2 && tNR != 3) {
		while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
		printf("Numero de Fronteiras (1/2/3): ");
		scanf("%d", &tNR);
	  }
	  if (tNR == 1) {
		while (valid1 != 1) {
		  do {
			printf("ID fronteira 1: ");
			scanf("%s", &t1);
		  } while (!areaExiste(zAreas, t1, nrAreas));
		  if (nrFront(zAreas, t1, nrAreas) >= 3) {
			printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
		  }
		  else {
			valid1 = 1;
		  }
		}
		nrAreas++;
		zAreas = addAreaEnd(zAreas, arID, tType, tCap, tNR, t1, "", "", nrAreas);
		zAreas = addFronteira(zAreas, t1, arID, nrAreas);
		valid1 = 0;
	  }
	  else if (tNR == 2) {
		while (valid1 != 1) {
		  do {
			printf("ID fronteira 1: ");
			scanf("%s", &t1);
		  } while (!areaExiste(zAreas, t1, nrAreas));
		  if (nrFront(zAreas, t1, nrAreas) >= 3) {
			printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
		  }
		  else {
			valid1 = 1;
		  }
		}
		while (valid2 != 1) {
		  do {
			printf("ID fronteira 2: ");
			scanf("%s", &t2);
		  } while ((strcmp(t1, t2) != 0) && !areaExiste(zAreas, t2, nrAreas));
		  if (nrFront(zAreas, t2, nrAreas) >= 3) {
			printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
		  }
		  else {
			valid2 = 1;
		  }
		}
		nrAreas++;
		zAreas = addAreaEnd(zAreas, arID, tType, tCap, tNR, t1, t2, "", nrAreas);
		zAreas = addFronteira(zAreas, t1, arID, nrAreas);
		zAreas = addFronteira(zAreas, t2, arID, nrAreas);
		valid1 = 0;
		valid2 = 0;
	  }
	  else if (tNR == 3) {
		while (valid1 != 1) {
		  do {
			printf("ID fronteira 1: ");
			scanf("%s", &t1);
		  } while (!areaExiste(zAreas, t1, nrAreas));
		  if (nrFront(zAreas, t1, nrAreas) >= 3) {
			printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
		  }
		  else {
			valid1 = 1;
		  }
		}
		while (valid2 != 1) {
		  do {
			printf("ID fronteira 2: ");
			scanf("%s", &t2);
		  } while ((strcmp(t1, t2) != 0) && !areaExiste(zAreas, t2, nrAreas));
		  if (nrFront(zAreas, t2, nrAreas) >= 3) {
			printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
		  }
		  else {
			valid2 = 1;
		  }
		}
		while (valid3 != 1) {
		  do {
			printf("ID fronteira 3: ");
			scanf("%s", &t3);
		  } while ((strcmp(t1, t3) != 0) && (strcmp(t2, t3) != 0) && !areaExiste(zAreas, t2, nrAreas));
		  if (nrFront(zAreas, t3, nrAreas) >= 3) {
			printf("Area selecionada ja tem o maximo de 3 fronteiras!\n");
		  }
		  else {
			valid3 = 1;
		  }
		}
		nrAreas++;
		zAreas = addAreaEnd(zAreas, arID, tType, tCap, tNR, t1, t2, t3, nrAreas);
		zAreas = addFronteira(zAreas, t1, arID, nrAreas);
		zAreas = addFronteira(zAreas, t2, arID, nrAreas);
		zAreas = addFronteira(zAreas, t3, arID, nrAreas);
		valid1 = 0;
		valid2 = 0;
		valid3 = 0;
	  }
	  printf("Area Adicionada!!\n");
	}
	if (menuopt == 12) {//remover area por id
	  valid1 = 0;
	  do {
		printf("ID da area a remover: ");
		scanf("%s", &arID);
		if (pesoActArea(zAreas, arID, nrAreas) != 0) {
		  printf("Area selecionada ainda tem animais!\n");
		  valid1 = 0;
		}
		else {
		  valid1 = 1;
		}
	  } while (valid1 != 1);
	  zAreas = rmArea(zAreas, arID, nrAreas);
	  zAreas = rmFronteira(zAreas, arID, nrAreas);
	}
	if (menuopt == 13) dispArea(zAreas, nrAreas);
	if (menuopt == 211) {//adicionar animal via ficheiro
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  printf("[NOTA] O ficheiro tem de estar na mesma pasta que o .exe deste programa!!\n");
	  printf("[NOTA] O ficheor deve estar no formato:\n\tESPECIE <tab> NOME <tab> PESO <tab> AREA_ID\n\n");
	  printf("Indique nome do ficheiro a importar: ");
	  char nfile[100];
	  fgets(nfile, sizeof(nfile), stdin);
	  strtok(nfile, "\n");
	  zAnimais = importAnimaisFile(zAnimais, zAreas, nfile, nrAreas);
	}
	if (menuopt == 212) {//adicionar animal via terminal
	  int aPeso;
	  char anome[100], aespecie[100], aLoc[100];
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  printf("\nNome do animal: ");
	  fgets(anome, sizeof(anome), stdin);
	  strtok(anome, "\n");
	  printf("Especie do animal: ");
	  fgets(aespecie, sizeof(aespecie), stdin);
	  strtok(aespecie, "\n");
	  printf("Peso do animal: ");
	  scanf("%d", &aPeso);
	  printf("Localizacao do animal: ");
	  scanf("%s", &aLoc);
	  zAnimais = addAnimaisEnd(zAnimais, zAreas, last_animal_id + 1, aespecie, anome, aPeso, aLoc, nrAreas);
	  printf("Animal adicionado!\n\n");
	}
	if (menuopt == 221) {//remover animal por id
	  int aID;
	  printf("ID do animal a remover: ");
	  scanf("%d", &aID);
	  rmAnimalID(zAnimais, zAreas, aID, nrAreas);
	  linkAnimais(zAnimais);
	}
	if (menuopt == 222) {//remover animal por nome
	  char nome[100];
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  printf("Nome do animal a remover: ");
	  fgets(nome, sizeof(nome), stdin);
	  strtok(nome, "\n");
	  rmAnimalNome(zAnimais, zAreas, nome, nrAreas);
	  linkAnimais(zAnimais);
	}
	if (menuopt == 231) {//Lista dodos os animais
	  dispAnimais(zAnimais);
	}
	if (menuopt == 232) {//Lista dodos os animais na area X
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  char aID[100];
	  printf("\nID da area a procurar: ");
	  scanf("%s", &aID);
	  dispAnimaisArea(zAnimais, aID, nrAreas);
	}
	if (menuopt == 233) {//Lista dodos os animais da especia X
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  char aespecie[100];
	  printf("\nEspecie a procurar: ");
	  fgets(aespecie, sizeof(aespecie), stdin);
	  strtok(aespecie, "\n");
	  dispAnimaisEspecie(zAnimais, aespecie);
	}
	if (menuopt == 241) {//info animal por id
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  int aID;
	  printf("\nID do animal: ");
	  scanf("%d", &aID);
	  dispAnimalID(zAnimais, aID);
	}
	if (menuopt == 242) {//info animal por nome
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  char nome[100];
	  printf("\nNome do animal: ");
	  fgets(nome, sizeof(nome), stdin);
	  strtok(nome, "\n");
	  dispAnimalNome(zAnimais, nome);
	}
	if (menuopt == 25) {//transferir animal por ID
	  int aID;
	  char destID[100];
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  printf("ID do animal a transferir: ");
	  scanf("%d", &aID);
	  printf("ID da area destino: ");
	  scanf("%s", &destID);
	  transfAnimal(zAnimais, zAreas, aID, destID, nrAreas);
	}
	if (menuopt == 261) {//Criar Filho a partir de 1 animal
	  char nome[100];
	  int aID;
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  printf("Indique o ID do animal que vai ter o filho: ");
	  scanf("%d", &aID);
	  printf("Indique o nome que deseja dar ao Filho: ");
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  fgets(nome, sizeof(nome), stdin);
	  strtok(nome, "\n");
	  criaFilho1(zAnimais, zAreas, aID, nome, nrAreas);
	}
	if (menuopt == 262) {//Criar Filho a partir de 2 animais
	  char nome[100];
	  int aID1 = 0, aID2 = 0;
	  printf("\nNOTA!!!\n\tPara poder ser criado um filho a partir de 2 animais o seguinte tem de ser verdade:\n\n\t- Ambos os animais da mesma especie;\n\t- Ambos os animais na mesma area do Zoo.\n\n");
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  printf("Indique o ID do primeiro animal que vai ter o filho: ");
	  scanf("%d", &aID1);
	  printf("Indique o ID do segundo animal que vai ter o filho: ");
	  scanf("%d", &aID2);
	  while (verifyFilho2(zAnimais, aID1, aID2) != true) {
		printf("Animais incompativeis para criar um filho!\n");
		printf("Indique o ID do segundo animal que vai ter o filho: ");
		scanf("%d", &aID2);
	  }
	  printf("Indique o nome que deseja dar ao Filho: ");
	  while (((ch = getchar()) != EOF) && (ch != '\n')) putchar(ch); // limpa o buffer stdin para usar o fgets
	  fgets(nome, sizeof(nome), stdin);
	  strtok(nome, "\n");
	  criaFilho2(zAnimais, zAreas, aID1, aID2, nome, nrAreas);
	}
  }

  saveAreas(zAreas, nrAreas);
  saveAnimais(zAnimais);
}

int menu(void) {
  int res;

  printf("\nMenu:\n\t1 - Gerir Areas\n\t2 - Gerir Animais\n\t0 - Sair\n");
  printf("Escolha: ");

  scanf("%d", &res);

  if (res == 0) {
	return 0;
  }
  else if (res == 1) {
	printf("Areas:\n\t1 - Adicionar Area\n\t2 - Remover Area\n\t3 - Listagem todas as areas\n\t4 - Cancelar\n");
	printf("Escolha: ");
	scanf("%d", &res);
	if (res == 1) return 11;
	if (res == 2) return 12;
	if (res == 3) return 13;
	if (res == 4) return -1;
  }
  else if (res == 2) {
	printf("Animais:\n\t1 - Adicionar Animal\n\t2 - Remover Animal\n\t3 - Listagem Animais\n\t4 - Info\n\t5 - Transferir animal\n\t6 - Criar filho\n\t7 - Cancelar\n");
	printf("Escolha: ");
	scanf("%d", &res);
	if (res == 1) {
	  printf("\n\t1 - Adicionar via ficheiro\n\t2 - Adicionar via terminal\n\t3 - Cancelar\n");
	  printf("Escolha: ");
	  scanf("%d", &res);
	  if (res == 1) return 211;
	  if (res == 2) return 212;
	  if (res == 3) return -1;
	};
	if (res == 2) {
	  printf("Remover animal por:\n\t1 - ID\n\t2 - Nome\n\t3 - Cancelar\n");
	  printf("Escolha: ");
	  scanf("%d", &res);
	  if (res == 1) return 221;
	  if (res == 2) return 222;
	  if (res == 3) return -1;
	}
	if (res == 3) {
	  printf("Listagem de:\n\t1 - Todos os animais\n\t2 - Animais na Area X\n\t3 - Animais da especie X\n\t4 - Cancelar\n");
	  printf("Escolha: ");
	  scanf("%d", &res);
	  if (res == 1) return 231;
	  if (res == 2) return 232;
	  if (res == 3) return 233;
	  if (res == 4) return -1;
	}
	if (res == 4) {
	  printf("Info:\n\t1 - Animal por ID\n\t2 - Animais por nome\n\t3 - Cancelar\n");
	  printf("Escolha: ");
	  scanf("%d", &res);
	  if (res == 1) return 241;
	  if (res == 2) return 242;
	  if (res == 3) return -1;
	}
	if (res == 5) return 25;
	if (res == 6) {
	  printf("Criar Filho:\n\t1 - A partir de 1 animal\n\t2 - A partir de 2 animais\n\t3 - Cancelar\n");
	  printf("Escolha: ");
	  scanf("%d", &res);
	  if (res == 1) return 261;
	  if (res == 2) return 262;
	  if (res == 3) return -1;
	}
	if (res == 7) return -1;
  }
  return -1;
}
