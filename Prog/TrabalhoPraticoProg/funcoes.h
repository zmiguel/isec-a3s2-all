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

void dispIntro(void){
	printf("\n\tZZZZZZZZZZZZZZZZZZZ\n\tZ:::::::::::::::::Z\n\tZ:::::::::::::::::Z\n\tZ:::ZZZZZZZZ:::::Z\n\tZZZZZ     Z:::::Z     ooooooooooo      ooooooooooo\n\t        Z:::::Z     oo:::::::::::oo  oo:::::::::::oo\n\t       Z:::::Z     o:::::::::::::::oo:::::::::::::::o\n\t      Z:::::Z      o:::::ooooo:::::oo:::::ooooo:::::o\n\t     Z:::::Z       o::::o     o::::oo::::o     o::::o\n\t    Z:::::Z        o::::o     o::::oo::::o     o::::o\n\t   Z:::::Z         o::::o     o::::oo::::o     o::::o\n\tZZZ:::::Z     ZZZZZo::::o     o::::oo::::o     o::::o\n\tZ::::::ZZZZZZZZ:::Zo:::::ooooo:::::oo:::::ooooo:::::o\n\tZ:::::::::::::::::Zo:::::::::::::::oo:::::::::::::::o\n\tZ:::::::::::::::::Z oo:::::::::::oo  oo:::::::::::oo\n\tZZZZZZZZZZZZZZZZZZZ   ooooooooooo      ooooooooooo\n");

	printf("\n#     #                                                 #######                                    \n#     #   ##   #      ######    #####    ##    ####     #       #       ####  #####  ######  ####  \n#     #  #  #  #      #         #    #  #  #  #         #       #      #    # #    # #      #      \n#     # #    # #      #####     #    # #    #  ####     #####   #      #    # #    # #####   ####  \n #   #  ###### #      #         #    # ######      #    #       #      #    # #####  #           # \n  # #   #    # #      #         #    # #    # #    #    #       #      #    # #   #  #      #    # \n   #    #    # ###### ######    #####  #    #  ####     #       ######  ####  #    # ######  ####  \n");
}
