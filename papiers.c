#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "structures.h"
#include "papiers.h"
#include "main.h"
#include "couleurs.h"

int lectureEnteteFichierPapiers()
{
    FILE *fichierPapiers=NULL;
    EnteteFichierPapiers enteteFichierPapiers;
    
    if((fichierPapiers=fopen("profils/papiers.2b3","rb"))==NULL) //Le fichiers n'existe pas
    {
        //----Creation et initialisation du fichier contenant les papiers---
        int nombreMaxPapier=NB_MAX_PAPIER;
        int nombrePapiersParDefaut=7;

        Papier papiersParDefaut[7]={
        {EMPLACEMENT_OCCUPE,"BLANC",{255, 255, 255}},
        {EMPLACEMENT_OCCUPE,"IVOIRE",{254, 247, 226}},
        {EMPLACEMENT_OCCUPE,"GRIS_PERLE",{236, 234, 221}},
        {EMPLACEMENT_OCCUPE,"CANARI",{251, 241, 168}},
        {EMPLACEMENT_OCCUPE,"LAVANDE",{163, 186, 223}},
        {EMPLACEMENT_OCCUPE,"ROSE",{241, 220, 223}},
        {EMPLACEMENT_OCCUPE,"SAUMON",{243,216,204}},
        };

        fichierPapiers=fopen("profils/papiers.2b3","wb"); //Creation du fichier en ecriture
        //----Entete------------
        fwrite(&nombreMaxPapier,sizeof(int),1,fichierPapiers);
        fwrite(&nombrePapiersParDefaut,sizeof(int),1,fichierPapiers);
        //----liste des papiers-----
        fwrite(papiersParDefaut,sizeof(Papier),nombrePapiersParDefaut,fichierPapiers);
        //----fermeture du fichier cree-----
        fclose(fichierPapiers);
        //----ouverture en lecture-------
        fichierPapiers=fopen("profils/papiers.2b3","rb");
    }
    fread(&enteteFichierPapiers,sizeof(EnteteFichierPapiers),1,fichierPapiers);
    fclose(fichierPapiers);
    return enteteFichierPapiers.nombrePapiersEnregistres;
}

void ouvrirFichierPapiers(int nombrePapiersEnregistres, Papier *listePapiers)
{
    FILE *fichierPapiers=NULL;
    EnteteFichierPapiers enteteFichierPapiers;
    
    if((fichierPapiers=fopen("profils/papiers.2b3","rb"))==NULL) //Le fichiers n'existe pas
    {
        printf("Erreur dans le chargement des papiers disponibles\n");
        exit(0);
    }
    fread(&enteteFichierPapiers,sizeof(EnteteFichierPapiers),1,fichierPapiers);
    nombrePapiersEnregistres=enteteFichierPapiers.nombrePapiersEnregistres;
    fread(listePapiers,sizeof(Papier),nombrePapiersEnregistres,fichierPapiers);

    fclose(fichierPapiers);
        
}

