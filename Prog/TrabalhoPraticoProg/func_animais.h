Animais * addAnimaisEnd(Animais *tAnimais, Areas *tAreas, int id, char *especie, char *nome, int peso, int locID, int pai, int mae) {
	Animais *aux = tAnimais;
	Areas *ta = tAreas;
	Areas *move;

	while (aux->prox != NULL) {
		aux = aux->prox;
	}
	aux->prox = malloc(sizeof(Animais));
	aux->prox->id = id;
	strcpy(aux->prox->especie, especie);
	strcpy(aux->prox->nome, nome);
	aux->prox->peso = peso;
	aux->prox->loc.id = locID;
	while(ta->prox != NULL){
		move = malloc(sizeof(Areas));
		ta = ta->prox;
		if(ta->id == locID){
			aux->prox->loc.area = ta;
			ta->pesoAct += peso;
			break;
		}
	}
	aux->prox->familia.paiID = pai;
	aux->prox->familia.pai = NULL;
	aux->prox->familia.maeID = mae;
	aux->prox->familia.mae = NULL;
	aux->prox->prox = NULL;
	return tAnimais;
}

Animais * readAnimais(Animais *tAnimais, Areas *tAreas){
	Animais *temp = tAnimais;
	Areas *ta = tAreas;
	Animais *read;
	FILE *f;
	int end;
	printf("A procurar ficheiro de Animais...\n");
	f = fopen("animais.dat","rb");
	if(f==NULL){
		printf("Fichero de animais nao encontrado, ou erro a abrir!\n");
		return tAnimais;
	}
	printf("Ficheiro de animais encontrado e aberto!\n");
	while(!feof(f)){
		ta = tAreas;
		read = malloc(sizeof(Animais));
		end = fread(read,sizeof(Animais),1,f);
		if(end!=1) break;
		while(ta->prox != NULL){
			ta = ta->prox;
			if(ta->id == read->loc.id){
				if((ta->pesoAct + read->peso) > ta->cap){//area ia ficar com peso a mais!
					if(ta->front1.area){
						if((ta->front1.area->pesoAct + read->peso) <= ta->front1.area->cap){
							ta->front1.area->pesoAct += read->peso;
							read->loc.id = ta->front1.area->id;
							read->loc.area = ta->front1.area;
							temp->prox = read;
							temp = temp->prox;
							break;
						}
					}
					if(ta->front2.area){
						if((ta->front2.area->pesoAct + read->peso) <= ta->front2.area->cap){
							ta->front2.area->pesoAct += read->peso;
							read->loc.id = ta->front2.area->id;
							read->loc.area = ta->front2.area;
							temp->prox = read;
							temp = temp->prox;
							break;
						}
					}
					if(ta->front3.area){
						if((ta->front3.area->pesoAct + read->peso) <= ta->front3.area->cap){
							ta->front3.area->pesoAct += read->peso;
							read->loc.id = ta->front3.area->id;
							read->loc.area = ta->front3.area;
							temp->prox = read;
							temp = temp->prox;
							break;
						}
					}
				}else{//area tem capacidade para ter o animal
					ta->pesoAct += read->peso;
					read->loc.area = ta;
					temp->prox = read;
					temp = temp->prox;
					break;
				}
			}
		}
	}

	fclose(f);
	return tAnimais;
}

Animais * importAnimaisFile(Animais *tAnimais, char *nfile, Areas *tAreas){
	Animais *temp = tAnimais;
	Areas *ta = tAreas;
	int last_id = getLastAnimalID(tAnimais), loc, peso;
	char nome[100], especie[100];
	FILE *f;
	printf("A procurar ficheiro...\n");
	f = fopen(nfile, "r");
	if(f==NULL){
		printf("Ficheiro nao encontrado!!!\n");
		return tAnimais;
	}
	printf("Ficheiro aberto!\n");

	while(!feof(f)){
		if(fscanf(f,"%s\t%s\t%d\t%d", especie, nome, &peso, &loc) < 0){
			break;
		}
		if((pesoActArea(ta,loc) + peso) <= capArea(ta, loc)){
			last_id++;
			temp = addAnimaisEnd(temp, ta, last_id, especie, nome, peso, loc, -1, -1);
		}

	}
	fclose(f);
	printf("Animais importados!\n");
	return tAnimais;
}

