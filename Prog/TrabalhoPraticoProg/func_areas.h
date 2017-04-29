Areas * addAreaEnd(Areas *tAreas, int id, int tipo, int cap, int nr_front, int front1, int front2, int front3) {
	Areas *aux = tAreas;

	while (aux->prox != NULL) {
		aux = aux->prox;
	}
	aux->prox = malloc(sizeof(Areas));
	aux->prox->id = id;
	aux->prox->tipo = tipo;
	aux->prox->cap = cap;
	aux->prox->pesoAct = 0;
	aux->prox->nr_front = nr_front;
	aux->prox->front1.id = front1;
	aux->prox->front2.id = front2;
	aux->prox->front3.id = front3;
	aux->prox->prox = NULL;
	return tAreas;
}

Areas * readAreas(Areas *tAreas){
	int tID, tType, tCap, tNR, t1, t2, t3, i=0;
	Areas *temp = tAreas;
	FILE *f;
	printf("A abrir ficheiro de Areas...\n");
	f = fopen("areas.txt", "r");
	if(f==NULL){
		printf("Erro a abrir ficheiro de areas!\n");
		exit(0);
	}
	printf("A preencher vector...\n");
	fscanf(f,"%d\t%d\t%d\t%d", &tID, &tType, &tCap, &tNR);
	do{
		if(tNR == 0){
			temp = addAreaEnd(temp, tID, tType, tCap, tNR, -1, -1 , -1);
		}else if(tNR == 1){
			fscanf(f,"\t%d",&t1);
			temp = addAreaEnd(temp, tID, tType, tCap, tNR, t1, -1 , -1);
		}else if(tNR == 2){
			fscanf(f,"\t%d\t%d",&t1, &t2);
			temp = addAreaEnd(temp, tID, tType, tCap, tNR, t1, t2, -1);
		}else if(tNR == 3){
			fscanf(f,"\t%d\t%d\t%d",&t1,&t2,&t3);
			temp = addAreaEnd(temp, tID, tType, tCap, tNR, t1, t2, t3);
		}else{
			exit(0);
		}
		fscanf(f,"%d\t%d\t%d\t%d", &tID, &tType, &tCap, &tNR);
		i++;
	}while(!feof(f));
	fclose(f);
	printf("%d areas carregadas!!\n", i);
	return temp;
}

void dispArea(Areas *tArea){
	Areas *temp = tArea;
	printf("[AREAS]\n");

	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->nr_front == 0){
			printf("[ID] (%d)   [Tipo] (%d)   [CAP] (%d/%d)\n", temp->id, temp->tipo, temp->pesoAct, temp->cap);
		}else if(temp->nr_front == 1){
			printf("[ID] (%d)   [Tipo] (%d)   [CAP] (%d/%d)   [F1] (%d)\n", temp->id, temp->tipo, temp->pesoAct, temp->cap, temp->front1.area->id);
		}else if(temp->nr_front == 2){
			printf("[ID] (%d)   [Tipo] (%d)   [CAP] (%d/%d)   [F1] (%d)   [F2] (%d)\n", temp->id, temp->tipo, temp->pesoAct, temp->cap, temp->front1.area->id, temp->front2.area->id);
		}else if(temp->nr_front == 3){
			printf("[ID] (%d)   [Tipo] (%d)   [CAP] (%d/%d)   [F1] (%d)   [F2] (%d)   [F3] (%d)\n", temp->id, temp->tipo, temp->pesoAct, temp->cap, temp->front1.area->id, temp->front2.area->id, temp->front3.area->id);
		}
	}
}

