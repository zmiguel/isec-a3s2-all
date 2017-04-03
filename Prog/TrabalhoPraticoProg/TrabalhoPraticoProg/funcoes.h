#pragma once

Grid * addGridIni(Grid *gamegrid, char cont) {
	Grid *novo, *aux;
	aux = gamegrid;
	novo = /*(Grid *) */malloc(sizeof(Grid));
	if (novo == NULL) exit(0);
	novo->cont = cont;
	novo->prox = aux->prox;
	aux->prox = novo;
	return(aux);
}

Grid * addGridEnd(Grid *gamegrid, char cont, int lin, int col) {
	Grid *aux = gamegrid;

	while (aux->prox != NULL) {
		aux = aux->prox;
	}
	aux->prox = malloc(sizeof(Grid));
	aux->prox->cont = cont;
	aux->prox->lin = lin;
	aux->prox->col = col;
	aux->prox->prox = NULL;

	return gamegrid;
}