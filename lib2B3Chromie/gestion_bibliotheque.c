#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "structures.h"
#include "conversion.h"
#include "gestion_bibliotheque.h"
#include "papiers.h"
#include "recherche.h"
#include "couleurs.h"

//charger profil 1D, le creer si il n'existe pas
int chargerProfil1D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, ComposantesNuance1D *profil1D, EnteteFichierProfil *entete)
{
    EnteteFichierProfil enteteProfil;
    DIR *dossierProfils=NULL;
    FILE *profil=NULL;
    char nomFichier[256];
    struct dirent *fichier;

    dossierProfils=opendir("profils/1_Couleurs");
    //La recherche du profil se fait par rapport aux couleurs reelles contenues dans l'entete du fichier
    while((fichier=readdir(dossierProfils))!=NULL)
    {
        sprintf(nomFichier,"profils/1_Couleurs/%s",fichier->d_name);
        if(strstr(nomFichier,".bib")!=NULL)
        {
            profil=fopen(nomFichier,"rb");
            fread(&enteteProfil,sizeof(EnteteFichierProfil),1,profil);
            if((identifierCouleur(enteteProfil.couleur1Rgb)==identifierCouleur(couleur1.couleur))
                &&(identifierCouleur(enteteProfil.couleurPapierRgb)==identifierCouleur(couleurPapier.couleur)))
            {
                *entete=enteteProfil;
                fread(profil1D,sizeof(ComposantesNuance1D),16*16*16,profil);
                fclose(profil);
                return 1;

            }
            fclose(profil);
            
        }
    }
    closedir(dossierProfils);
    return 0;
}

int creerProfil1D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, ComposantesNuance1D *profil1D, EnteteFichierProfil *entete, RgbColor *nuancier, int *tableauDesDifferences)
{

    RgbColor couleur={0,0,0};
    ComposantesNuance1D composantes1D={0};

    printf("Creation du profil %s sur papier %s\n", couleur1.nom, couleurPapier.nom);

    for(int i=0;i<16;i++)
    {
        printf("\r%d/16",i+1);
        fflush(stdout);
        couleur.r=i*17;
        for(int j=0;j<16;j++)
        {
            couleur.g=j*17;
            for(int k=0;k<16;k++)
            {
                couleur.b=k*17;
                composantes1D=rechercheNuanceProche1D(couleur,nuancier,tableauDesDifferences);
                profil1D[16*16*i+16*j+k]=composantes1D;
                  
            }
        }
        
    }
    printf("\n");
    //enregistrerProfil1D(couleurPapier,couleur1,profil1D);
    

    return 1;
}

int enregistrerProfil1D(CouleurDImpression couleurPapier, CouleurDImpression couleur1, ComposantesNuance1D *profil1D)
{
    FILE *profil=NULL;
    char nomProfil[100];
    EnteteFichierProfil entete;
    char repertoire[100]="profils/1_Couleurs/";
    if(sprintf(nomProfil,"profil_%s-papier_%s.bib",couleur1.nom,couleurPapier.nom)<0)
    {
        printf("Erreur d'enregistrement du profil\n");
        exit(0);
    }
    strcat(repertoire,nomProfil);

    profil=fopen(repertoire,"wb");
    if(profil==NULL)
    {
        printf("Erreur d'enregistrement du profil\n");
        exit(0);
    }
    entete.couleur1Rgb=couleur1.couleur;
    strcpy(entete.nomCouleur1,couleur1.nom);
    entete.couleurPapierRgb=couleurPapier.couleur;
    strcpy(entete.nomCouleurPapier,couleurPapier.nom);
    entete.nombreDeCouleurs=1;
    

    fwrite(&entete,sizeof(EnteteFichierProfil),1,profil);
    fwrite(profil1D,sizeof(ComposantesNuance1D),16*16*16,profil);
    fclose(profil);

    printf("Le profil %s sur papier %s est cree\n",couleur1.nom, couleurPapier.nom);

    return 1;
}

