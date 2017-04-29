struct area{
  int id;
  struct area_st *area;
};

struct fam{
	int paiID;
	struct animais_st *pai;
	int maeID;
    struct animais_st *mae;
};

typedef struct area_st{
  int id;
  int tipo; // 0 = jaula, 1 = espaço vedado
  int cap;
  int pesoAct;
  //fronteiras
  int nr_front;
  struct area front1;
  struct area front2;
  struct area front3;
  //next ID
  struct area_st *prox;
}Areas;

typedef struct animais_st{
  int id;
  char especie[100];
  char nome[100];
  int peso;
  struct area loc;
  //familia
  struct fam familia;
  //next ID
  struct animais_st *prox;
}Animais;
