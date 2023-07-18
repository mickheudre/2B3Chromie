#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "structures.h"
#include "couleurs.h"
#include "conversion.h"
#include "memoire.h"

int lectureEnteteFichierCouleurs()
{
    FILE *fichierCouleurs=NULL;
    EnteteFichierCouleurs enteteFichierCouleurs;
    
    if((fichierCouleurs=fopen("profils/couleurs.2b3","rb"))==NULL) //Le fichiers n'existe pas
    {
        //----Creation et initialisation du fichier contenant les couleurs---
        int nombreMaxCouleur=NB_MAX_COULEUR;
        int nombreCouleursParDefaut=18;

        Couleur couleursParDefaut[18]={
        {EMPLACEMENT_OCCUPE,"BLACK",{0,0,0}},
        {EMPLACEMENT_OCCUPE,"BURGUNDY",{145, 78, 114}},
        {EMPLACEMENT_OCCUPE,"BLUE",{0, 120, 191}},
        {EMPLACEMENT_OCCUPE,"GREEN",{0, 169, 92}},
        {EMPLACEMENT_OCCUPE,"MEDIUM_BLUE",{50, 85, 164}},
        {EMPLACEMENT_OCCUPE,"BRIGHT_RED",{241, 80, 96}},
        {EMPLACEMENT_OCCUPE,"PURPLE",{118, 91, 167}},
        {EMPLACEMENT_OCCUPE,"TEAL",{0, 131, 138}},
        {EMPLACEMENT_OCCUPE,"FLAT_GOLD",{187, 139, 65}},
        {EMPLACEMENT_OCCUPE,"HUNTER_GREEN",{64, 112, 96}},
        {EMPLACEMENT_OCCUPE,"PURE_RED",{255, 0, 0}},
        {EMPLACEMENT_OCCUPE,"RED",{255, 102, 94}},
        {EMPLACEMENT_OCCUPE,"BROWN",{146, 95, 82}},
        {EMPLACEMENT_OCCUPE,"FEDERAL_BLUE",{61, 85, 136}},
        {EMPLACEMENT_OCCUPE,"YELLOW",{255, 232, 0}},
        {EMPLACEMENT_OCCUPE,"MARINE_RED",{210, 81, 94}},
        {EMPLACEMENT_OCCUPE,"ORANGE",{255, 108, 47}},
        {EMPLACEMENT_OCCUPE,"FLUORESCENT_PINK",{255, 72, 176}}
        };

        fichierCouleurs=fopen("profils/couleurs.2b3","wb"); //Creation du fichier en ecriture
        //----Entete------------
        fwrite(&nombreMaxCouleur,sizeof(int),1,fichierCouleurs);
        fwrite(&nombreCouleursParDefaut,sizeof(int),1,fichierCouleurs);
        //----liste des couleurs-----
        fwrite(couleursParDefaut,sizeof(Couleur),nombreCouleursParDefaut,fichierCouleurs);
        //----fermeture du fichier cree-----
        fclose(fichierCouleurs);
        //----ouverture en lecture-------
        fichierCouleurs=fopen("profils/couleurs.2b3","rb");
    }
    fread(&enteteFichierCouleurs,sizeof(EnteteFichierCouleurs),1,fichierCouleurs);
    fclose(fichierCouleurs);
    return enteteFichierCouleurs.nombreCouleursEnregistres;
}

void ouvrirFichierCouleurs(int nombreCouleursEnregistres, Couleur *listeCouleurs)
{
    FILE *fichierCouleurs=NULL;
    EnteteFichierCouleurs enteteFichierCouleurs;
    
    if((fichierCouleurs=fopen("profils/couleurs.2b3","rb"))==NULL) //Le fichiers n'existe pas
    {
        printf("Erreur dans le chargement des couleurs disponibles\n");
        exit(0);
    }
    fread(&enteteFichierCouleurs,sizeof(EnteteFichierCouleurs),1,fichierCouleurs);
    nombreCouleursEnregistres=enteteFichierCouleurs.nombreCouleursEnregistres;
    fread(listeCouleurs,sizeof(Couleur),nombreCouleursEnregistres,fichierCouleurs);

    fclose(fichierCouleurs);
        
}