//charger un profil 2D, le creer si il n'existe pas
int chargerProfil2D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, ComposantesNuance2D *profil2D, EnteteFichierProfil *entete)
{
    EnteteFichierProfil enteteProfil;
    DIR *dossierProfils=NULL;
    FILE *profil=NULL;
    char nomFichier[256];
    struct dirent *fichier;

    dossierProfils=opendir("profils/2_Couleurs");
    //La recherche du profil se fait par rapport aux couleurs reelles contenues dans l'entete du fichier
    while((fichier=readdir(dossierProfils))!=NULL)
    {
        sprintf(nomFichier,"profils/2_Couleurs/%s",fichier->d_name);
        if(strstr(nomFichier,".bib")!=NULL)
        {
            profil=fopen(nomFichier,"rb");
            fread(&enteteProfil,sizeof(EnteteFichierProfil),1,profil);
            if((identifierCouleur(enteteProfil.couleur1Rgb)==identifierCouleur(couleur1.couleur))
                &&(identifierCouleur(enteteProfil.couleur2Rgb)==identifierCouleur(couleur2.couleur))
                &&(identifierCouleur(enteteProfil.couleurPapierRgb)==identifierCouleur(couleurPapier.couleur)))
            {
                *entete=enteteProfil;
                fread(profil2D,sizeof(ComposantesNuance2D),16*16*16,profil);
                fclose(profil);
                return 1;

            }
            fclose(profil);
            
        }
    }
    closedir(dossierProfils);
    return 0;
}

int creerProfil2D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, ComposantesNuance2D *profil2D, EnteteFichierProfil *entete, RgbColor *nuancier, int *tableauDesDifferences)
{
    RgbColor couleur={0,0,0};
    ComposantesNuance2D composantes2D={0,0};
    int nombreNuancesProfil = 4096;

    printf("Creation du profil %s + %s sur papier %s\n", couleur1.nom, couleur2.nom, couleurPapier.nom);

    for(int i=0;i<16;i++)
    {
        printf("\r%d/16",i+1);
        fflush(stdout);
        couleur.r=i*17;
        for(int j=0;j<16;j++)
        {
            couleur.g=j*17;
            for(int k=0;k<16;k++)
            {
                couleur.b=k*17;
                composantes2D=rechercheNuanceProche2D(couleur,nuancier,tableauDesDifferences);
                profil2D[16*16*i+16*j+k]=composantes2D;
                  
            }
        }
        
    }
    printf("\n");
    enregistrerProfil2D(couleurPapier,couleur1,couleur2,profil2D);
    

    return 1;
}

int enregistrerProfil2D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, ComposantesNuance2D *profil2D)
{
    FILE *profil=NULL;
    char nomProfil[100];
    EnteteFichierProfil entete;
    char repertoire[100]="profils/2_Couleurs/";
    if(sprintf(nomProfil,"profil_%s__%s-papier_%s.bib",couleur1.nom,couleur2.nom,couleurPapier.nom)<0)
    {
        printf("Erreur d'enregistrement du profil\n");
        exit(0);
    }
    strcat(repertoire,nomProfil);

    profil=fopen(repertoire,"wb");
    if(profil==NULL)
    {
        printf("Erreur d'enregistrement du profil\n");
        exit(0);
    }
    entete.couleur1Rgb=couleur1.couleur;
    strcpy(entete.nomCouleur1,couleur1.nom);
    entete.couleur2Rgb=couleur2.couleur;
    strcpy(entete.nomCouleur2,couleur2.nom);
    entete.couleurPapierRgb=couleurPapier.couleur;
    strcpy(entete.nomCouleurPapier,couleurPapier.nom);
    entete.nombreDeCouleurs=2;
    

    fwrite(&entete,sizeof(EnteteFichierProfil),1,profil);
    fwrite(profil2D,sizeof(ComposantesNuance2D),16*16*16,profil);
    fclose(profil);

    printf("Le profil %s + %s sur papier %s est cree\n",couleur1.nom,couleur2.nom,couleurPapier.nom);

    return 1;
}

