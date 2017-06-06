Animais * addAnimaisEnd(Animais *tAnimais, Areas *tAreas, int id, char *especie, char *nome, int peso, int locID, int filho, int nrAreas) {
	Animais *aux = tAnimais;
	Animais *ani2 = tAnimais;
	int i;

	while (aux->prox != NULL) {
		aux = aux->prox;
	}

	for(i=0;i<nrAreas;i++){
		if(tAreas[i].id == locID) break;
	}

	aux->prox = malloc(sizeof(Animais));
	aux->prox->id = id;
	strcpy(aux->prox->especie, especie);
	strcpy(aux->prox->nome, nome);
	aux->prox->peso = peso;
	tAreas[i].pesoAct += peso;
	aux->prox->loc = locID;
	aux->prox->filho.fID = filho;
	if(filho != -1){
		while (ani2->prox != NULL) {
			ani2 = ani2->prox;
			if(ani2->id == filho){
				aux->prox->filho.strt = ani2;
				break;
			}else{
				aux->prox->filho.strt = NULL;
			}
		}
	} else {
		aux->prox->filho.strt = NULL;
		aux->prox->pais.strt = NULL;
	}
	aux->prox->prox = NULL;
	return tAnimais;
}

Animais * readAnimais(Animais *tAnimais, Areas *tAreas, int nrAreas, bool compActive){
	Animais *temp = tAnimais;
	Animais *read;
	FILE *f;
	int i, i2;
	unsigned long end;
	printf("A procurar ficheiro de Animais...\n");
	f = fopen("animais.dat","rb");
	if(f==NULL){
		printf("Fichero de animais nao encontrado, ou erro a abrir!\n");
		temp->prox = NULL;
		return tAnimais;
	}
	printf("Ficheiro de animais encontrado e aberto!\n");
	if (compActive) {//caso incompatibilidade entre animais esteja activa

	}else{//caso nao esteja activa
		while (!feof(f)) {
			read = malloc(sizeof(Animais));
			end = fread(read, sizeof(Animais), 1, f);
			if (end != 1) break;
			for (i = 0; i<nrAreas; i++) {
				if (tAreas[i].id == read->loc) {
					if ((tAreas[i].pesoAct + read->peso) > tAreas[i].cap) {//area ia ficar com peso a mais!
						if (tAreas[i].nr_front == 1) {
							for (i2 = 0; i2<nrAreas; i2++) {
								if (tAreas[i2].id == tAreas[i].front1) {
									if ((tAreas[i2].pesoAct + read->peso) <= tAreas[i2].cap) {
										tAreas[i2].pesoAct += read->peso;
										read->loc = tAreas[i2].front1;
										temp->prox = read;
										temp = temp->prox;
										fclose(f);
										return tAnimais;
									}
								}
							}
						}
						if (tAreas[i].nr_front == 2) {
							for (i2 = 0; i2<nrAreas; i2++) {
								if (tAreas[i2].id == tAreas[i].front2) {
									if ((tAreas[i2].pesoAct + read->peso) <= tAreas[i2].cap) {
										tAreas[i2].pesoAct += read->peso;
										read->loc = tAreas[i2].front2;
										temp->prox = read;
										temp = temp->prox;
										fclose(f);
										return tAnimais;
									}
								}
							}
						}
						if (tAreas[i].nr_front == 3) {
							for (i2 = 0; i2<nrAreas; i2++) {
								if (tAreas[i2].id == tAreas[i].front3) {
									if ((tAreas[i2].pesoAct + read->peso) <= tAreas[i2].cap) {
										tAreas[i2].pesoAct += read->peso;
										read->loc = tAreas[i2].front3;
										temp->prox = read;
										temp = temp->prox;
										fclose(f);
										return tAnimais;
									}
								}
							}
						}
					}
					else {//area tem capacidade para ter o animal
						tAreas[i].pesoAct += read->peso;
						temp->prox = read;
						temp = temp->prox;
						break;
					}
				}
			}
		}
	}
	
	fclose(f);
	return tAnimais;
}

