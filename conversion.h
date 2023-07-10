#ifndef DEF_CONVERSION

#define DEF_CONVERSION
#define RESOLUTION 256
#define RESOLUTION_DIMINUE 83
#define PAS_RESOLUTION_DIMINUE 3 //82*3=255 ==> 0+3+3+3+.....+3=255 (83 pas)

// FONCTIONS DE CREATION DES NUANCIERS EN SELON LES COULEURS D'IMPRESSION
void creationNuancier1D(const RgbColor couleurPapier,
                        const RgbColor *couleur1,
                        RgbColor *nuancierRgb1D);

void creationNuancier2D(const RgbColor couleurPapier,
                        const RgbColor *couleur1,
                        const RgbColor *couleur2,
                        RgbColor *nuancierRgb2D);

void creationNuancier3D(const RgbColor couleurPapier,
                        const RgbColor *couleur1,
                        const RgbColor *couleur2,
                        const RgbColor *couleur3,
                        RgbColor *nuancierRgb3D);

void creationNuancier4D(const RgbColor couleurPapier,
                        const RgbColor *couleur1,
                        const RgbColor *couleur2,
                        const RgbColor *couleur3,
                        const RgbColor *couleur4,
                        RgbColor *nuancierRgb4D);




//Calcul des fichiers d'impression d'une image donnee
void calculerFichiersImpression1D(unsigned char *img,int width,int height,ComposantesNuance1D *profil1D, ElementBibliotheque1D *bibliotheque1D,int taux_encre_max);
void calculerFichiersImpression2D(unsigned char *img,int width,int height,ComposantesNuance2D *profil2D, ElementBibliotheque2D *bibliotheque2D,int taux_encre_max);
void calculerFichiersImpression3D(unsigned char *img,int width,int height,ComposantesNuance3D *profil3D, ElementBibliotheque3D *bibliotheque3D,int taux_encre_max);
void calculerFichiersImpression4D(unsigned char *img,int width,int height,ComposantesNuance4D *profil4D, ElementBibliotheque4D *bibliotheque4D,int taux_encre_max);
















#endif