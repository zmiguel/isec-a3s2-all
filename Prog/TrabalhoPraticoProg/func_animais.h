Animais * addAnimaisEnd(Animais *tAnimais, int id, char *especie, char *nome, int peso, int locID, int pai, int mae, int filho) {
	Animais *aux = tAnimais;

	while (aux->prox != NULL) {
		aux = aux->prox;
	}
	aux->prox = malloc(sizeof(Animais));
	aux->prox->id = id;
	strcpy(aux->prox->especie, especie);
	strcpy(aux->prox->nome, nome);
	aux->prox->peso = peso;
	aux->prox->loc.id = locID;
	aux->prox->familia.paiID = pai;
	aux->prox->familia.maeID = mae;
	aux->prox->familia.filhoID = filho;
	aux->prox->prox = NULL;
	return tAnimais;
}

Animais * readAnimais(Animais *tAnimais){
	Animais *temp = tAnimais;
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
		read = malloc(sizeof(Animais));
		end = fread(read,sizeof(Animais),1,f);
		if(end!=1) break;
		temp->prox = read;
		temp = temp->prox;

	}

	fclose(f);
	return tAnimais;
}

void dispAnimais(Animais *tAnimais){
	Animais *temp = tAnimais;
	while(temp->prox != NULL){
		temp = temp->prox;
		printf("id: %d\tnome: %s\tespecie: %s\tpeso: %d\tarea: %d\tpai: %d\tmae: %d\tfilho: %d\n", temp->id, temp->nome, temp->especie, temp->peso, temp->loc.id, temp->familia.paiID, temp->familia.maeID, temp->familia.filhoID);
	}
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
