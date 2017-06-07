struct fam{
	int fnr;
	int fID;
	int fID2;
	struct animais_st *strt;
};

typedef struct area_st{
  char id[100];
  int tipo; // 0 = jaula, 1 = espaço vedado
  int cap;
  int pesoAct;
  //fronteiras
  int nr_front;
  char front1[100];
  char front2[100];
  char front3[100];
}Areas;

typedef struct animais_st{
  int id;
  char especie[100];
  char nome[100];
  int peso;
  char loc[100];
  //familia
  struct fam filho;
  struct fam pais;
  //next ID
  struct animais_st *prox;
}Animais;
