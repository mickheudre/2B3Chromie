#ifndef DEF_STRUCTURES
#define DEF_STRUCTURES

// Pixel rgb 24bits
typedef struct RgbColor RgbColor;
struct RgbColor
{
    unsigned char r; //entre 0 et 255
    unsigned char g; //entre 0 et 255
    unsigned char b; //entre 0 et 255
};

// espace hsv (non utilise dans 2B3Chromie)
typedef struct HsvColor HsvColor;
struct HsvColor
{
    unsigned char h; //entre 0 et 255
    unsigned char s; //entre 0 et 255
    unsigned char v; //entre 0 et 255
};

// definition d'une couleur d'impression = son nom + sa couleur rgb
typedef struct
{
    char nom[30];
    RgbColor couleur;

}CouleurDImpression;

// definition d'une "couleur" dans le fichier de gestion des couleurs de l'utilisateur
typedef struct{
    int emplacement;
    CouleurDImpression couleur;
}Couleur;

// entete du fichier contenant les couleurs utilisateur
typedef struct{
    int nombreMaxiCouleurs;
    int nombreCouleursEnregistres;
}EnteteFichierCouleurs;

// definition d'une "papier" dans le fichier de gestion des papiers de l'utilisateur
typedef struct{
    int emplacement;
    CouleurDImpression papier;
}Papier;

// entete du fichier contenant les papiers utilisateur
typedef struct{
    int nombreMaxiPapiers;
    int nombrePapiersEnregistres;
}EnteteFichierPapiers;

// definition des composantes en niveau de gris de la decompostion 
typedef struct ComposantesNuance1D ComposantesNuance1D;
struct ComposantesNuance1D
{
    unsigned char composante1; //niveaux de gris
};

typedef struct ComposantesNuance2D ComposantesNuance2D;
struct ComposantesNuance2D
{
    unsigned char composante1; //niveaux de gris
    unsigned char composante2; //entre 0 et 255 
};

typedef struct ComposantesNuance3D ComposantesNuance3D;
struct ComposantesNuance3D
{
    unsigned char composante1; //niveaux de gris
    unsigned char composante2; //entre 0 et 255
    unsigned char composante3;
};

typedef struct ComposantesNuance4D ComposantesNuance4D;
struct ComposantesNuance4D
{
    unsigned char composante1; //niveaux de gris
    unsigned char composante2; //entre 0 et 255
    unsigned char composante3;
    unsigned char composante4;
};

// definition de l'entete d'un profil
typedef struct
{
    unsigned char nombreDeCouleurs; //nombre de couleurs utilisees pour l'impression
    char nomCouleur1[30]; //nom de la couleur en MAJUSCULES
    RgbColor couleur1Rgb; //indices RGB (R,G,B) entre 0 et 255
    char nomCouleur2[30];
    RgbColor couleur2Rgb;
    char nomCouleur3[30];
    RgbColor couleur3Rgb;
    char nomCouleur4[30];
    RgbColor couleur4Rgb;
    char nomCouleur5[30];
    RgbColor couleur5Rgb;
    char nomCouleurPapier[30];
    RgbColor couleurPapierRgb;

}EnteteFichierProfil;

// Non utilise encore : item d'une liste de profils utilisateur
typedef struct
{
    char nomProfilEnregistre[100];
    EnteteFichierProfil entete;

}ElementListeProfils;

// definitions d'un element de la table de conversion entre rgb et le jeu de couleurs choisies
typedef struct
{
    unsigned char dejaCalcule; //indicateur de calcul de la couleur; 1 si la couleur a été caculé, 0 sinon
    ComposantesNuance1D composantes;

}ElementBibliotheque1D;

typedef struct
{
    unsigned char dejaCalcule; //indicateur de calcul de la couleur; 1 si la couleur a été caculé, 0 sinon
    ComposantesNuance2D composantes;

}ElementBibliotheque2D;

typedef struct
{
    unsigned char dejaCalcule; //indicateur de calcul de la couleur; 1 si la couleur a été caculé, 0 sinon
    ComposantesNuance3D composantes;

}ElementBibliotheque3D;

typedef struct
{
    unsigned char dejaCalcule; //indicateur de calcul de la couleur; 1 si la couleur a été caculé, 0 sinon
    ComposantesNuance4D composantes;

}ElementBibliotheque4D;

#endif