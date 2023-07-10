//Ce fichier definit les fonctions et objets en lien avec la gestion des couleurs d'impression de l'utilisateur
//et qui sont enregistrees dans le fichier ./Profils/couleurs.2b3
#ifndef DEF_COULEURS
#define DEF_COULEURS

#define NB_MAX_COULEUR 40
#define EMPLACEMENT_LIBRE 0
#define EMPLACEMENT_OCCUPE 1


//Couleurs RGB des principales couleurs riso, données récupérées sur http://stencil.wiki/colors
#define BLANC {"BLANC", 255 ,255 ,255}
#define BLACK {"BLACK",0,0,0}
#define BURGUNDY {"BURGUNDY",145, 78, 114}
#define BLUE {"BLUE",0, 120, 191}
#define GREEN {"GREEN",0, 169, 92}
#define MEDIUM_BLUE {"MEDIUM_BLUE",50, 85, 164}
#define BRIGHT_RED {"BRIGHT_RED",241, 80, 96}
#define PURPLE {"PURPLE",118, 91, 167}
#define TEAL {"TEAL",0, 131, 138}
#define FLAT_GOLD {"FLAT_GOLD",187, 139, 65}
#define HUNTER_GREEN {"HUNTER_GREEN",64, 112, 96}
#define PURE_RED {"PURE_RED",255, 0, 0}
#define RED {"RED",255, 102, 94}
#define BROWN {"BROWN",146, 95, 82}
#define FEDERAL_BLUE {"FEDERAL_BLUE",61, 85, 136}
#define YELLOW {"YELLOW",255, 232, 0}
#define MARINE_RED {"MARINE_RED",210, 81, 94}
#define ORANGE {"ORANGE",255, 108, 47}
#define FLUORESCENT_PINK {"FLUORESCENT_PINK",255, 72, 176}


int lectureEnteteFichierCouleurs(); //Fonction pour connaitre ne nombre de couleurs enregistres a partir de l'entete
void ouvrirFichierCouleurs(int nombreCouleursEnregistres, Couleur *listeCouleurs);
void ajouterCouleur();
void supprimerCouleur();
void ordonnerCouleurs(Couleur *listeCouleurs, int nombreCouleursAvantSuppression);

unsigned int identifierCouleur(RgbColor couleur); //donne un identifiant unique pour chaque couleur



#endif