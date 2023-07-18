#ifndef DEF_RECHERCHE
#define DEF_RECHERCHE

//Calcul de la distance entre deux couleurs dans l'espace RGB
int calculDistanceCouleur(RgbColor couleur1, RgbColor couleur2);

//Fonctions utilisees pour calculer un nouveau profil
ComposantesNuance1D rechercheNuanceProche1D(const RgbColor couleur,const RgbColor *nuancier1D, int *tableauErreur);
ComposantesNuance2D rechercheNuanceProche2D(const RgbColor couleur,const RgbColor *nuancier2D, int *tableauErreur);
ComposantesNuance3D rechercheNuanceProche3D(const RgbColor couleur,const RgbColor *nuancier3D, int *tableauErreur);
ComposantesNuance4D rechercheNuanceProche4D(const RgbColor couleur,const RgbColor *nuancier4D, int *tableauErreur);

//Fonctions d'interpolation a partir des valeurs du profil
ComposantesNuance1D interpolation1D(const RgbColor couleur, ComposantesNuance1D *profil);
ComposantesNuance2D interpolation2D(const RgbColor couleur, ComposantesNuance2D *profil);
ComposantesNuance3D interpolation3D(const RgbColor couleur, ComposantesNuance3D *profil);
ComposantesNuance4D interpolation4D(const RgbColor couleur, ComposantesNuance4D *profil);

//Recherche la premiere occurence d'un minimum dans une liste
//puis retourne son indice dans la liste et stocke sa valeur dans la variable minimum
//qui doit avoir été déclarée au préalable
int rechercheMinimum(int *tableauDeFloats, int tailleTableau);

//pour simuler l'impression à partir des composantes en 2D et 3D
RgbColor *simulerImpression1D(const unsigned char *composante1, const RgbColor couleurPapier, const RgbColor couleur1, const int tailleImage);
RgbColor *simulerImpression2D(const unsigned char *composante1, const unsigned char *composante2, const RgbColor couleurPapier, const RgbColor couleur1, const RgbColor couleur2, const int tailleImage);
RgbColor *simulerImpression3D(const unsigned char *composante1, const unsigned char *composante2, const unsigned char *composante3, const RgbColor couleurPapier,const RgbColor couleur1, const RgbColor couleur2, const RgbColor couleur3, const int tailleImage);
RgbColor *simulerImpression4D(const unsigned char *composante1, const unsigned char *composante2, const unsigned char *composante3, const unsigned char *composante4,
                                const RgbColor couleurPapier,const RgbColor couleur1, const RgbColor couleur2, const RgbColor couleur3, const RgbColor couleur4,
                                const int tailleImage);







#endif