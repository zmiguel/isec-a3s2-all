Animais * addAnimaisEnd(Animais *tAnimais, Areas *tAreas, int id, char *especie, char *nome, int peso, int locID, int filho, int nrAreas);
Animais * importAnimaisFile(Animais *tAnimais, char *nfile, Areas *tAreas, int nrAreas);
Animais * readAnimais(Animais *tAnimais, Areas *tAreas, int nrAreas);
Areas * addAreaEnd(Areas *tAreas, int id, int tipo, int cap, int nr_front, int front1, int front2, int front3, int nrAreas);
Areas * addFronteira(Areas *tAreas, int exist, int novo, int nrAreas);
Areas * linkAreas(Areas *tAreas);
Areas * readAreas(Areas *tAreas, int *nrAreas);
Areas * rmArea(Areas *tAreas, int id, int nrAreas);
Areas * rmFronteira(Areas *tAreas, int id, int nrAreas);
bool verifyFilho2(Animais *tAnimais,int id1, int id2);
int capArea(Areas *tArea, int id, int nrAreas);
int getLastAnimalID(Animais *tAnimais);
int getLastAreaID(Areas *tAreas, int nrAreas);
int main(void);
int menu(void);
int nrFront(Areas *tArea, int id, int nrAreas);
int pesoActArea(Areas *tArea, int id, int nrAreas);
void criaFilho1(Animais *tAnimais, Areas *tAreas, int id, char *nome, int nrAreas);
void criaFilho2(Animais *tAnimais, Areas *tAreas, int id1, int id2, char *nome, int nrAreas);
void dispAnimais(Animais *tAnimais);
void dispAnimaisArea(Animais *tAnimais, Areas *tAreas, int id, int nrAreas);
void dispAnimaisEspecie(Animais *tAnimais, char *especie);
void dispAnimalID(Animais *tAnimais, int id);
void dispAnimalNome(Animais *tAnimais, char *nome);
void dispArea(Areas *tArea, int nrAreas);
void dispIntro(void);
void linkAnimais(Animais *tAnimais);
void rmAnimalID(Animais *tAnimais, Areas *tAreas, int id, int nrAreas);
void rmAnimalNome(Animais *tAnimais, Areas *tAreas, char *nome, int nrAreas);
void saveAnimais(Animais *tAnimais);
void saveAreas(Areas *tAreas, int nrAreas);
void transfAnimal(Animais *tAnimais, Areas *tAreas, int id, int desto, int nrAreas);
