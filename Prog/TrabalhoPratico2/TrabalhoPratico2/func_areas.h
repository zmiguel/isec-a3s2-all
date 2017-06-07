Areas * addAreaEnd(Areas *tAreas, char *id, int tipo, int cap, int nr_front, char *front1, char *front2, char *front3, int nrAreas) {
	//printf("(%d) sizeof tAreas: %d\n", nrAreas, (sizeof(Areas)*nrAreas));
	tAreas = realloc(tAreas, (sizeof(Areas)*nrAreas));

	strcpy(tAreas[nrAreas - 1].id, id);
	tAreas[nrAreas-1].tipo = tipo;
	tAreas[nrAreas-1].cap = cap;
	tAreas[nrAreas-1].pesoAct = 0;
	tAreas[nrAreas-1].nr_front = nr_front;
	strcpy(tAreas[nrAreas-1].front1, front1);
	strcpy(tAreas[nrAreas-1].front2, front2);
	strcpy(tAreas[nrAreas-1].front3, front3);

	//printf("[ADD-AREA] %s %d %d %d %s %s %s\n", tAreas[nrAreas-1].id,tAreas[nrAreas -1].tipo,tAreas[nrAreas -1].cap,tAreas[nrAreas -1].nr_front,tAreas[nrAreas -1].front1,tAreas[nrAreas -1].front2,tAreas[nrAreas -1].front3);

	return tAreas;
}

Areas * readAreas(Areas *tAreas, int *nrAreas){
	int tType, tCap, tNR, i=0;
	char tID[100], t1[100], t2[100], t3[100];
	FILE *f;
	printf("A abrir ficheiro de Areas...\n");
	f = fopen("areas.txt", "r");
	if(f==NULL){
		printf("Erro a abrir ficheiro de areas!\n");
		exit(0);
	}
	printf("A preencher vector...\n");
	fscanf(f,"%s\t%d\t%d\t%d", &tID, &tType, &tCap, &tNR);
	do{
		*nrAreas = i+1;
		if(tNR == 0){
			tAreas = addAreaEnd(tAreas, tID, tType, tCap, tNR, "", "", "", *nrAreas);
		}else if(tNR == 1){
			fscanf(f,"\t%s",&t1);
			tAreas = addAreaEnd(tAreas, tID, tType, tCap, tNR, t1, "", "", *nrAreas);
		}else if(tNR == 2){
			fscanf(f,"\t%s\t%s",&t1, &t2);
			tAreas = addAreaEnd(tAreas, tID, tType, tCap, tNR, t1, t2, "", *nrAreas);
		}else if(tNR == 3){
			fscanf(f,"\t%s\t%s\t%s",&t1,&t2,&t3);
			tAreas = addAreaEnd(tAreas, tID, tType, tCap, tNR, t1, t2, t3, *nrAreas);
		}else{
			exit(0);
		}
		fscanf(f,"%s\t%d\t%d\t%d", &tID, &tType, &tCap, &tNR);
		i++;
	}while(!feof(f));
	fclose(f);
	printf("%d areas carregadas!!\n", i);
	return tAreas;
}

void dispArea(Areas *tAreas, int nrAreas){
	int i;
	printf("[AREAS]\n");

	for(i=0;i<nrAreas;i++){
		if(tAreas[i].nr_front == 0){
			printf("[ID] (%s)   [Tipo] (%d)   [CAP] (%d/%d)\n", tAreas[i].id, tAreas[i].tipo, tAreas[i].pesoAct, tAreas[i].cap);
		}else if(tAreas[i].nr_front == 1){
			printf("[ID] (%s)   [Tipo] (%d)   [CAP] (%d/%d)   [F1] (%s)\n", tAreas[i].id, tAreas[i].tipo, tAreas[i].pesoAct, tAreas[i].cap, tAreas[i].front1);
		}else if(tAreas[i].nr_front == 2){
			printf("[ID] (%s)   [Tipo] (%d)   [CAP] (%d/%d)   [F1] (%s)   [F2] (%s)\n", tAreas[i].id, tAreas[i].tipo, tAreas[i].pesoAct, tAreas[i].cap, tAreas[i].front1, tAreas[i].front2);
		}else if(tAreas[i].nr_front == 3){
			printf("[ID] (%s)   [Tipo] (%d)   [CAP] (%d/%d)   [F1] (%s)   [F2] (%s)   [F3] (%s)\n", tAreas[i].id, tAreas[i].tipo, tAreas[i].pesoAct, tAreas[i].cap, tAreas[i].front1, tAreas[i].front2, tAreas[i].front3);
		}
	}
}