void dispAnimais(Animais *tAnimais){
	Animais *temp = tAnimais;
	printf("\n[ANIMAIS]\n");
	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->familia.pai && temp->familia.mae){
			printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:%d/m:%d)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.pai->id, temp->familia.mae->id);
		}
		if(temp->familia.pai && !temp->familia.mae){
			printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:%d/m:---)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.pai->id);
		}
		if(!temp->familia.pai && temp->familia.mae){
			printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:---/m:%d)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.mae->id);
		}
		if(!temp->familia.pai && !temp->familia.mae){
			printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:---/m:---)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id);
		}
	}
}

void dispAnimaisArea(Animais *tAnimais, Areas *tAreas, int id){
	Animais *temp = tAnimais;
	Areas *ta = tAreas;
	printf("\n[ANIMAIS NA AREA %d]\n", id);
	while(ta->prox != NULL){
		ta = ta->prox;
		if(ta->id == id){
			while(temp->prox != NULL){
				temp = temp->prox;
				if(temp->familia.pai && temp->familia.mae){
					printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:%d/m:%d)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.pai->id, temp->familia.mae->id);
				}
				if(temp->familia.pai && !temp->familia.mae){
					printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:%d/m:---)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.pai->id);
				}
				if(!temp->familia.pai && temp->familia.mae){
					printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:---/m:%d)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.mae->id);
				}
				if(!temp->familia.pai && !temp->familia.mae){
					printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:---/m:---)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id);
				}
			}
		}
	}
}

void dispAnimaisEspecie(Animais *tAnimais, char *especie){
	Animais *temp = tAnimais;
	printf("\n[ANIMAIS DA ESPECIE %s]\n", especie);
	while(temp->prox != NULL){
		temp = temp->prox;
		if(strcmp(temp->especie,especie)==0){
			if(temp->familia.pai && temp->familia.mae){
				printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:%d/m:%d)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.pai->id, temp->familia.mae->id);
			}
			if(temp->familia.pai && !temp->familia.mae){
				printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:%d/m:---)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.pai->id);
			}
			if(!temp->familia.pai && temp->familia.mae){
				printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:---/m:%d)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.mae->id);
			}
			if(!temp->familia.pai && !temp->familia.mae){
				printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FAM](p:---/m:---)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id);
			}
		}
	}
}