Animais * importAnimaisFile(Animais *tAnimais, char *nfile, Areas *tAreas, int nrAreas){
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
		if((pesoActArea(ta,loc,nrAreas) + peso) <= capArea(ta, loc, nrAreas)){
			last_id++;
			temp = addAnimaisEnd(temp, ta, last_id, especie, nome, peso, loc, -1, nrAreas);
		}

	}
	fclose(f);
	printf("Animais importados!\n");
	return tAnimais;
}

void dispAnimais(Animais *tAnimais){
	Animais *temp = tAnimais;
	Animais *temp2;
	printf("\n[ANIMAIS]\n");
	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->filho.strt && !temp->pais.strt){
			printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   ", temp->id, temp->nome, temp->especie, temp->peso, temp->loc);
			temp2 = temp->filho.strt;
			while (temp2 != NULL) {
				printf("[FILHO](%s)   ", temp2->nome);
				temp2 = temp2->prox;
			}
			printf("\n");
		}
		if(!temp->filho.strt && !temp->pais.strt){
			printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FILHO]()\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc);
		}
		if (!temp->filho.strt && temp->pais.strt) {
			printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   ", temp->id, temp->nome, temp->especie, temp->peso, temp->loc);
			temp2 = temp->pais.strt;
			while (temp2 != NULL) {
				printf("[PAIS](%s)   ", temp2->nome);
				temp2 = temp2->prox;
			}
			printf("\n");
		}
		if (temp->filho.strt && temp->pais.strt) {
			printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   ", temp->id, temp->nome, temp->especie, temp->peso, temp->loc);
			temp2 = temp->filho.strt;
			while (temp2 != NULL) {
				printf("[FILHO](%s)   ", temp2->nome);
				temp2 = temp2->prox;
			}
			temp2 = temp->pais.strt;
			while (temp2 != NULL) {
				printf("[PAIS](%s)   ", temp2->nome);
				temp2 = temp2->prox;
			}
			printf("\n");
		}
	}
}

void dispAnimaisArea(Animais *tAnimais, Areas *tAreas, int id, int nrAreas){
	Animais *temp = tAnimais;
	int i;
	printf("\n[ANIMAIS NA AREA %d]\n", id);
	for(i=0;i<nrAreas;i++){
		if(tAreas[i].id == id){
			while(temp->prox != NULL){
				temp = temp->prox;
				if(temp->filho.strt){
					printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FILHO](%d-%s)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc, temp->filho.strt->id, temp->filho.strt->nome);
				}
				if(!temp->filho.strt){
					printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FILHO]()\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc);
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
			if(temp->filho.strt){
				printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FILHO](%d-%s)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc, temp->filho.strt->id, temp->filho.strt->nome);
			}
			if(!temp->filho.strt){
				printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FILHO]()\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc);
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
			if(temp->filho.strt){
				printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FILHO](%d-%s)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc, temp->filho.strt->id, temp->filho.strt->nome);
			}
			if(!temp->filho.strt){
				printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FILHO]()\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc);
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
			if(temp->filho.strt){
				printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FILHO](%d-%s)\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc, temp->filho.strt->id, temp->filho.strt->nome);
			}
			if(!temp->filho.strt){
				printf("[ID](%d)   [NOME](%s)   [ESPECIE](%s)   [PESO](%d)   [LOC](%d)   [FILHO]()\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc);
			}
		}
	}
}