void ajouterPapier()
{
    FILE *fichierPapiers=NULL;
    EnteteFichierPapiers enteteFichierPapiers;
    int nombreinitialPapiersEnregistres;
    Papier *listePapiers=NULL;

    Papier nouveauPapier={0};

    char nomNouveauPapier[30];
    unsigned char nouveauPapier_R=0;
    char nouveauPapier_R_Char[10]="-1 ";
    unsigned char nouveauPapier_G=0;
    char nouveauPapier_G_Char[10]="-1 ";
    unsigned char nouveauPapier_B=0;
    char nouveauPapier_B_Char[10]="-1 ";
    
    if((fichierPapiers=fopen("profils/papiers.2b3","rb"))==NULL) //Le fichiers n'existe pas
    {
        //----Creation et initialisation du fichier contenant les papiers---
        int nombreMaxPapier=NB_MAX_PAPIER;
        int nombrePapiersParDefaut=7;

        Papier papiersParDefaut[7]={
        {EMPLACEMENT_OCCUPE,"BLANC",{255, 255, 255}},
        {EMPLACEMENT_OCCUPE,"IVOIRE",{254, 247, 226}},
        {EMPLACEMENT_OCCUPE,"GRIS_PERLE",{236, 234, 221}},
        {EMPLACEMENT_OCCUPE,"CANARI",{251, 241, 168}},
        {EMPLACEMENT_OCCUPE,"LAVANDE",{163, 186, 223}},
        {EMPLACEMENT_OCCUPE,"ROSE",{241, 220, 223}},
        {EMPLACEMENT_OCCUPE,"SAUMON",{243,216,204}},
        };

        fichierPapiers=fopen("profils/papiers.2b3","wb"); //Creation du fichier en ecriture
        //----Entete------------
        fwrite(&nombreMaxPapier,sizeof(int),1,fichierPapiers);
        fwrite(&nombrePapiersParDefaut,sizeof(int),1,fichierPapiers);
        //----liste des papiers-----
        fwrite(papiersParDefaut,sizeof(Papier),nombrePapiersParDefaut,fichierPapiers);
        //----fermeture du fichier cree-----
        fclose(fichierPapiers);
        //----ouverture en lecture-------
        fichierPapiers=fopen("profils/papiers.2b3","rb");
    }
    fread(&enteteFichierPapiers,sizeof(EnteteFichierPapiers),1,fichierPapiers);
    nombreinitialPapiersEnregistres=enteteFichierPapiers.nombrePapiersEnregistres;
    listePapiers=malloc_erreurs((nombreinitialPapiersEnregistres+1)*sizeof(Papier));
    fread(listePapiers,sizeof(Papier),nombreinitialPapiersEnregistres,fichierPapiers);
    fclose(fichierPapiers);

    //-----Le logiciel demande les attributs de la couleur à ajouter
    int nouveauNomValide=0;
    int comparaison;
    
    if(nombreinitialPapiersEnregistres<NB_MAX_PAPIER)
    {
        while(nouveauNomValide==0)
        {
            printf("Indiquez le nom du papier en MAJUSCULES\n");
            lire(nomNouveauPapier,30);
            for(int i=0;i<nombreinitialPapiersEnregistres;i++)
            {
                if((comparaison=strcmp(nomNouveauPapier,listePapiers[i].papier.nom))==0)
                {
                    printf("Ce nom est deja utilise\n");
                    break;
                }
                if(comparaison!=0&&i==(nombreinitialPapiersEnregistres-1))
                    nouveauNomValide=1;
            }
        }
        strcpy(nouveauPapier.papier.nom,nomNouveauPapier);
        printf("Indiquez les composantes [R]ed, [G]reen et [B]lue entre 0 et 255\n");
        while(atoi(nouveauPapier_R_Char)<0||atoi(nouveauPapier_R_Char)>255)
        {
            printf("R : ");
            lire(nouveauPapier_R_Char,10);
        }
        nouveauPapier.papier.couleur.r=(unsigned char)atoi(nouveauPapier_R_Char);
        while(atoi(nouveauPapier_G_Char)<0||atoi(nouveauPapier_G_Char)>255)
        {
            printf("G : ");
            lire(nouveauPapier_G_Char,10);
        }
        nouveauPapier.papier.couleur.g=(unsigned char)atoi(nouveauPapier_G_Char);
        while(atoi(nouveauPapier_B_Char)<0||atoi(nouveauPapier_B_Char)>255)
        {
            printf("B : ");
            lire(nouveauPapier_B_Char,10);
        }
        nouveauPapier.papier.couleur.b=(unsigned char)atoi(nouveauPapier_B_Char);

        int papierExistePas=1;
        for(int i=0;i<nombreinitialPapiersEnregistres;i++)
        {
                if(identifierCouleur(nouveauPapier.papier.couleur)==identifierCouleur(listePapiers[i].papier.couleur))
                {
                    printf("Cette nuance existe deja et s'appelle : %s\n",listePapiers[i].papier.nom);
                    sleep(1);
                    papierExistePas=0;
                    break;
                }
        }
        if(papierExistePas)
        {
        listePapiers[nombreinitialPapiersEnregistres]=nouveauPapier;
        listePapiers[nombreinitialPapiersEnregistres].emplacement=EMPLACEMENT_OCCUPE;

        enteteFichierPapiers.nombreMaxiPapiers=NB_MAX_PAPIER;
        enteteFichierPapiers.nombrePapiersEnregistres=nombreinitialPapiersEnregistres+1;

        fichierPapiers=fopen("profils/papiers.2b3","wb");
        fwrite(&enteteFichierPapiers,sizeof(enteteFichierPapiers),1,fichierPapiers);
        fwrite(listePapiers,sizeof(Papier),nombreinitialPapiersEnregistres+1,fichierPapiers);
        fclose(fichierPapiers);
        printf("\nPapier %s ajouté à la liste des papiers disponibles\n",nouveauPapier.papier.nom);
        sleep(1);
        }
        free(listePapiers);
    }else
    {
        printf("Nombre maximum de papiers atteint\nSupprimez-en d'abord\n");
    }

}