void dispAnimalID(Animais *tAnimais, int id){
	Animais *temp = tAnimais;
	printf("\n[INFO ANIMAL ID: %d]\n", id);
	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->id == id){
			if(temp->familia.pai && temp->familia.mae){
				printf("\n\tID: %d\n\tNome: %s\n\tEspecie: %s\n\tPeso: %d\n\tArea: %d\n\tPai: [%d]%s\n\tMae: [%d]%s\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.pai->id, temp->familia.pai->nome, temp->familia.mae->id, temp->familia.mae->nome);
			}
			if(temp->familia.pai && !temp->familia.mae){
				printf("\n\tID: %d\n\tNome: %s\n\tEspecie: %s\n\tPeso: %d\n\tArea: %d\n\tPai: [%d]%s\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.pai->id, temp->familia.pai->nome);
			}
			if(!temp->familia.pai && temp->familia.mae){
				printf("\n\tID: %d\n\tNome: %s\n\tEspecie: %s\n\tPeso: %d\n\tArea: %d\n\tMae: [%d]%s\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.mae->id, temp->familia.mae->nome);
			}
			if(!temp->familia.pai && !temp->familia.mae){
				printf("\n\tID: %d\n\tNome: %s\n\tEspecie: %s\n\tPeso: %d\n\tArea: %d\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id);
			}
		}
	}
}

void dispAnimalNome(Animais *tAnimais, char *nome){
	Animais *temp = tAnimais;
	printf("\n[INFO ANIMAL NOME: %s]\n", nome);
	while(temp->prox != NULL){
		temp = temp->prox;
		if(strcmp(temp->nome,nome)==0){
			if(temp->familia.pai && temp->familia.mae){
				printf("\n\tID: %d\n\tNome: %s\n\tEspecie: %s\n\tPeso: %d\n\tArea: %d\n\tPai: [%d]%s\n\tMae: [%d]%s\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.pai->id, temp->familia.pai->nome, temp->familia.mae->id, temp->familia.mae->nome);
			}
			if(temp->familia.pai && !temp->familia.mae){
				printf("\n\tID: %d\n\tNome: %s\n\tEspecie: %s\n\tPeso: %d\n\tArea: %d\n\tPai: [%d]%s\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.pai->id, temp->familia.pai->nome);
			}
			if(!temp->familia.pai && temp->familia.mae){
				printf("\n\tID: %d\n\tNome: %s\n\tEspecie: %s\n\tPeso: %d\n\tArea: %d\n\tMae: [%d]%s\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id, temp->familia.mae->id, temp->familia.mae->nome);
			}
			if(!temp->familia.pai && !temp->familia.mae){
				printf("\n\tID: %d\n\tNome: %s\n\tEspecie: %s\n\tPeso: %d\n\tArea: %d\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.area->id);
			}
		}
	}
}

void rmAnimalID(Animais *tAnimais, Areas *tAreas, int id){
	Animais *temp = tAnimais;
	Animais *ani = sizeof(Animais);
	Areas *ta = tAreas;

	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->id == id){
			temp->loc.area->pesoAct -= temp->peso;
			tAnimais = temp->prox;
			printf("Animal removido!\n");
			ani = tAnimais;
			while(ani->prox != NULL){
				ani = ani->prox;
				if(ani->familia.pai && ani->familia.pai->id == id){
					ani->familia.pai = NULL;
					ani->familia.paiID = -1;
				}
				if(ani->familia.mae && ani->familia.mae->id == id){
					ani->familia.mae = NULL;
					ani->familia.maeID = -1;
				}
			}
			return;
		}
		if(temp->prox->id == id){
			temp->prox->loc.area->pesoAct -= temp->prox->peso;
			temp->prox = temp->prox->prox;
			printf("Animal removido!\n");
			ani = tAnimais;
			while(ani->prox != NULL){
				ani = ani->prox;
				if(ani->familia.pai && ani->familia.pai->id == id){
					ani->familia.pai = NULL;
					ani->familia.paiID = -1;
				}
				if(ani->familia.mae && ani->familia.mae->id == id){
					ani->familia.mae = NULL;
					ani->familia.maeID = -1;
				}
			}
			return;
		}
	}
	printf("Animal com o ID: %d, nao encontrado!\n", id);
	return;
}

void rmAnimalNome(Animais *tAnimais, Areas *tAreas, char *nome){
	Animais *temp = tAnimais;
	Animais *ani = sizeof(Animais);
	Areas *ta = tAreas;

	while(temp->prox != NULL){
		temp = temp->prox;
		if(strcmp(temp->nome,nome)==0){
			temp->loc.area->pesoAct -= temp->peso;
			tAnimais = temp->prox;
			printf("Animal removido!\n");
			ani = tAnimais;
			while(ani->prox != NULL){
				ani = ani->prox;
				if(ani->familia.pai && strcmp(ani->familia.pai->nome,nome)==0){
					ani->familia.pai = NULL;
					ani->familia.paiID = -1;
				}
				if(ani->familia.mae && strcmp(ani->familia.mae->nome,nome)==0){
					ani->familia.mae = NULL;
					ani->familia.maeID = -1;
				}
			}
			return;
		}
		if(strcmp(temp->prox->nome,nome)==0){
			temp->prox->loc.area->pesoAct -= temp->prox->peso;
			temp->prox = temp->prox->prox;
			printf("Animal removido!\n");
			ani = tAnimais;
			while(ani->prox != NULL){
				ani = ani->prox;
				if(ani->familia.pai && strcmp(ani->familia.pai->nome,nome)==0){
					ani->familia.pai = NULL;
					ani->familia.paiID = -1;
				}
				if(ani->familia.mae && strcmp(ani->familia.mae->nome,nome)==0){
					ani->familia.mae = NULL;
					ani->familia.maeID = -1;
				}
			}
			return;
		}
	}
	printf("Animal com o nome: %s, nao encontrado!\n", nome);
	return;
}

void transfAnimal(Animais *tAnimais, Areas *tAreas, int id, int desto){
	Animais *temp = tAnimais;
	Areas *ta = tAreas;
	int i=1,a=1;

	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->id == id){
			while(ta->prox != NULL){
				ta = ta->prox;
				if(ta->id == desto){
					if(ta->front1.area && ta->front1.area->id == temp->loc.area->id){
						if((ta->front1.area->pesoAct + temp->peso) <= ta->front1.area->cap){
							temp->loc.area->pesoAct -= temp->peso;
							ta->pesoAct += temp->peso;
							temp->loc.area = ta;
							temp->loc.id = ta->id;
							printf("Animal transferido!! [%d/%d/%d]\n", temp->id, temp->loc.id, temp->loc.area->id);
							return;
						}else{
							printf("Area destino nao tem capacidade para receber o animal!!\n");
							return;
						}
					}else if(ta->front2.area && ta->front2.area->id == temp->loc.area->id){
						if((ta->front2.area->pesoAct + temp->peso) <= ta->front2.area->cap){
							temp->loc.area->pesoAct -= temp->peso;
							ta->pesoAct += temp->peso;
							temp->loc.area = ta;
							temp->loc.id = ta->id;
							printf("Animal transferido!! [%d/%d/%d]\n", temp->id, temp->loc.id, temp->loc.area->id);
							return;
						}else{
							printf("Area destino nao tem capacidade para receber o animal!!\n");
							return;
						}
					}else if(ta->front3.area && ta->front3.area->id == temp->loc.area->id){
						if((ta->front3.area->pesoAct + temp->peso) <= ta->front3.area->cap){
							temp->loc.area->pesoAct -= temp->peso;
							ta->pesoAct += temp->peso;
							temp->loc.area = ta;
							temp->loc.id = ta->id;
							printf("Animal transferido!! [%d/%d/%d]\n", temp->id, temp->loc.id, temp->loc.area->id);
							return;
						}else{
							printf("Area destino nao tem capacidade para receber o animal!!\n");
							return;
						}
					}else{
						printf("Area destino nao faz fronteira com a area em que o animal esta!!\n");
						return;
					}
				}
			}
		}
	}
	printf("alguma coisa correu mal...\n");
}

void saveAnimais(Animais *tAnimais){
	Animais *temp = tAnimais;
	FILE *f;
	printf("A abrir ficheiro de Animais...\n");
	f = fopen("animais.dat", "wb+");
	if(f==NULL){
		printf("Erro a abrir ficheiro de Animais!\n");
	}
	printf("A guardar Animais para ficheiro...\n");
	while(temp->prox != NULL){
		temp = temp->prox;
		fwrite(temp, sizeof(Animais), 1, f);
	}
	fclose(f);
	printf("Animais guardados!\n");
}

int getLastAnimalID(Animais *tAnimais){
	Animais *temp = tAnimais;
	if(temp->prox == NULL) return 0;
	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->prox == NULL){
			return temp->id;
		}
	}
}