int chargerProfil3D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, ComposantesNuance3D *profil3D, EnteteFichierProfil *entete)
{
    EnteteFichierProfil enteteProfil;
    DIR *dossierProfils=NULL;
    FILE *profil=NULL;
    char nomFichier[256];
    struct dirent *fichier;

    dossierProfils=opendir("profils/3_Couleurs");
    //La recherche du profil se fait par rapport aux couleurs reelles contenues dans l'entete du fichier
    while((fichier=readdir(dossierProfils))!=NULL)
    {
        sprintf(nomFichier,"profils/3_Couleurs/%s",fichier->d_name);
        if(strstr(nomFichier,".bib")!=NULL)
        {
            profil=fopen(nomFichier,"rb");
            fread(&enteteProfil,sizeof(EnteteFichierProfil),1,profil);
            if((identifierCouleur(enteteProfil.couleur1Rgb)==identifierCouleur(couleur1.couleur))
                &&(identifierCouleur(enteteProfil.couleur2Rgb)==identifierCouleur(couleur2.couleur))
                &&(identifierCouleur(enteteProfil.couleur3Rgb)==identifierCouleur(couleur3.couleur))
                &&(identifierCouleur(enteteProfil.couleurPapierRgb)==identifierCouleur(couleurPapier.couleur)))
            {
                *entete=enteteProfil;
                fread(profil3D,sizeof(ComposantesNuance3D),16*16*16,profil);
                fclose(profil);
                return 1;

            }
            fclose(profil);
            
        }
    }
    closedir(dossierProfils);
    return 0;
}

int creerProfil3D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, ComposantesNuance3D *profil3D, EnteteFichierProfil *entete, RgbColor *nuancier, int *tableauDesDifferences)
{
    RgbColor couleur={0,0,0};
    ComposantesNuance3D composantes3D={0,0,0};

    printf("Creation du profil %s + %s + %s sur papier %s\n", couleur1.nom, couleur2.nom, couleur3.nom, couleurPapier.nom);

    for(int i=0;i<16;i++)
    {
        printf("\r%d/16",i+1);
        fflush(stdout);
        couleur.r=i*17;
        for(int j=0;j<16;j++)
        {
            couleur.g=j*17;
            for(int k=0;k<16;k++)
            {
                couleur.b=k*17;
                composantes3D=rechercheNuanceProche3D(couleur,nuancier,tableauDesDifferences);
                profil3D[16*16*i+16*j+k]=composantes3D;
                
            }
        }
        
    }
    printf("\n");
    enregistrerProfil3D(couleurPapier,couleur1,couleur2,couleur3, profil3D);
    

    return 1;
}

int enregistrerProfil3D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, ComposantesNuance3D *profil3D)
{
    FILE *profil=NULL;
    char nomProfil[100];
    EnteteFichierProfil entete;
    char repertoire[100]="profils/3_Couleurs/";
    if(sprintf(nomProfil,"profil_%s__%s__%s-papier_%s.bib",couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom)<0)
    {
        printf("Erreur d'enregistrement du profil\n");
        exit(0);
    }
    strcat(repertoire,nomProfil);

    profil=fopen(repertoire,"wb");
    if(profil==NULL)
    {
        printf("Erreur d'enregistrement du profil\n");
        exit(0);
    }
    entete.couleur1Rgb=couleur1.couleur;
    strcpy(entete.nomCouleur1,couleur1.nom);
    entete.couleur2Rgb=couleur2.couleur;
    strcpy(entete.nomCouleur2,couleur2.nom);
    entete.couleur3Rgb=couleur3.couleur;
    strcpy(entete.nomCouleur3,couleur3.nom);
    entete.couleurPapierRgb=couleurPapier.couleur;
    strcpy(entete.nomCouleurPapier,couleurPapier.nom);
    entete.nombreDeCouleurs=3;
    
    fwrite(&entete,sizeof(EnteteFichierProfil),1,profil);
    fwrite(profil3D,sizeof(ComposantesNuance3D),16*16*16,profil);
    fclose(profil);

    printf("Le profil %s + %s + %s sur papier %s est cree\n",couleur1.nom,couleur2.nom,couleur3.nom, couleurPapier.nom);

    return 1;
}