void rmAnimalID(Animais *tAnimais, Areas *tAreas, int id, int nrAreas){
	Animais *temp = tAnimais;
	Animais *ani = malloc(sizeof(Animais));
	int i;

	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->id == id){
			for(i=0;i<nrAreas;i++){
				if(tAreas[i].id == temp->loc){
					tAreas[i].pesoAct -= temp->peso;
				}
			}
			tAnimais = temp->prox;
			printf("Animal removido!\n");
			ani = tAnimais;
			while(ani->prox != NULL){
				ani = ani->prox;
				if(ani->filho.strt && ani->filho.strt->id == id){
					ani->filho.strt = NULL;
					ani->filho.fID = -1;
				}
			}
			return;
		}
		if(temp->prox->id == id){
			for(i=0;i<nrAreas;i++){
				if(tAreas[i].id == temp->prox->loc){
					tAreas[i].pesoAct -= temp->prox->peso;
				}
			}
			temp->prox = temp->prox->prox;
			printf("Animal removido!\n");
			ani = tAnimais;
			while(ani->prox != NULL){
				ani = ani->prox;
				if(ani->filho.strt && ani->filho.strt->id == id){
					ani->filho.strt = NULL;
					ani->filho.fID = -1;
				}
			}
			return;
		}
	}
	printf("Animal com o ID: %d, nao encontrado!\n", id);
	return;
}

void rmAnimalNome(Animais *tAnimais, Areas *tAreas, char *nome, int nrAreas){
	Animais *temp = tAnimais;
	Animais *ani = malloc(sizeof(Animais));
	int i;

	while(temp->prox != NULL){
		temp = temp->prox;
		if(strcmp(temp->nome,nome)==0){
			for(i=0;i<nrAreas;i++){
				if(tAreas[i].id == temp->loc){
					tAreas[i].pesoAct -= temp->peso;
				}
			}
			tAnimais = temp->prox;
			printf("Animal removido!\n");
			ani = tAnimais;
			while(ani->prox != NULL){
				ani = ani->prox;
				if(ani->filho.strt && strcmp(ani->filho.strt->nome,nome)==0){
					ani->filho.strt = NULL;
					ani->filho.fID = -1;
				}
			}
			return;
		}
		if(strcmp(temp->prox->nome,nome)==0){
			for(i=0;i<nrAreas;i++){
				if(tAreas[i].id == temp->prox->loc){
					tAreas[i].pesoAct -= temp->prox->peso;
				}
			}
			temp->prox = temp->prox->prox;
			printf("Animal removido!\n");
			ani = tAnimais;
			while(ani->prox != NULL){
				ani = ani->prox;
				if(ani->filho.strt && strcmp(ani->filho.strt->nome,nome)==0){
					ani->filho.strt = NULL;
					ani->filho.fID = -1;
				}
			}
			return;
		}
	}
	printf("Animal com o nome: %s, nao encontrado!\n", nome);
	return;
}

