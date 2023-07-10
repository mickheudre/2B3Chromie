#ifndef DEF_MAIN
#define DEF_MAIN

//Definition des signatures possibles pour les JPEG (enregistrees en big-endian)
#define ISJPEGEXIF 0xE1FFD8FF //Vraie valeur 0xFFD8FFE1
#define ISJPEGJFIF 0xE0FFD8FF //...
#define ISJPEGSPIFF 0xE8FFD8FF //...
#define ISJPEGCANON 0xE2FFD8FF //...
#define ISJPEGSAMSUNG 0xE3FFD8FF //...

void *malloc_erreurs(unsigned int tailleMemoire);
void utilisation();
int lire(char *chaine, int longueur);
void viderBuffer();

void printLogo();









#endif