void saveAreas(Areas *tAreas, int nrAreas){
	FILE *f;
    int i;
	printf("A abrir ficheiro de Areas...\n");
	f = fopen("areas.txt", "w+");
	if(f==NULL){
		printf("Erro a abrir ficheiro de areas!\n");
	}
	printf("A guardar Areas para ficheiro...\n");

    for(i=0;i<nrAreas;i++){
        if(tAreas[i].nr_front == 0){
            fprintf(f,"%s\t%d\t%d\t%d\n", tAreas[i].id, tAreas[i].tipo, tAreas[i].cap, tAreas[i].nr_front);
        }else if(tAreas[i].nr_front == 1){
            fprintf(f,"%s\t%d\t%d\t%d\t%s\n", tAreas[i].id, tAreas[i].tipo, tAreas[i].cap, tAreas[i].nr_front, tAreas[i].front1);
        }else if(tAreas[i].nr_front == 2){
            fprintf(f,"%s\t%d\t%d\t%d\t%s\t%s\n", tAreas[i].id, tAreas[i].tipo, tAreas[i].cap, tAreas[i].nr_front, tAreas[i].front1, tAreas[i].front2);
        }else if(tAreas[i].nr_front == 3){
            fprintf(f,"%s\t%d\t%d\t%d\t%s\t%s\t%s\n", tAreas[i].id, tAreas[i].tipo, tAreas[i].cap, tAreas[i].nr_front, tAreas[i].front1, tAreas[i].front2, tAreas[i].front3);
        }
    }

	fclose(f);
	printf("areas guardadas!!\n");
}

int nrFront(Areas *tAreas, char *id, int nrAreas){
    int i;
    for(i=0;i<nrAreas;i++){
        if(strcmp(tAreas[i].id, id)==0){
            return tAreas[i].nr_front;
        }
    }
	return -1;
}

Areas * addFronteira(Areas *tAreas, char *exist, char *novo, int nrAreas){
    int i;
	printf("A adicionar nova fronteira a area existente\n");

    for(i=0;i<nrAreas;i++){
        if(strcmp(tAreas[i].id, exist)==0){
            if(tAreas[i].nr_front == 1){
                tAreas[i].nr_front++;
                strcpy(tAreas[i].front2,novo);
            }else if(tAreas[i].nr_front == 2){
                tAreas[i].nr_front++;
                strcpy(tAreas[i].front3,novo);
            }
        }
    }
	printf("Area existente actualizada!\n");
	return tAreas;
}

int pesoActArea(Areas *tAreas, char *id, int nrAreas){
	int i;

    for(i=0;i<nrAreas;i++){
        if(strcmp(tAreas[i].id, id)==0){
			return tAreas[i].pesoAct;
        }
    }
	return -1;
}

int capArea(Areas *tAreas, char *id, int nrAreas){
	int i;

	for(i=0;i<nrAreas;i++){
		if(strcmp(tAreas[i].id, id)==0){
			return tAreas[i].cap;
		}
	}

	return -1;
}

Areas * rmArea(Areas *tAreas, char *id, int nrAreas){
	Areas *temp = malloc((sizeof(Areas)*(nrAreas-1)));
	int i, i2=0, i3=0;

	for(i=0;i<nrAreas;i++){
		if(strcmp(tAreas[i].id, id)==0){
			if(tAreas[i].pesoAct != 0){
				printf("area ainda tem animais!\n");
				return tAreas;
			}else{
				for(i2=0;i2<nrAreas;i2++){
					if(tAreas[i2].id != id){
						strcpy(temp[i2].id, tAreas[i3].id);
						temp[i2].tipo = tAreas[i3].tipo;
						temp[i2].cap = tAreas[i3].cap;
						temp[i2].pesoAct = tAreas[i3].pesoAct;
						temp[i2].nr_front = tAreas[i3].nr_front;
						strcpy(temp[i2].front1, tAreas[i3].front1);
						strcpy(temp[i2].front2, tAreas[i3].front2);
						strcpy(temp[i2].front3, tAreas[i3].front3);
					}else{
						i3++;
					}
					i3++;
				}
				return temp;
			}
		}
	}
	printf("Area nao encontrada!!!\n");
	return tAreas;
}

Areas * rmFronteira(Areas *tAreas, char *id, int nrAreas){
	int i;

	for(i=0;i<nrAreas;i++){
		if(tAreas[i].nr_front==1){
			if(strcmp(tAreas[i].front1,id)==0){
				tAreas[i].nr_front=0;
				strcpy(tAreas[i].front1,"");
			}
		}else if(tAreas[i].nr_front==2){
			if(strcmp(tAreas[i].front1, id) == 0){
				tAreas[i].nr_front--;
				strcpy(tAreas[i].front1, tAreas[i].front2);
				strcpy(tAreas[i].front2, "");
			}else if(strcmp(tAreas[i].front2, id) == 0){
				tAreas[i].nr_front--;
				strcpy(tAreas[i].front2, "");
			}
		}else if(tAreas[i].nr_front==3){
			if(tAreas[i].front1==id){
				tAreas[i].nr_front--;
				strcpy(tAreas[i].front1, tAreas[i].front2);
				strcpy(tAreas[i].front2, tAreas[i].front3);
				strcpy(tAreas[i].front3, "");
			}else if(tAreas[i].front2==id){
				tAreas[i].nr_front--;
				strcpy(tAreas[i].front2, tAreas[i].front3);
				strcpy(tAreas[i].front3, "");
			}else if(tAreas[i].front3==id){
				tAreas[i].nr_front--;
				strcpy(tAreas[i].front3, "");
			}
		}
	}
	return tAreas;
}

bool areaExiste(Areas *tAreas, char *id, int nrAreas) {
	int i;
	for (i = 0; i < nrAreas; i++) {
		if (strcmp(tAreas[i].id, id) == 0) {
			return true;
		}
	}
	return false;
}