void saveAreas(Areas *tAreas){
	Areas *temp = tAreas;
	FILE *f;
	printf("A abrir ficheiro de Areas...\n");
	f = fopen("areas.txt", "w+");
	if(f==NULL){
		printf("Erro a abrir ficheiro de areas!\n");
	}
	printf("A guardar Areas para ficheiro...\n");
	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->nr_front == 0){
			fprintf(f,"%d\t%d\t%d\t%d\n", temp->id, temp->tipo, temp->cap, temp->nr_front);
		}else if(temp->nr_front == 1){
			fprintf(f,"%d\t%d\t%d\t%d\t%d\n", temp->id, temp->tipo, temp->cap, temp->nr_front, temp->front1.id);
		}else if(temp->nr_front == 2){
			fprintf(f,"%d\t%d\t%d\t%d\t%d\t%d\n", temp->id, temp->tipo, temp->cap, temp->nr_front, temp->front1.id, temp->front2.id);
		}else if(temp->nr_front == 3){
			fprintf(f,"%d\t%d\t%d\t%d\t%d\t%d\t%d\n", temp->id, temp->tipo, temp->cap, temp->nr_front, temp->front1.id, temp->front2.id, temp->front3.id);
		}

	}
	fclose(f);
	printf("areas guardadas!!\n");
}

int nrFront(Areas *tArea, int id){
	Areas *temp = tArea;

	do{
		temp = temp->prox;
		if(temp == NULL) return -1;
	}while(temp->id != id);

	return temp->nr_front;
}

Areas * addFronteira(Areas *tAreas, int exist, int novo){
	Areas *temp = tAreas;
	printf("A adicionar nova fronteira a area existente\n");
	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->id == exist){
			if(temp->nr_front == 1){
				temp->nr_front++;
				temp->front2.id=novo;
			}else if(temp->nr_front == 2){
				temp->nr_front++;
				temp->front3.id=novo;
			}
		}
	}
	printf("Area existente actualizada!\n");
	return tAreas;
}

int pesoActArea(Areas *tArea, int id){
	Areas *temp = tArea;

	do{
		temp = temp->prox;
		if(temp == NULL) return -1;
	}while(temp->id != id);

	return temp->pesoAct;
}

int capArea(Areas *tArea, int id){
	Areas *temp = tArea;

	do{
		temp = temp->prox;
		if(temp == NULL) return -1;
	}while(temp->id != id);

	return temp->cap;
}

Areas * rmArea(Areas *tAreas, int id){
	Areas *temp = tAreas;
	while(temp->prox != NULL){
		if(temp->prox->id == id){
			if(temp->prox->pesoAct != 0){
				printf("area ainda tem animais!\n");
			}else{
				if(temp->prox->prox == NULL){
					temp->prox = NULL;
				}else{
					temp->prox = temp->prox->prox;
				}
				break;
			}
		}
		temp = temp->prox;
	}
	printf("Area removida!\n");
	return tAreas;
}

Areas * rmFronteira(Areas *tAreas, int id){
	Areas *temp = tAreas;
	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->nr_front==1){
			if(temp->front1.id==id){
				temp->nr_front=0;
				temp->front1.id=-1;
			}
		}else if(temp->nr_front==2){
			if(temp->front1.id==id){
				temp->nr_front--;
				temp->front1.id = temp->front2.id;
				temp->front2.id=-1;
			}else if(temp->front2.id==id){
				temp->nr_front--;
				temp->front2.id=-1;
			}
		}else if(temp->nr_front==3){
			if(temp->front1.id==id){
				temp->nr_front--;
				temp->front1.id = temp->front2.id;
				temp->front2.id = temp->front3.id;
				temp->front3.id=-1;
			}else if(temp->front2.id==id){
				temp->nr_front--;
				temp->front2.id = temp->front3.id;
				temp->front3.id=-1;
			}else if(temp->front3.id==id){
				temp->nr_front--;
				temp->front3.id=-1;
			}
		}
	}
	return tAreas;
}

int getLastAreaID(Areas *tAreas){
	Areas *temp = tAreas;
	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->prox == NULL){
			return temp->id;
		}
	}
}

Areas * linkAreas(Areas *tAreas){
	Areas *temp = tAreas;
	Areas *temp2 = tAreas;
	Areas *move;
	while(temp->prox != NULL){
		temp = temp->prox;
		temp2 = tAreas;
		while(temp2->prox != NULL){
			move = malloc(sizeof(Areas));
			temp2 = temp2->prox;
			if(temp2->id == temp->front1.id){
				move = temp2;
				temp->front1.area = move;
			}
			if(temp2->id == temp->front2.id){
				move = temp2;
				temp->front2.area = move;
			}
			if(temp2->id == temp->front3.id){
				move = temp2;
				temp->front3.area = move;
			}
		}
	}
	return tAreas;
}