int chargerProfil4D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3,CouleurDImpression couleur4, ComposantesNuance4D *profil4D, EnteteFichierProfil *entete)
{
    EnteteFichierProfil enteteProfil;
    DIR *dossierProfils=NULL;
    FILE *profil=NULL;
    char nomFichier[256];
    struct dirent *fichier;

    dossierProfils=opendir("profils/4_Couleurs");
    //La recherche du profil se fait par rapport aux couleurs reelles contenues dans l'entete du fichier
    while((fichier=readdir(dossierProfils))!=NULL)
    {
        sprintf(nomFichier,"profils/4_Couleurs/%s",fichier->d_name);
        if(strstr(nomFichier,".bib")!=NULL)
        {
            profil=fopen(nomFichier,"rb");
            fread(&enteteProfil,sizeof(EnteteFichierProfil),1,profil);
            if((identifierCouleur(enteteProfil.couleur1Rgb)==identifierCouleur(couleur1.couleur))
                &&(identifierCouleur(enteteProfil.couleur2Rgb)==identifierCouleur(couleur2.couleur))
                &&(identifierCouleur(enteteProfil.couleur3Rgb)==identifierCouleur(couleur3.couleur))
                &&(identifierCouleur(enteteProfil.couleur4Rgb)==identifierCouleur(couleur4.couleur))
                &&(identifierCouleur(enteteProfil.couleurPapierRgb)==identifierCouleur(couleurPapier.couleur)))
            {
                *entete=enteteProfil;
                fread(profil4D,sizeof(ComposantesNuance4D),16*16*16,profil);
                fclose(profil);
                closedir(dossierProfils);
                return 1;

            }
            fclose(profil);
            
        }
    }
    closedir(dossierProfils);
    return 0;
}

int creerProfil4D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, CouleurDImpression couleur4, ComposantesNuance4D *profil4D, EnteteFichierProfil *entete, RgbColor *nuancier, int *tableauDesDifferences)
{
    RgbColor couleur={0,0,0};
    ComposantesNuance4D composantes4D={0,0,0,0};

    printf("Creation du profil %s + %s + %s + %s sur papier %s\n", couleur1.nom, couleur2.nom, couleur3.nom, couleur4.nom, couleurPapier.nom);

    for(int i=0;i<16;i++)
    {
        printf("\r%d/16",i+1);
        fflush(stdout);
        couleur.r=i*17;
        for(int j=0;j<16;j++)
        {
            couleur.g=j*17;
            for(int k=0;k<16;k++)
            {
                couleur.b=k*17;
                composantes4D=rechercheNuanceProche4D(couleur,nuancier,tableauDesDifferences);
                profil4D[16*16*i+16*j+k]=composantes4D;
                
            }
        }
        
    }
    printf("\n");
    enregistrerProfil4D(couleurPapier,couleur1,couleur2,couleur3,couleur4,profil4D);
    

    return 1;
}

int enregistrerProfil4D(CouleurDImpression couleurPapier,CouleurDImpression couleur1, CouleurDImpression couleur2, CouleurDImpression couleur3, CouleurDImpression couleur4, ComposantesNuance4D *profil4D)
{
    FILE *profil=NULL;
    char nomProfil[200];
    EnteteFichierProfil entete;
    char repertoire[200]="profils/4_Couleurs/";
    if(sprintf(nomProfil,"profil_%s__%s__%s__%s-papier_%s.bib",couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom)<0)
    {
        printf("Erreur d'enregistrement du profil\n");
        exit(0);
    }
    strcat(repertoire,nomProfil);

    profil=fopen(repertoire,"wb");
    if(profil==NULL)
    {
        printf("Erreur d'enregistrement du profil\n");
        exit(0);
    }
    entete.couleur1Rgb=couleur1.couleur;
    strcpy(entete.nomCouleur1,couleur1.nom);
    entete.couleur2Rgb=couleur2.couleur;
    strcpy(entete.nomCouleur2,couleur2.nom);
    entete.couleur3Rgb=couleur3.couleur;
    strcpy(entete.nomCouleur3,couleur3.nom);
    entete.couleur4Rgb=couleur4.couleur;
    strcpy(entete.nomCouleur4,couleur4.nom);
    entete.couleurPapierRgb=couleurPapier.couleur;
    strcpy(entete.nomCouleurPapier,couleurPapier.nom);
    entete.nombreDeCouleurs=3;
    
    fwrite(&entete,sizeof(EnteteFichierProfil),1,profil);
    fwrite(profil4D,sizeof(ComposantesNuance4D),16*16*16,profil);
    fclose(profil);

    printf("Le profil %s + %s + %s + %s sur papier %s est cree\n",couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom, couleurPapier.nom);

    return 1;
}

