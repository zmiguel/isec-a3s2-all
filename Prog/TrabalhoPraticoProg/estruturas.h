struct animal_s{
	int filhoID;
	struct animais_st *strt;
};

typedef struct area_st{
  int id;
  int tipo; // 0 = jaula, 1 = espaço vedado
  int cap;
  int pesoAct;
  //fronteiras
  int nr_front;
  int front1;
  int front2;
  int front3;
}Areas;

typedef struct animais_st{
  int id;
  char especie[100];
  char nome[100];
  int peso;
  int loc;
  //filho
  struct animal_s filho;
  //next ID
  struct animais_st *prox;
}Animais;