void ajouterCouleur()
{
    FILE *fichierCouleurs=NULL;
    EnteteFichierCouleurs enteteFichierCouleurs;
    int nombreinitialCouleursEnregistres;
    Couleur *listeCouleurs=NULL;

    Couleur nouveauCouleur={0};

    char nomNouveauCouleur[30];
    unsigned char nouveauCouleur_R=0;
    char nouveauCouleur_R_Char[10]="-1 ";
    unsigned char nouveauCouleur_G=0;
    char nouveauCouleur_G_Char[10]="-1 ";
    unsigned char nouveauCouleur_B=0;
    char nouveauCouleur_B_Char[10]="-1 ";
    
    if((fichierCouleurs=fopen("profils/couleurs.2b3","rb"))==NULL) //Le fichiers n'existe pas
    {
        //----Creation et initialisation du fichier contenant les couleurs---
        int nombreMaxCouleur=NB_MAX_COULEUR;
        int nombreCouleursParDefaut=18;

        Couleur couleursParDefaut[18]={
        {EMPLACEMENT_OCCUPE,"BLACK",{0,0,0}},
        {EMPLACEMENT_OCCUPE,"BURGUNDY",{145, 78, 114}},
        {EMPLACEMENT_OCCUPE,"BLUE",{0, 120, 191}},
        {EMPLACEMENT_OCCUPE,"GREEN",{0, 169, 92}},
        {EMPLACEMENT_OCCUPE,"MEDIUM_BLUE",{50, 85, 164}},
        {EMPLACEMENT_OCCUPE,"BRIGHT_RED",{241, 80, 96}},
        {EMPLACEMENT_OCCUPE,"PURPLE",{118, 91, 167}},
        {EMPLACEMENT_OCCUPE,"TEAL",{0, 131, 138}},
        {EMPLACEMENT_OCCUPE,"FLAT_GOLD",{187, 139, 65}},
        {EMPLACEMENT_OCCUPE,"HUNTER_GREEN",{64, 112, 96}},
        {EMPLACEMENT_OCCUPE,"PURE_RED",{255, 0, 0}},
        {EMPLACEMENT_OCCUPE,"RED",{255, 102, 94}},
        {EMPLACEMENT_OCCUPE,"BROWN",{146, 95, 82}},
        {EMPLACEMENT_OCCUPE,"FEDERAL_BLUE",{61, 85, 136}},
        {EMPLACEMENT_OCCUPE,"YELLOW",{255, 232, 0}},
        {EMPLACEMENT_OCCUPE,"MARINE_RED",{210, 81, 94}},
        {EMPLACEMENT_OCCUPE,"ORANGE",{255, 108, 47}},
        {EMPLACEMENT_OCCUPE,"FLUORESCENT_PINK",{255, 72, 176}}
        };

        fichierCouleurs=fopen("profils/couleurs.2b3","wb"); //Creation du fichier en ecriture
        //----Entete------------
        fwrite(&nombreMaxCouleur,sizeof(int),1,fichierCouleurs);
        fwrite(&nombreCouleursParDefaut,sizeof(int),1,fichierCouleurs);
        //----liste des couleurs-----
        fwrite(couleursParDefaut,sizeof(Couleur),nombreCouleursParDefaut,fichierCouleurs);
        //----fermeture du fichier cree-----
        fclose(fichierCouleurs);
        //----ouverture en lecture-------
        fichierCouleurs=fopen("profils/couleurs.2b3","rb");
    }
    fread(&enteteFichierCouleurs,sizeof(EnteteFichierCouleurs),1,fichierCouleurs);
    nombreinitialCouleursEnregistres=enteteFichierCouleurs.nombreCouleursEnregistres;
    listeCouleurs=malloc_erreurs((nombreinitialCouleursEnregistres+1)*sizeof(Couleur));
    fread(listeCouleurs,sizeof(Couleur),nombreinitialCouleursEnregistres,fichierCouleurs);
    fclose(fichierCouleurs);

    //-----Le logiciel demande les attributs de la couleur à ajouter
    int nouveauNomValide=0;
    int comparaison;
    
    if(nombreinitialCouleursEnregistres<NB_MAX_COULEUR)
    {
        while(nouveauNomValide==0)
        {
            printf("Indiquez le nom de la couleur en MAJUSCULES\n");
            lire(nomNouveauCouleur,30);
            for(int i=0;i<nombreinitialCouleursEnregistres;i++)
            {
                if((comparaison=strcmp(nomNouveauCouleur,listeCouleurs[i].couleur.nom))==0)
                {
                    printf("Ce nom est deja utilise\n");
                    break;
                }
                if(comparaison!=0&&i==(nombreinitialCouleursEnregistres-1))
                    nouveauNomValide=1;
            }
        }
        strcpy(nouveauCouleur.couleur.nom,nomNouveauCouleur);
        printf("Indiquez les composantes [R]ed, [G]reen et [B]lue entre 0 et 255\n");
        while(atoi(nouveauCouleur_R_Char)<0||atoi(nouveauCouleur_R_Char)>255)
        {
            printf("R = ");
            lire(nouveauCouleur_R_Char,10);
        }
        nouveauCouleur.couleur.couleur.r=(unsigned char)atoi(nouveauCouleur_R_Char);
        while(atoi(nouveauCouleur_G_Char)<0||atoi(nouveauCouleur_G_Char)>255)
        {
            printf("G = ");
            lire(nouveauCouleur_G_Char,10);
        }
        nouveauCouleur.couleur.couleur.g=(unsigned char)atoi(nouveauCouleur_G_Char);
        while(atoi(nouveauCouleur_B_Char)<0||atoi(nouveauCouleur_B_Char)>255)
        {
            printf("B = ");
            lire(nouveauCouleur_B_Char,10);
        }

        int couleurExistePas=1;
        for(int i=0;i<nombreinitialCouleursEnregistres;i++)
        {
                if(identifierCouleur(nouveauCouleur.couleur.couleur)==identifierCouleur(listeCouleurs[i].couleur.couleur))
                {
                    printf("Cette nuance existe deja et s'appelle : %s\n",listeCouleurs[i].couleur.nom);
                    sleep(1);
                    couleurExistePas=0;
                    break;
                }
        }
        if(couleurExistePas)
        {
        nouveauCouleur.couleur.couleur.b=(unsigned char)atoi(nouveauCouleur_B_Char);
        listeCouleurs[nombreinitialCouleursEnregistres]=nouveauCouleur;
        listeCouleurs[nombreinitialCouleursEnregistres].emplacement=EMPLACEMENT_OCCUPE;

        enteteFichierCouleurs.nombreMaxiCouleurs=NB_MAX_COULEUR;
        enteteFichierCouleurs.nombreCouleursEnregistres=nombreinitialCouleursEnregistres+1;

        fichierCouleurs=fopen("profils/couleurs.2b3","wb");
        fwrite(&enteteFichierCouleurs,sizeof(enteteFichierCouleurs),1,fichierCouleurs);
        fwrite(listeCouleurs,sizeof(Couleur),nombreinitialCouleursEnregistres+1,fichierCouleurs);
        fclose(fichierCouleurs);
        }
    }else
    {
        printf("Nombre maximum de couleurs atteint\nSupprimez-en d'abord\n");
    }

}

