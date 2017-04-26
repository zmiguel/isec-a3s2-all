/*Grid * addGridIni(Grid *gamegrid, char cont) {
	Grid *novo, *aux;
	aux = gamegrid;
	novo = malloc(sizeof(Grid));
	if (novo == NULL) exit(0);
	novo->cont = cont;
	novo->prox = aux->prox;
	aux->prox = novo;
	return aux ;
}*/

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

void dispIntro(void){
	printf("\n\tZZZZZZZZZZZZZZZZZZZ\n\tZ:::::::::::::::::Z\n\tZ:::::::::::::::::Z\n\tZ:::ZZZZZZZZ:::::Z\n\tZZZZZ     Z:::::Z     ooooooooooo      ooooooooooo\n\t        Z:::::Z     oo:::::::::::oo  oo:::::::::::oo\n\t       Z:::::Z     o:::::::::::::::oo:::::::::::::::o\n\t      Z:::::Z      o:::::ooooo:::::oo:::::ooooo:::::o\n\t     Z:::::Z       o::::o     o::::oo::::o     o::::o\n\t    Z:::::Z        o::::o     o::::oo::::o     o::::o\n\t   Z:::::Z         o::::o     o::::oo::::o     o::::o\n\tZZZ:::::Z     ZZZZZo::::o     o::::oo::::o     o::::o\n\tZ::::::ZZZZZZZZ:::Zo:::::ooooo:::::oo:::::ooooo:::::o\n\tZ:::::::::::::::::Zo:::::::::::::::oo:::::::::::::::o\n\tZ:::::::::::::::::Z oo:::::::::::oo  oo:::::::::::oo\n\tZZZZZZZZZZZZZZZZZZZ   ooooooooooo      ooooooooooo\n");

	printf("\n#     #                                                 #######                                    \n#     #   ##   #      ######    #####    ##    ####     #       #       ####  #####  ######  ####  \n#     #  #  #  #      #         #    #  #  #  #         #       #      #    # #    # #      #      \n#     # #    # #      #####     #    # #    #  ####     #####   #      #    # #    # #####   ####  \n #   #  ###### #      #         #    # ######      #    #       #      #    # #####  #           # \n  # #   #    # #      #         #    # #    # #    #    #       #      #    # #   #  #      #    # \n   #    #    # ###### ######    #####  #    #  ####     #       ######  ####  #    # ######  ####  \n");
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

	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->nr_front == 0){
			printf("id:%d\ttipo:%d\tcap:%d\n", temp->id, temp->tipo, temp->cap);
		}else if(temp->nr_front == 1){
			printf("id:%d\ttipo:%d\tcap:%d\tfront1:%d\n", temp->id, temp->tipo, temp->cap, temp->front1.id);
		}else if(temp->nr_front == 2){
			printf("id:%d\ttipo:%d\tcap:%d\tfront1:%d\tfront2:%d\n", temp->id, temp->tipo, temp->cap, temp->front1.id, temp->front2.id);
		}else if(temp->nr_front == 3){
			printf("id:%d\ttipo:%d\tcap:%d\tfront1:%d\tfront2:%d\tfront3:%d\n", temp->id, temp->tipo, temp->cap, temp->front1.id, temp->front2.id, temp->front3.id);
		}
	}
}

void saveAreas(Areas *tAreas){
	int tID, tType, tCap, tNR, t1, t2, t3, i=0;
	Areas *temp = tAreas;
	FILE *f;
	printf("A abrir ficheiro de Areas...\n");
	f = fopen("areas.txt", "w+");
	if(f==NULL){
		printf("Erro a abrir ficheiro de areas!\n");
		exit(0);
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

Areas * rmArea(Areas *tAreas, int id){
	Areas *temp = tAreas;
	while(temp->prox != NULL){
		temp = temp->prox;
		if(temp->prox->id == id){
			if(temp->prox->prox == NULL){
				temp->prox = NULL;
			}else{
				temp->prox = temp->prox->prox;
			}
			break;
		}
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