void transfAnimal(Animais *tAnimais, Areas *tAreas, int id, int desto, int nrAreas){
	Animais *temp = tAnimais;
	int i/*destino*/, i2/*actual*/;

	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->id == id){
			for(i=0;i<nrAreas;i++){
				if(tAreas[i].id == desto){//procura area com ID do destino
					if(tAreas[i].front1 == temp->loc){ // verifica se a localizaçao actual faz fronteira com a area destino
						for(i2=0;i2<nrAreas;i2++){
							if(tAreas[i2].id == tAreas[i].front1){//encontra a area actual do animal
								if((tAreas[i].pesoAct + temp->peso) <= tAreas[i].cap){//verifica se o destino tem capacidade para ter o animal
									tAreas[i2].pesoAct -= temp->peso;
									tAreas[i].pesoAct += temp->peso;
									temp->loc = tAreas[i].id;
									printf("Animal transferido!! [%d/%d/%d]\n", temp->id, temp->loc, temp->loc);
									return;
								}else{
									printf("Area destino nao tem capacidade para receber o animal!!\n");
									return;
								}
							}
						}
					}
					if(tAreas[i].front2 == temp->loc){// verifica se a localizaçao actual faz fronteira com a area destino
						for(i2=0;i2<nrAreas;i2++){
							if(tAreas[i2].id == tAreas[i].front2){//encontra a area actual do animal
								if((tAreas[i].pesoAct + temp->peso) <= tAreas[i].cap){//verifica se o destino tem capacidade para ter o animal
									tAreas[i2].pesoAct -= temp->peso;
									tAreas[i].pesoAct += temp->peso;
									temp->loc = tAreas[i].id;
									printf("Animal transferido!! [%d/%d/%d]\n", temp->id, temp->loc, temp->loc);
									return;
								}else{
									printf("Area destino nao tem capacidade para receber o animal!!\n");
									return;
								}
							}
						}
					}
					if(tAreas[i].front3 == temp->loc){// verifica se a localizaçao actual faz fronteira com a area destino
						for(i2=0;i2<nrAreas;i2++){
							if(tAreas[i2].id == tAreas[i].front3){//encontra a area actual do animal
								if((tAreas[i].pesoAct + temp->peso) <= tAreas[i].cap){//verifica se o destino tem capacidade para ter o animal
									tAreas[i2].pesoAct -= temp->peso;
									tAreas[i].pesoAct += temp->peso;
									temp->loc = tAreas[i].id;
									printf("Animal transferido!! [%d/%d/%d]\n", temp->id, temp->loc, temp->loc);
									return;
								}else{
									printf("Area destino nao tem capacidade para receber o animal!!\n");
									return;
								}
							}
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
	return;
}

void saveAnimais(Animais *tAnimais){
	Animais *temp = tAnimais;
	FILE *f;
	printf("A abrir ficheiro de Animais...\n");
	f = fopen("animais.dat", "wb+");
	if(f==NULL){
		printf("Erro a abrir ficheiro de Animais!\n");
		return;
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
	if(temp == NULL) return 0;
	if(temp->prox == NULL) return 0;
	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->prox == NULL){
			return temp->id;
		}
	}
	return 0;
}

void linkAnimais(Animais *tAnimais){
	Animais *ani = tAnimais;
	Animais *anit;

	while(ani->prox != NULL){
		ani = ani->prox;
		anit = tAnimais;
		while(anit->prox != NULL){
			anit = anit->prox;
			if(anit->id == ani->filho.fID){
				ani->filho.strt = anit;
			}
		}
	}
}

void criaFilho1(Animais *tAnimais, Areas *tAreas, int id, char *nome, int nrAreas){
	int tpeso=0, i;
	Animais *temp = tAnimais;
	Animais *anew;
	Animais *ftemp;
	Animais *ptemp;

	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->id == id){
			for (i = 0; i<nrAreas; i++) {//obter area
				if (tAreas[i].id == temp->loc) break;
			}
			tpeso = temp->peso * 0.20;
			temp->peso -= tpeso;
			tAreas[i].pesoAct -= tpeso;
			anew = addAnimaisEnd(tAnimais, tAreas, getLastAnimalID(tAnimais)+1,temp->especie,nome,tpeso,temp->loc,-1, nrAreas);
			while (anew->prox != NULL) {
				anew = anew->prox;
			}
			if (temp->filho.strt) {
				ftemp = temp->filho.strt;
				while(ftemp->prox != NULL){
					ftemp = ftemp->prox;
				}
				ftemp = malloc(sizeof(Animais));
				memcpy(ftemp, anew, sizeof(Animais));//cria uma copia independente do bloco do filho no bloco do pai
				ftemp->prox = NULL;
				ptemp = temp;
				ftemp->pais.strt = malloc(sizeof(Animais));
				memcpy(ftemp->pais.strt, temp, sizeof(Animais));//cria uma copia independente do bloco do pai no bloco independente do filho
				temp->filho.strt->pais.strt->prox = NULL;
				temp = temp->prox;
				temp->pais.strt = malloc(sizeof(Animais));
				memcpy(temp->pais.strt, ptemp, sizeof(Animais));//cria uma copia independente do bloco do pai no bloco do filho
				temp->pais.strt->prox = NULL;
				return;

			} else {
				temp->filho.fID = anew->id;
				temp->filho.strt = malloc(sizeof(Animais));
				memcpy(temp->filho.strt, anew, sizeof(Animais));//cria uma copia independente do bloco do filho no bloco do pai
				temp->filho.strt->prox = NULL;
				ptemp = temp;
				temp->filho.strt->pais.strt = malloc(sizeof(Animais));
				memcpy(temp->filho.strt->pais.strt, temp, sizeof(Animais));//cria uma copia independente do bloco do pai no bloco independente do filho
				temp->filho.strt->pais.strt->prox = NULL;
				temp = temp->prox;
				temp->pais.strt = malloc(sizeof(Animais));
				memcpy(temp->pais.strt, ptemp, sizeof(Animais));//cria uma copia independente do bloco do pai no bloco do filho
				temp->pais.strt->prox = NULL;
				return;
			}
		}
	}
}

bool verifyFilho2(Animais *tAnimais,int id1, int id2){
	Animais *temp = tAnimais;
	Animais *anew;

	if(id1 == id2){
		printf("nao podes escolher o mesmo animal!!\n");
		return false;
	}

	while(temp->prox != NULL){
		temp = temp->prox;
		anew = tAnimais;
		if(temp->id == id1){
			while (anew->prox != NULL) {
				anew = anew->prox;
				if(anew->id == id2){
					if(temp->loc == anew->loc){
						if(strcmp(temp->especie,anew->especie) == 0){
							return true;
						}else{
							printf("animais de especies diferentes!\n");
							return false;
						}
					}else{
						printf("of animais estao em areas diferentes!\n");
						return false;
					}
				}
			}
		}
	}
	return false;
}

void criaFilho2(Animais *tAnimais, Areas *tAreas, int id1, int id2, char *nome, int nrAreas){
	int tpeso=0, i;
	Animais *temp = tAnimais;
	Animais *temp2 = tAnimais;
	Animais *anew;
	Animais *ftemp;
	Animais *ptemp;

	for(i=0;i<nrAreas;i++){
		if(tAreas[i].id == id1) break;
	}

	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->id == id1){
			while(temp2->prox != NULL){
				temp2 = temp2->prox;
				if(temp2->id == id2){
					tpeso = temp->peso * 0.20; //animal 1
					temp->peso -= temp->peso * 0.20; //animal 1
					tpeso += temp2->peso * 0.20; //animal 2
					temp2->peso -= temp2->peso * 0.20; //animal 2
					tAreas[i].pesoAct -= tpeso; //peso area on estao
					anew = addAnimaisEnd(tAnimais, tAreas, getLastAnimalID(tAnimais)+1,temp->especie,nome,tpeso,temp->loc,-1, nrAreas);
					while (anew->prox != NULL) {
						anew = anew->prox;
					}
					//animal 1
					if (temp->filho.strt) {
						ftemp = temp->filho.strt;
						while (ftemp->prox != NULL) {
							ftemp = ftemp->prox;
						}
						ftemp = anew;
						ftemp->prox = NULL;
					} else {
						temp->filho.fID = anew->id;
						temp->filho.strt = anew;
						temp->filho.strt->prox = NULL;
					}
					//animal 2
					if (temp2->filho.strt) {
						ftemp = temp2->filho.strt;
						while (ftemp->prox != NULL) {
							ftemp = ftemp->prox;
						}
						ftemp = anew;
						ftemp->prox = NULL;
					} else {
						temp2->filho.fID = anew->id;
						temp2->filho.strt = anew;
						temp2->filho.strt->prox = NULL;
					}

					temp->filho.strt->pais.strt = temp;
					temp->filho.strt->pais.strt->prox = temp2;
					temp->filho.strt->pais.strt->prox->prox = NULL;
				}
			}
		}
	}
}
