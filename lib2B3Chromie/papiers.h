//Ce fichier definit les fonctions et objets en lien avec la gestion des couleurs de papier de l'utilisateur
//et qui sont enregistrees dans le fichier ./Profils/papiers.2b3
#ifndef DEF_PAPIERS
#define DEF_PAPIERS

#define NB_MAX_PAPIER 40
#define EMPLACEMENT_LIBRE 0
#define EMPLACEMENT_OCCUPE 1

int lectureEnteteFichierPapiers(); //Fonction pour connaitre ne nombre de papiers enregistres a partir de l'entete
void ouvrirFichierPapiers(int nombrePapiersEnregistres, Papier *listePapiers);
void ajouterPapier();
void supprimerPapier();
void ordonnerPapiers(Papier *listePapiers, int nombrePapiersAvantSuppression);




#endif