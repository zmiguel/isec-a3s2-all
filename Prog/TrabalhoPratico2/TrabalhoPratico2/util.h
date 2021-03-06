/*
Jos� Miguel Dias Valdeviesso Alves
a21240042@alunos.isec.pt
P11 - Programa��o
*/
Animais * addAnimaisEnd(Animais *tAnimais, Areas *tAreas, int id, char *especie, char *nome, int peso, char *locID, int nrAreas);
Animais * importAnimaisFile(Animais *tAnimais, Areas *tAreas, char *nfile, int nrAreas);
Animais * readAnimais(Animais *tAnimais, Areas *tAreas, int nrAreas, bool compActive);
Areas * addAreaEnd(Areas *tAreas, char *id, int tipo, int cap, int nr_front, char *front1, char *front2, char *front3, int nrAreas);
Areas * addFronteira(Areas *tAreas, char *exist, char *novo, int nrAreas);
Areas * readAreas(Areas *tAreas, int *nrAreas);
Areas * rmArea(Areas *tAreas, char *id, int nrAreas);
Areas * rmFronteira(Areas *tAreas, char *id, int nrAreas);
bool verifyFilho2(Animais *tAnimais,int id1, int id2);
bool areaExiste(Areas *tAreas, char *id, int nrAreas);
int capArea(Areas *tArea, char *id, int nrAreas);
int getLastAnimalID(Animais *tAnimais);
int main(void);
int menu(void);
int nrFront(Areas *tArea, char *id, int nrAreas);
int pesoActArea(Areas *tArea, char *id, int nrAreas);
void criaFilho1(Animais *tAnimais, Areas *tAreas, int id, char *nome, int nrAreas);
void criaFilho2(Animais *tAnimais, Areas *tAreas, int id1, int id2, char *nome, int nrAreas);
void dispAnimais(Animais *tAnimais);
void dispAnimaisArea(Animais *tAnimais, char *id, int nrAreas);
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
void transfAnimal(Animais *tAnimais, Areas *tAreas, int id, char *desto, int nrAreas);