void estimationTempsCalul(int nombreDeCouleurs, RgbColor *nuancier, int *tableauDesDifferences)
{
    int nombreNouvellesCouleurs=4096; //nombre de couleurs à calculer pour créer un profil 16*16*16
    int debutChrono=0, finChrono=0;
    RgbColor couleur={26,49,241}; //Couleur lambda utilisee pour mesurer le temps de calcul

    ComposantesNuance1D composantes1D; //pour stocker le resultat de la recherche en 1 couleurs
    ComposantesNuance2D composantes2D; //pour stocker le resultat de la recherche en 2 couleurs
    ComposantesNuance3D composantes3D; //Idem en 3 couleurs
    ComposantesNuance4D composantes4D; //Idem en 4 couleurs
    if (nombreDeCouleurs==1)
    {
        debutChrono=clock();
        composantes1D=rechercheNuanceProche1D(couleur,nuancier,tableauDesDifferences);
        finChrono=clock();
    }else if (nombreDeCouleurs==2)
    {
        debutChrono=clock();
        composantes2D=rechercheNuanceProche2D(couleur,nuancier,tableauDesDifferences);
        finChrono=clock();
    }else if(nombreDeCouleurs==3){
        debutChrono=clock();
        composantes3D=rechercheNuanceProche3D(couleur,nuancier,tableauDesDifferences);
        finChrono=clock();
    }
    else{
        debutChrono=clock();
        composantes4D=rechercheNuanceProche4D(couleur,nuancier,tableauDesDifferences);
        finChrono=clock();
    }
    printf("Temps de calcul estime : %f minutes\n",(float)(finChrono-debutChrono)/(CLOCKS_PER_SEC*60)*nombreNouvellesCouleurs);
}

void reordonnerProfil2CouleursV2(CouleurDImpression *couleur1,
                                CouleurDImpression *couleur2)
{
    CouleurDImpression tamponCouleur1=*couleur1, tamponCouleur2=*couleur2;
    if(identifierCouleur(couleur1->couleur)>identifierCouleur(couleur2->couleur))
    {
        *couleur1=tamponCouleur2;
        *couleur2=tamponCouleur1;
    }
    
}


void reordonnerProfil3CouleursV2(CouleurDImpression *couleur1,
                                CouleurDImpression *couleur2,
                                CouleurDImpression *couleur3)
{
    CouleurDImpression tamponCouleur;
    int tampon;
    while(!(identifierCouleur(couleur1->couleur)<=identifierCouleur(couleur2->couleur)&&identifierCouleur(couleur2->couleur)<=identifierCouleur(couleur3->couleur)))
    {
        if(identifierCouleur(couleur1->couleur)>identifierCouleur(couleur2->couleur))
        {
            tamponCouleur=*couleur1;
            *couleur1=*couleur2; 
            *couleur2=tamponCouleur;
        }
        if(identifierCouleur(couleur2->couleur)>identifierCouleur(couleur3->couleur))
        {
            tamponCouleur=*couleur2;
            *couleur2=*couleur3; 
            *couleur3=tamponCouleur;
        }
    }

}

void reordonnerProfil4CouleursV2(CouleurDImpression *couleur1,
                                CouleurDImpression *couleur2,
                                CouleurDImpression *couleur3,
                                CouleurDImpression *couleur4)
{
    CouleurDImpression tamponCouleur;
    int tampon;
    while(!(identifierCouleur(couleur1->couleur)<=identifierCouleur(couleur2->couleur)&&identifierCouleur(couleur2->couleur)<=identifierCouleur(couleur3->couleur)&&identifierCouleur(couleur3->couleur)<=identifierCouleur(couleur4->couleur)))
    {
        if(identifierCouleur(couleur1->couleur)>identifierCouleur(couleur2->couleur))
        {
            tamponCouleur=*couleur1;
            *couleur1=*couleur2; 
            *couleur2=tamponCouleur;
        }
        if(identifierCouleur(couleur2->couleur)>identifierCouleur(couleur3->couleur))
        {
            tamponCouleur=*couleur2;
            *couleur2=*couleur3; 
            *couleur3=tamponCouleur;
        }
        if(identifierCouleur(couleur3->couleur)>identifierCouleur(couleur4->couleur))
        {
            tamponCouleur=*couleur3;
            *couleur3=*couleur4; 
            *couleur4=tamponCouleur;
        }
    }

}