void supprimerCouleur()
{
    FILE *fichierCouleurs=NULL;
    EnteteFichierCouleurs enteteFichierCouleurs;
    int nombreinitialCouleursEnregistres;
    Couleur *listeCouleurs=NULL;

    char couleurSupprimeChar[10]={0};
    int couleurSupprime;

    if((fichierCouleurs=fopen("profils/couleurs.2b3","rb"))==NULL) //Le fichiers n'existe pas
    {
        //----Creation et initialisation du fichier contenant les couleurs---
        int nombreMaxCouleur=NB_MAX_COULEUR;
        int nombreCouleursParDefaut=7;

        Couleur couleursParDefaut[18]={
        {EMPLACEMENT_OCCUPE,"BLACK",{0,0,0}},
        {EMPLACEMENT_OCCUPE,"BURGUNDY",{145, 78, 114}},
        {EMPLACEMENT_OCCUPE,"BLUE",{0, 120, 191}},
        {EMPLACEMENT_OCCUPE,"GREEN",{0, 169, 92}},
        {EMPLACEMENT_OCCUPE,"MEDIUM_BLUE",{50, 85, 164}},
        {EMPLACEMENT_OCCUPE,"BRIGHT_RED",{241, 80, 96}},
        {EMPLACEMENT_OCCUPE,"PURPLE",{118, 91, 167}},
        {EMPLACEMENT_OCCUPE,"TEAL",{0, 131, 138}},
        {EMPLACEMENT_OCCUPE,"FLAT_GOLD",{187, 139, 65}},
        {EMPLACEMENT_OCCUPE,"HUNTER_GREEN",{64, 112, 96}},
        {EMPLACEMENT_OCCUPE,"PURE_RED",{255, 0, 0}},
        {EMPLACEMENT_OCCUPE,"RED",{255, 102, 94}},
        {EMPLACEMENT_OCCUPE,"BROWN",{146, 95, 82}},
        {EMPLACEMENT_OCCUPE,"FEDERAL_BLUE",{61, 85, 136}},
        {EMPLACEMENT_OCCUPE,"YELLOW",{255, 232, 0}},
        {EMPLACEMENT_OCCUPE,"MARINE_RED",{210, 81, 94}},
        {EMPLACEMENT_OCCUPE,"ORANGE",{255, 108, 47}},
        {EMPLACEMENT_OCCUPE,"FLUORESCENT_PINK",{255, 72, 176}}
        };

        fichierCouleurs=fopen("profils/couleurs.2b3","wb"); //Creation du fichier en ecriture
        //----Entete------------
        fwrite(&nombreMaxCouleur,sizeof(int),1,fichierCouleurs);
        fwrite(&nombreCouleursParDefaut,sizeof(int),1,fichierCouleurs);
        //----liste des couleurs-----
        fwrite(couleursParDefaut,sizeof(Couleur),nombreCouleursParDefaut,fichierCouleurs);
        //----fermeture du fichier cree-----
        fclose(fichierCouleurs);
        //----ouverture en lecture-------
        fichierCouleurs=fopen("profils/couleurs.2b3","rb");
    }

    fread(&enteteFichierCouleurs,sizeof(EnteteFichierCouleurs),1,fichierCouleurs);
    nombreinitialCouleursEnregistres=enteteFichierCouleurs.nombreCouleursEnregistres;
    listeCouleurs=malloc_erreurs((nombreinitialCouleursEnregistres+1)*sizeof(Couleur));
    fread(listeCouleurs,sizeof(Couleur),nombreinitialCouleursEnregistres,fichierCouleurs);
    fclose(fichierCouleurs);

    system("clear");
    printLogo();
    printf("Ajout/Suppression de couleurs\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("Indiquez la couleur que vous souhaitez supprimer :\n");
    for(int i=1;i<nombreinitialCouleursEnregistres+1;i++){
        printf("%d-%s ",i,listeCouleurs[i-1].couleur.nom);
        printf("[%d,%d,%d]\n",listeCouleurs[i-1].couleur.couleur.r,listeCouleurs[i-1].couleur.couleur.g,listeCouleurs[i-1].couleur.couleur.b);
    }
    printf("%d-Annuler :)\n",nombreinitialCouleursEnregistres+1);
    lire(couleurSupprimeChar,10);
    couleurSupprime=atoi(couleurSupprimeChar);
    while(couleurSupprime<1||couleurSupprime>nombreinitialCouleursEnregistres+1)
    {
        printf("Ceci n'est pas une entrée valide\n");
        lire(couleurSupprimeChar,10);
    }
    if(couleurSupprime==nombreinitialCouleursEnregistres+1) //ANNULATION SUPPRESSION
        return;

    listeCouleurs[couleurSupprime-1].emplacement=EMPLACEMENT_LIBRE;
    printf("Couleur %s supprimee\n",listeCouleurs[couleurSupprime-1].couleur.nom);
    sleep(1);
    ordonnerCouleurs(listeCouleurs,nombreinitialCouleursEnregistres);

    enteteFichierCouleurs.nombreMaxiCouleurs=NB_MAX_COULEUR;
    enteteFichierCouleurs.nombreCouleursEnregistres=nombreinitialCouleursEnregistres-1;

    fichierCouleurs=fopen("profils/couleurs.2b3","wb");
    fwrite(&enteteFichierCouleurs,sizeof(enteteFichierCouleurs),1,fichierCouleurs);
    fwrite(listeCouleurs,sizeof(Couleur),enteteFichierCouleurs.nombreCouleursEnregistres,fichierCouleurs);
    fclose(fichierCouleurs);

}

void ordonnerCouleurs(Couleur *listeCouleurs, int nombreCouleursAvantSuppression)
{
    int a=0;
    while(a!=(nombreCouleursAvantSuppression-1))
    {
        a=0;
        for(int i=0;i<nombreCouleursAvantSuppression;i++)
        {
            if(listeCouleurs[i].emplacement==EMPLACEMENT_LIBRE)
            {
                a=i;
                break;
            }
        }
        listeCouleurs[a]=listeCouleurs[a+1];
        listeCouleurs[a+1].emplacement=EMPLACEMENT_LIBRE;
    }
    
}


unsigned int identifierCouleur(RgbColor couleur)
{
    return 256*256*couleur.r+256*couleur.g+couleur.b;
}