void supprimerPapier()
{
    FILE *fichierPapiers=NULL;
    EnteteFichierPapiers enteteFichierPapiers;
    int nombreinitialPapiersEnregistres;
    Papier *listePapiers=NULL;

    char papierSupprimeChar[10]={0};
    int papierSupprime;

    if((fichierPapiers=fopen("profils/papiers.2b3","rb"))==NULL) //Le fichiers n'existe pas
    {
        //----Creation et initialisation du fichier contenant les papiers---
        int nombreMaxPapier=NB_MAX_PAPIER;
        int nombrePapiersParDefaut=7;

        Papier papiersParDefaut[7]={
        {EMPLACEMENT_OCCUPE,"BLANC",{255, 255, 255}},
        {EMPLACEMENT_OCCUPE,"IVOIRE",{254, 247, 226}},
        {EMPLACEMENT_OCCUPE,"GRIS_PERLE",{236, 234, 221}},
        {EMPLACEMENT_OCCUPE,"CANARI",{251, 241, 168}},
        {EMPLACEMENT_OCCUPE,"LAVANDE",{163, 186, 223}},
        {EMPLACEMENT_OCCUPE,"ROSE",{241, 220, 223}},
        {EMPLACEMENT_OCCUPE,"SAUMON",{243,216,204}},
        };

        fichierPapiers=fopen("profils/papiers.2b3","wb"); //Creation du fichier en ecriture
        //----Entete------------
        fwrite(&nombreMaxPapier,sizeof(int),1,fichierPapiers);
        fwrite(&nombrePapiersParDefaut,sizeof(int),1,fichierPapiers);
        //----liste des papiers-----
        fwrite(papiersParDefaut,sizeof(Papier),nombrePapiersParDefaut,fichierPapiers);
        //----fermeture du fichier cree-----
        fclose(fichierPapiers);
        //----ouverture en lecture-------
        fichierPapiers=fopen("profils/papiers.2b3","rb");
    }

    fread(&enteteFichierPapiers,sizeof(EnteteFichierPapiers),1,fichierPapiers);
    nombreinitialPapiersEnregistres=enteteFichierPapiers.nombrePapiersEnregistres;
    listePapiers=malloc_erreurs((nombreinitialPapiersEnregistres+1)*sizeof(Papier));
    fread(listePapiers,sizeof(Papier),nombreinitialPapiersEnregistres,fichierPapiers);
    fclose(fichierPapiers);

    system("clear");
    printLogo();
    printf("Ajout/Suppression de couleurs\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("Indiquez le papier que vous souhaitez supprimer :\n");
    for(int i=1;i<nombreinitialPapiersEnregistres+1;i++){
        printf("%d-%s ",i,listePapiers[i-1].papier.nom);
        printf("[%d,%d,%d]\n",listePapiers[i-1].papier.couleur.r,listePapiers[i-1].papier.couleur.g,listePapiers[i-1].papier.couleur.b);
    }
    printf("%d-Annuler :(\n",nombreinitialPapiersEnregistres+1);
    lire(papierSupprimeChar,10);
    papierSupprime=atoi(papierSupprimeChar);
    while(papierSupprime<1||papierSupprime>nombreinitialPapiersEnregistres+1)
    {
        printf("Ceci n'est pas une entrée valide\n");
        lire(papierSupprimeChar,10);
    }
    if(papierSupprime==nombreinitialPapiersEnregistres+1) //ANNULATION SUPPRESSION
        return;

    listePapiers[papierSupprime-1].emplacement=EMPLACEMENT_LIBRE;
    printf("Papier %s supprime\n",listePapiers[papierSupprime-1].papier.nom);
    sleep(1);
    ordonnerPapiers(listePapiers,nombreinitialPapiersEnregistres);

    enteteFichierPapiers.nombreMaxiPapiers=NB_MAX_PAPIER;
    enteteFichierPapiers.nombrePapiersEnregistres=nombreinitialPapiersEnregistres-1;

    fichierPapiers=fopen("profils/papiers.2b3","wb");
    fwrite(&enteteFichierPapiers,sizeof(enteteFichierPapiers),1,fichierPapiers);
    fwrite(listePapiers,sizeof(Papier),enteteFichierPapiers.nombrePapiersEnregistres,fichierPapiers);
    fclose(fichierPapiers);

}

void ordonnerPapiers(Papier *listePapiers, int nombrePapiersAvantSuppression)
{
    int a=0;
    while(a!=(nombrePapiersAvantSuppression-1))
    {
        a=0;
        for(int i=0;i<nombrePapiersAvantSuppression;i++)
        {
            if(listePapiers[i].emplacement==EMPLACEMENT_LIBRE)
            {
                a=i;
                break;
            }
        }
        listePapiers[a]=listePapiers[a+1];
        listePapiers[a+1].emplacement=EMPLACEMENT_LIBRE;
    }
    
}

