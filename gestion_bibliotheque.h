#ifndef DEF_GESTION_BIBLIOTHEQUE
#define DEF_GESTION_BIBLIOTHEQUE

//PROTOTYPES DES FONCTIONS D'ECRITURE ET DE LECTURE ET DE CREATION DES BIBLIOTEQUES
//1D:MONOCHROMIE
int chargerProfil1D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, ComposantesNuance1D *profil1D, EnteteFichierProfil *entete);
int creerProfil1D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, ComposantesNuance1D *profil1D, EnteteFichierProfil *entete, RgbColor *nuancier, int *tableauDesDifferences);
int enregistrerProfil1D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, ComposantesNuance1D *profil1D);

//2D:BICHROMIE
int chargerProfil2D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, ComposantesNuance2D *profil2D, EnteteFichierProfil *entete);
int creerProfil2D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, ComposantesNuance2D *profil2D, EnteteFichierProfil *entete, RgbColor *nuancier, int *tableauDesDifferences);
int enregistrerProfil2D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, ComposantesNuance2D *profil2D);

//3D:TRICHROMIE
int chargerProfil3D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, ComposantesNuance3D *profil3D, EnteteFichierProfil *entete);
int creerProfil3D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, ComposantesNuance3D *profil3D, EnteteFichierProfil *entete, RgbColor *nuancier, int *tableauDesDifferences);
int enregistrerProfil3D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, ComposantesNuance3D *profil3D);

//4D:QUADRICHROMIE
int chargerProfil4D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, CouleurDImpression couleur4, ComposantesNuance4D *profil4D, EnteteFichierProfil *entete);
int creerProfil4D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, CouleurDImpression couleur4, ComposantesNuance4D *profil4D, EnteteFichierProfil *entete, RgbColor *nuancier, int *tableauDesDifferences);
int enregistrerProfil4D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, CouleurDImpression couleur4, ComposantesNuance4D *profil4D);

//Fonction d'estimation du temps de calcul d'un nouveau profil
void estimationTempsCalul(int nombreDeCouleurs, RgbColor *nuancier, int *tableauDesDifferences);

//Fonctions pour eviter les doublons de profils par ordre de selection des couleurs;

void reordonnerProfil2CouleursV2(CouleurDImpression *couleur1,
                                CouleurDImpression *couleur2);

void reordonnerProfil3CouleursV2(CouleurDImpression *couleur1,
                                CouleurDImpression *couleur2,
                                CouleurDImpression *couleur3);

void reordonnerProfil4CouleursV2(CouleurDImpression *couleur1,
                                CouleurDImpression *couleur2,
                                CouleurDImpression *couleur3,
                                CouleurDImpression *couleur4);

#endif