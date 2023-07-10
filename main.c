#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include "structures.h"
#include "main.h"
#include <dirent.h>
#include "conversion.h"
#include "couleurs.h"
#include "recherche.h"
#include "gestion_bibliotheque.h"
#include "papiers.h"
#include <time.h>
#include <sys/stat.h>
#include <setjmp.h>
#include <signal.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#define VERSION "2023.01.25"
#define OS "MacOS"

int niveau_menu=0; //Variable utilisee pour savoir le niveau de menu (pour revenir en arriere)
sigjmp_buf env[3];

void ctrl_z(int sig){
    if(niveau_menu!=0){
        niveau_menu--;
        siglongjmp(env[niveau_menu],1);
    }
}

int main(int argc, char* argv[])
{
    int presenceOption=0;
    int option;
    int sflag=0, dflag=0, aflag=0, eflag=0; //drapeau pour indiquer si des options sont selectionnees
    char nomDossier[100];
    char *nomFichierImage;
    int nombreMagique=0;
    int width=0, height=0, channels=0; //donnees de l'image a traiter
    int taux_encre=10000;

    struct stat fichier;

    signal(SIGTSTP, ctrl_z);

    while((option=getopt(argc,argv,"ase:"))!=-1)
    {
        presenceOption=1;
        switch (option)
        {
            case 'a':
                aflag=1; //On commence le logiciel avec un menu pour rajouter ou supprimer des papiers
            break;
            case 's':
                sflag=1;
            break;
            case 'e':
                eflag=1;
                taux_encre=atoi(optarg);
            break;
            case '?':
            utilisation();
            exit(0);
            break;
        }
    }
    if(presenceOption==0&&argc!=2)//Dans le cas où aucune option n'est selectionnée et qu'il y a trop d'arguments
    {
        utilisation();
        exit(0);
    }
    else if(presenceOption==0) //Dans le cas "./2B3Chromie image.jpg" ou "./2B3Chromie mon_dossier"
    {
        if (stat(argv[1], &fichier) == -1)
        {
        printf("%s : Fichier non trouve\n", argv[1]);
        exit(0);
        }
        if(S_ISREG(fichier.st_mode))
        {
            nomFichierImage=argv[1];
            FILE *dimage=NULL; //descripteur fichier image
            if((dimage=fopen(nomFichierImage,"rb"))!=NULL)
            {
                fread(&nombreMagique,sizeof(int),1,dimage);
                if(nombreMagique!=ISJPEGEXIF && nombreMagique!=ISJPEGJFIF && nombreMagique!=ISJPEGSPIFF
                && nombreMagique!=ISJPEGCANON && nombreMagique!=ISJPEGSAMSUNG)
                {
                    printf("%s : Pas une image .jpg habituelle\n",nomFichierImage);
                    exit(0);
                }
                fclose(dimage);
            }
        }else if(S_ISDIR(fichier.st_mode))
        {
            dflag=1;
            strcpy(nomDossier,argv[1]);
            printf("Traitement du dossier %s\n",nomDossier);
            sleep(1);
        }
        else
        {
            printf("%s : Fichier non trouve\n", nomFichierImage);
            exit(0);
        }
    }
    else if(presenceOption==1)
    {
        if (stat(argv[optind], &fichier) == -1)
        {
        printf("%s : Fichier non trouve\n", argv[1]);
        exit(0);
        }
        if(S_ISREG(fichier.st_mode))
        {
        nomFichierImage=argv[optind];
        FILE *dimage=NULL; //descripteur fichier image
        if((dimage=fopen(nomFichierImage,"rb"))!=NULL)
        {
            fread(&nombreMagique,sizeof(int),1,dimage);
            if(nombreMagique!=ISJPEGEXIF && nombreMagique!=ISJPEGJFIF && nombreMagique!=ISJPEGSPIFF
                && nombreMagique!=ISJPEGCANON && nombreMagique!=ISJPEGSAMSUNG)
            {
                printf("%s : Pas une image .jpg habituelle\n",nomFichierImage);
                exit(0);
            }
            fclose(dimage);
        }
        }else if(S_ISDIR(fichier.st_mode))
        {
            dflag=1;
            strcpy(nomDossier,argv[optind]);
            printf("Traitement du dossier %s\n",nomDossier);
            sleep(1);
        }
        else
        {
            printf("%s : Le fichier n'est pas valide\n", nomFichierImage);
            exit(0);
        }

    }
    else
    {
        utilisation();
        exit(0);
    }
 
    CouleurDImpression couleur1,couleur2,couleur3,couleur4,couleurPapier;
    int indiceCouleur1, indiceCouleur2, indiceCouleur3,indiceCouleur4;
    //-----------------------------------------------------

    //-------Menu optionnel d'ajout de couleurs d'impression ou de papier------
    int sortieMenu=0;
    char choixChar[10];
    int choix;

    if(aflag==1)
    {
        while(sortieMenu==0)
        {
            system("clear");
            printLogo();
            printf("Ajout/Suppression de couleurs\n");
            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("1-Lister les papiers\n");
            printf("2-Lister les couleurs d'impression\n");
            printf("3-Ajouter un papier\n");
            printf("4-Ajouter une couleur d'impression\n");
            printf("5-Supprimer un papier\n");
            printf("6-Supprimer une couleur d'impression\n");
            printf("7-Continuer vers la decompositon\n");
            printf("8-Quitter\n\n");
            printf("Choix : ");

            lire(choixChar,10);
            choix=atoi(choixChar);
            while(choix<1||choix>8)
            {
                printf("Ceci n'est pas une entrée valide\n");
                lire(choixChar,10);
                choix=atoi(choixChar);
            }
            switch (choix)
            {
                case 1:
                {
                    int nombrePapiersDisponibles=lectureEnteteFichierPapiers();
                    Papier *listePapiers=malloc_erreurs(nombrePapiersDisponibles*sizeof(Papier));
                    ouvrirFichierPapiers(nombrePapiersDisponibles,listePapiers);
                    system("clear");
                    printLogo();
                    printf("Ajout/Suppression de couleurs\n");
                    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("Liste des papiers disponibles\n");
                    for(int i=1;i<nombrePapiersDisponibles+1;i++){
                        printf("%d-%s ",i,listePapiers[i-1].papier.nom);
                        printf("[%d,%d,%d]\n",listePapiers[i-1].papier.couleur.r,listePapiers[i-1].papier.couleur.g,listePapiers[i-1].papier.couleur.b);
                    }
                    free(listePapiers);
                    printf("\nAppuyez sur ENTREE pour continuer\n");
                    getchar();
                }
                break;
                case 2:
                {
                    int nombreCouleursDisponibles=lectureEnteteFichierCouleurs();
                    Couleur *listeCouleurs=malloc_erreurs(nombreCouleursDisponibles*sizeof(Couleur));
                    ouvrirFichierCouleurs(nombreCouleursDisponibles,listeCouleurs);
                    system("clear");
                    printLogo();
                    printf("Ajout/Suppression de couleurs\n");
                    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("Liste des couleurs d'impression disponibles\n");
                    for(int i=1;i<nombreCouleursDisponibles+1;i++){
                        printf("%d-%s ",i,listeCouleurs[i-1].couleur.nom);
                        printf("[%d,%d,%d]\n",listeCouleurs[i-1].couleur.couleur.r,listeCouleurs[i-1].couleur.couleur.g,listeCouleurs[i-1].couleur.couleur.b);
                    }
                    free(listeCouleurs);
                    printf("\nAppuyez sur ENTREE pour continuer\n");
                    getchar();
                }
                break;
                case 3:
                    ajouterPapier();
                break;
                case 4:
                    ajouterCouleur();
                break;
                case 5:
                    supprimerPapier();
                break;
                case 6:
                    supprimerCouleur();
                break;
                case 7:
                    sortieMenu=1;
                break;
                case 8:
                    exit(1);
                break;
            }


        }
    }

    //------- Menu du programme ----------------------------
    //----1-Selection du nombre de couleurs a imprimer
    sigsetjmp(env[niveau_menu],1);
    system("clear");
    printLogo();
    printf("Decomposition en couches de couleur\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    printf("Indiquez le nombre de couleurs d'impression (1/2/3/4)\n");
    printf("Choix : ");
    char nombreDeCouleursChar[10];
    int nombreDeCouleursInt=0;
    while(nombreDeCouleursInt<1||nombreDeCouleursInt>4)
    {
        lire(nombreDeCouleursChar,10);
        nombreDeCouleursInt=atoi(nombreDeCouleursChar);
        if(nombreDeCouleursInt<1||nombreDeCouleursInt>4)
        {
            printf("Ceci n'est pas une entrée valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rChoix : ");
            fflush(stdout);
        }
        
    }
    //-----1-Selection de la couleur du papier sur lequel on imprime
    niveau_menu++; //Menu suivant
    sigsetjmp(env[niveau_menu],1);
    system("clear");
    printLogo();
    printf("Decomposition en couches de couleur\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("Nombre de couleurs : %d\n",nombreDeCouleursInt);
    char numeroPapierChoisiChar[10];
    int numeroPapierChoisiInt;
    int nombrePapiersDisponibles=lectureEnteteFichierPapiers();
    Papier *listePapiers=malloc_erreurs(nombrePapiersDisponibles*sizeof(Papier));
    ouvrirFichierPapiers(nombrePapiersDisponibles,listePapiers);
    printf("Indiquez la couleur du papier sur lequel vous effectuez l'impression\n");
    for(int i=1;i<nombrePapiersDisponibles+1;i++){
        printf("%d-%s\n",i,listePapiers[i-1].papier.nom);
    }
    printf("Choix : ");
    lire(numeroPapierChoisiChar,10);
    numeroPapierChoisiInt=atoi(numeroPapierChoisiChar);
    while(numeroPapierChoisiInt<1||numeroPapierChoisiInt>nombrePapiersDisponibles)
        {
            printf("Ceci n'est pas une entrée valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rChoix : ");
            fflush(stdout);
            lire(numeroPapierChoisiChar,10);
            numeroPapierChoisiInt=atoi(numeroPapierChoisiChar);
        }
    couleurPapier=listePapiers[numeroPapierChoisiInt-1].papier;
    system("clear");
    printLogo();
    printf("Decomposition en couches de couleur\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("Nombre de couleurs : %d\n",nombreDeCouleursInt);
    printf("Papier : %s\n", couleurPapier.nom);

    free(listePapiers);

    //-----3-Selection des couleurs d'impression
    niveau_menu++; //Menu suivant
    sigsetjmp(env[niveau_menu],1);
    char numeroCouleurChoisieChar[10];
    int numeroCouleurChoisieInt=0;
    int nombreCouleursDisponibles=lectureEnteteFichierCouleurs();
    Couleur *listeCouleurs=malloc_erreurs(nombreCouleursDisponibles*sizeof(Couleur));
    ouvrirFichierCouleurs(nombreCouleursDisponibles,listeCouleurs);
    if (nombreDeCouleursInt==1)
    {
        printf("Choisir la couleur en indiquant son numero\n");
        for(int i=1;i<nombreCouleursDisponibles+1;i++){
            printf("%d-%s\n",i,listeCouleurs[i-1].couleur.nom);
        }
        printf("Couleur 1 ? ");
        lire(numeroCouleurChoisieChar,10);
        numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        while(numeroCouleurChoisieInt<1||numeroCouleurChoisieInt>nombreCouleursDisponibles)
        {
            printf("Ceci n'est pas une entree valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rCouleur 1 ? ");
            fflush(stdout);
            lire(numeroCouleurChoisieChar,10);
            numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        }
        indiceCouleur1=atoi(numeroCouleurChoisieChar);
        couleur1=listeCouleurs[indiceCouleur1-1].couleur;
        printf("Couleur 1 : %s\n\n",couleur1.nom);
    }
    else if(nombreDeCouleursInt==2){
        printf("Choisir les 2 couleurs en indiquant leur numero\n");
        for(int i=1;i<nombreCouleursDisponibles+1;i++){
            printf("%d-%s\n",i,listeCouleurs[i-1].couleur.nom);
        }
        printf("Couleur 1 ? ");
        lire(numeroCouleurChoisieChar,10);
        numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        while(numeroCouleurChoisieInt<1||numeroCouleurChoisieInt>nombreCouleursDisponibles)
        {
            printf("Ceci n'est pas une entree valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rCouleur 1 ? ");
            fflush(stdout);
            lire(numeroCouleurChoisieChar,10);
            numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        }
        indiceCouleur1=atoi(numeroCouleurChoisieChar);
        couleur1=listeCouleurs[indiceCouleur1-1].couleur;
        printf("Couleur 1 : %s\n\n",couleur1.nom);
        printf("Couleur 2 ? ");
        lire(numeroCouleurChoisieChar,10);
        numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        while(numeroCouleurChoisieInt<1||numeroCouleurChoisieInt>nombreCouleursDisponibles)
        {
            printf("Ceci n'est pas une entree valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rCouleur 2 ? ");
            fflush(stdout);
            lire(numeroCouleurChoisieChar,10);
            numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        }
        indiceCouleur2=atoi(numeroCouleurChoisieChar);
        couleur2=listeCouleurs[indiceCouleur2-1].couleur;
        printf("Couleur 2 : %s\n\n",couleur2.nom);

        reordonnerProfil2CouleursV2(&couleur1,&couleur2);

    }
    else if(nombreDeCouleursInt==3){
        printf("Choisir les 3 couleurs en indiquant leur numero\n");
        for(int i=1;i<nombreCouleursDisponibles+1;i++){
            printf("%d-%s\n",i,listeCouleurs[i-1].couleur.nom);
        }
        printf("Couleur 1 ? ");
        lire(numeroCouleurChoisieChar,10);
        numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        while(numeroCouleurChoisieInt<1||numeroCouleurChoisieInt>nombreCouleursDisponibles)
        {
            printf("Ceci n'est pas une entree valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rCouleur 1 ? ");
            fflush(stdout);
            lire(numeroCouleurChoisieChar,10);
            numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        }
        indiceCouleur1=atoi(numeroCouleurChoisieChar);
        couleur1=listeCouleurs[indiceCouleur1-1].couleur;
        printf("Couleur 1 : %s\n\n",couleur1.nom);
        printf("Couleur 2 ? ");
        lire(numeroCouleurChoisieChar,10);
        numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        while(numeroCouleurChoisieInt<1||numeroCouleurChoisieInt>nombreCouleursDisponibles)
        {
            printf("Ceci n'est pas une entree valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rCouleur 2 ? ");
            fflush(stdout);
            lire(numeroCouleurChoisieChar,10);
            numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        }
        indiceCouleur2=atoi(numeroCouleurChoisieChar);
        couleur2=listeCouleurs[indiceCouleur2-1].couleur;
        printf("Couleur 2 : %s\n\n",couleur2.nom);
        printf("Couleur 3 ? ");
        lire(numeroCouleurChoisieChar,10);
        numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        while(numeroCouleurChoisieInt<1||numeroCouleurChoisieInt>nombreCouleursDisponibles)
        {
            printf("Ceci n'est pas une entree valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rCouleur 3 ? ");
            fflush(stdout);
            lire(numeroCouleurChoisieChar,10);
            numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        }
        indiceCouleur3=atoi(numeroCouleurChoisieChar);
        couleur3=listeCouleurs[indiceCouleur3-1].couleur;
        printf("Couleur 3 : %s\n\n",couleur3.nom);

        reordonnerProfil3CouleursV2(&couleur1,&couleur2,&couleur3);
    }
    else
    {
        printf("Choisir les 4 couleurs en indiquant leur numero\n");
        for(int i=1;i<nombreCouleursDisponibles+1;i++){
            printf("%d-%s\n",i,listeCouleurs[i-1].couleur.nom);
        }
        printf("Couleur 1 ? ");
        lire(numeroCouleurChoisieChar,10);
        numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        while(numeroCouleurChoisieInt<1||numeroCouleurChoisieInt>nombreCouleursDisponibles)
        {
            printf("Ceci n'est pas une entree valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rCouleur 1 ? ");
            fflush(stdout);
            lire(numeroCouleurChoisieChar,10);
            numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        }
        indiceCouleur1=atoi(numeroCouleurChoisieChar);
        couleur1=listeCouleurs[indiceCouleur1-1].couleur;
        printf("Couleur 1 : %s\n\n",couleur1.nom);
        printf("Couleur 2 ? ");
        lire(numeroCouleurChoisieChar,10);
        numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        while(numeroCouleurChoisieInt<1||numeroCouleurChoisieInt>nombreCouleursDisponibles)
        {
            printf("Ceci n'est pas une entree valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rCouleur 2 ? ");
            fflush(stdout);
            lire(numeroCouleurChoisieChar,10);
            numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        }
        indiceCouleur2=atoi(numeroCouleurChoisieChar);
        couleur2=listeCouleurs[indiceCouleur2-1].couleur;
        printf("Couleur 2 : %s\n\n",couleur2.nom);
        printf("Couleur 3 ? ");
        lire(numeroCouleurChoisieChar,10);
        numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        while(numeroCouleurChoisieInt<1||numeroCouleurChoisieInt>nombreCouleursDisponibles)
        {
            printf("Ceci n'est pas une entree valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rCouleur 3 ? ");
            fflush(stdout);
            lire(numeroCouleurChoisieChar,10);
            numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        }
        indiceCouleur3=atoi(numeroCouleurChoisieChar);
        couleur3=listeCouleurs[indiceCouleur3-1].couleur;
        printf("Couleur 3 : %s\n\n",couleur3.nom);
        printf("Couleur 4 ? ");
        lire(numeroCouleurChoisieChar,10);
        numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        while(numeroCouleurChoisieInt<1||numeroCouleurChoisieInt>nombreCouleursDisponibles)
        {
            printf("Ceci n'est pas une entree valide");
            fflush(stdout);
            sleep(1);
            printf("\r                                ");
            fflush(stdout);
            printf("\rCouleur 4 ? ");
            fflush(stdout);
            lire(numeroCouleurChoisieChar,10);
            numeroCouleurChoisieInt=atoi(numeroCouleurChoisieChar);
        }
        indiceCouleur4=atoi(numeroCouleurChoisieChar);
        couleur4=listeCouleurs[indiceCouleur4-1].couleur;
        printf("Couleur 4 : %s\n\n",couleur4.nom);

        reordonnerProfil4CouleursV2(&couleur1,&couleur2,&couleur3,&couleur4);

    }

    //Création du dossier ./Images_Traitees s'il n'existe pas
    DIR *dossierImagesTraitees;
    if((dossierImagesTraitees=opendir("Images_Traitees"))==NULL)
    {
        mkdir("Images_Traitees",0700);
        printf("Creation du dossier \"Images_Traitees\"\n");
    }
    else closedir(dossierImagesTraitees);

    //------------------------------------------------------

    
    
    int i=0;


    RgbColor *nuancierRgb=NULL; //Nuancier des couleurs obtenables en riso
    RgbColor *imageSimulee=NULL; //Image qui va simuler la sortie riso


    switch (nombreDeCouleursInt)
    {
        case 1: //MONOCHROMIE
        {
            //CREATION DU PROFIL & INITIALISATION DES VARIABLES DE CALCUL DES FICHIERS D'IMPRESSION
            ElementBibliotheque1D *bibliotheque1D=malloc_erreurs(256*256*256*sizeof(ElementBibliotheque1D));
            ComposantesNuance1D *profil1D=malloc_erreurs(16*16*16*sizeof(ComposantesNuance1D));
            EnteteFichierProfil *entete=malloc_erreurs(sizeof(EnteteFichierProfil));
            unsigned char *img=NULL; //pointeur vers l'image
            char x[400]; //variable tampon pour stocker les noms et creer les fichiers
            char ouiNon[2]; //Utiliser pour la validation utilisateur
            struct stat fichier;

            //----------Initialisation de la bibliotheque à zero------
            for(i=0;i<256*256*256;i++)
            {
                *(char*)((ElementBibliotheque1D*)bibliotheque1D+i)=0;
            }
            //---------------------------------------------------

            //LE PROFIL EST TOUJOURS CREE EN PREMIER MEME S'IL N'EST PAS UTILISE
            if(chargerProfil1D(couleurPapier,couleur1,profil1D,entete)==0) //Rechargement du profil s'il existe ou creation si ce n'est pas le cas
            {
                printf("Le profil %s sur papier %s n'existe pas \nVoulez-vous le creer ?[O-oui/N-non, quitter le programme]\n", couleur1.nom, couleurPapier.nom);
                //------Creation du nauncier des couleurs imprimables avec le jeu de couleurs choisies-----
                nuancierRgb=malloc_erreurs(RESOLUTION*sizeof(RgbColor));
                creationNuancier1D(couleurPapier.couleur,&couleur1.couleur,nuancierRgb);
                
                //------Estimation du temps de calcul d'un nouveau profil 2 couleurs-----------------------
                int *tableauDesDifferences=malloc_erreurs(RESOLUTION*sizeof(int));
                estimationTempsCalul(1, nuancierRgb, tableauDesDifferences);


                lire(ouiNon,2); //----Est ce que l'utilisateur veut ou non creer un nouveau profil ?
                while((ouiNon[0]!='O')&&(ouiNon[0]!='N'))
                {
                    printf("Le profil n'existe pas \nVoulez-vous le creer ?[O/N]\n");
                    lire(ouiNon,2);
                }
                if (ouiNon[0]=='N') exit(0); //Le programme s'arrete si l'on choisit de ne pas creer le profil
                
                creerProfil1D(couleurPapier,couleur1,profil1D,entete,nuancierRgb,tableauDesDifferences);
                free(nuancierRgb);
                free(tableauDesDifferences);
            }


            //TRAITEMENT D'UN REPERTOIRE D'IMAGES
            if(dflag==1){
                //DIR *ddossier=NULL;
                struct dirent *contenu;
                DIR *ddossier=opendir(nomDossier); //descripteur de dossier
                int nombreMagique; //permet d'identifier un fichier jpeg
                
                

                //CREATION DES DOSSIERS POUR STOCKER LES FICHIERS CALCULES
                sprintf(x,"%s/Images_Traitees-%s_papier-%s",nomDossier,couleur1.nom,couleurPapier.nom);
                mkdir(x,0700);
                if(sflag!=1)//si -s est positionné on ne fait que la simulation
                {
                    sprintf(x,"%s/Images_Traitees-%s_papier-%s/1-%s",nomDossier,couleur1.nom,couleurPapier.nom,couleur1.nom); //Dossier couleur 1
                    mkdir(x,0700);
                }
                sprintf(x,"%s/Images_Traitees-%s_papier-%s/SIMULATIONS",nomDossier,couleur1.nom,couleurPapier.nom); //Dossier simualtions
                mkdir(x,0700);

                while((contenu=readdir(ddossier))!=NULL)
                {
                    strcpy(x,nomDossier);
                    strcat(x,"/");
                    FILE *dimage=fopen(strcat(x,contenu->d_name),"rb");
                    stat(x,&fichier);
                    fread(&nombreMagique,sizeof(int),1,dimage);
                    fclose(dimage);
                    if((nombreMagique==ISJPEGEXIF||nombreMagique==ISJPEGJFIF)&&(S_ISDIR(fichier.st_mode)!=1)) //est-ce bien un JPEG et PAS un dossier ?
                    {
                        img=stbi_load(x,&width,&height,&channels,0);

                        //-------------creation des images en niveau de gris destinees a la riso-------

                        unsigned char *imageComposante1=malloc_erreurs(width*height*sizeof(char));

                        calculerFichiersImpression1D(img,width,height,profil1D,bibliotheque1D,taux_encre);
                        printf("image %s traitee ",contenu->d_name);
                        fflush(stdout);

                        for(i=0;i<width*height;i++)
                        {
                            imageComposante1[i]=bibliotheque1D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante1;
                        }

                        //-------------creation de l'image simulee de l'impression-----------------------

                        imageSimulee=simulerImpression1D(imageComposante1,couleurPapier.couleur,couleur1.couleur,width*height);

                        //ENREGISTREMENT DES IMAGES
                        if(sflag!=1)//si -s est positionné on ne fait que la simulation
                        {    //Couleur1
                        sprintf(x,"%s/Images_Traitees-%s_papier-%s/1-%s/%s",nomDossier,couleur1.nom,couleurPapier.nom,couleur1.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,1,imageComposante1,100);
                        }
                            //Simulation
                        sprintf(x,"%s/Images_Traitees-%s_papier-%s/SIMULATIONS/%s",nomDossier,couleur1.nom,couleurPapier.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,3,imageSimulee,80);
                        
                        
                        free(imageComposante1);
                        free(imageSimulee);

                        printf("et enregistree\n");
                        

                        stbi_image_free(img);
                    }
                    
                
                }
                printf("\nImages enregistrees dans le dossier : %s/Images_Traitees-%s_papier-%s\n\n",nomDossier,couleur1.nom,couleurPapier.nom);
                free(bibliotheque1D);
                free(profil1D);
                free(entete);

            }
            else //cas d'une image seule
            {
                //-------------Chargement de l'image------------------------
                img=stbi_load(nomFichierImage,&width,&height,&channels,0);
                //-------------creation des images en niveau de gris destinees a la riso-------

                unsigned char *imageComposante1=malloc_erreurs(width*height*sizeof(char));

                calculerFichiersImpression1D(img,width,height,profil1D,bibliotheque1D,taux_encre);

                for(i=0;i<width*height;i++)
                {
                    imageComposante1[i]=bibliotheque1D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante1;
                }

                //-------------creation de l'image simulee de l'impression-----------------------

                imageSimulee=simulerImpression1D(imageComposante1,couleurPapier.couleur,couleur1.couleur,width*height);

                //--------------------enregistrement des fichiers (images et maj bibliotheque)---------
                
                
                sprintf(x,"Images_Traitees/%s-traitee-%s_papier-%s/",nomFichierImage,couleur1.nom,couleurPapier.nom);
                mkdir(x,0700);

                if(sflag!=1)
                {
                    sprintf(x,"Images_Traitees/%s-traitee-%s_papier-%s/1-%s_%s",nomFichierImage,couleur1.nom,couleurPapier.nom,couleur1.nom,nomFichierImage);
                    stbi_write_jpg(x,width,height,1,imageComposante1,100);
                }

                sprintf(x,"Images_Traitees/%s-traitee-%s_papier-%s/SIMULATION-%s_papier-%s_%s",nomFichierImage,couleur1.nom,couleurPapier.nom,couleur1.nom,couleurPapier.nom,nomFichierImage);
                stbi_write_jpg(x,width,height,3,imageSimulee,80);
                printf("Images enregistrees dans le dossier : Images_Traitees/%s-traitee-%s_papier-%s\n\n",nomFichierImage,couleur1.nom,couleurPapier.nom);
                


                stbi_image_free(img);
                free(bibliotheque1D);
                free(profil1D);
                free(entete);
                free(imageComposante1);
                free(imageSimulee); 
            }

        break;
        }
        case 2: //BICHROMIE
        {
            //CREATION DU PROFIL & INITIALISATION DES VARIABLES DE CALCUL DES FICHIERS D'IMPRESSION
            ElementBibliotheque2D *bibliotheque2D=malloc_erreurs(256*256*256*sizeof(ElementBibliotheque2D));
            ComposantesNuance2D *profil2D=malloc_erreurs(16*16*16*sizeof(ComposantesNuance2D));
            EnteteFichierProfil *entete=malloc_erreurs(sizeof(EnteteFichierProfil));
            unsigned char *img=NULL; //pointeur vers l'image
            char x[400]; //variable tampon pour stocker les noms et creer les fichiers
            char ouiNon[2]; //Utiliser pour la validation utilisateur
            struct stat fichier;

            //----------Initialisation de la bibliotheque à zero------
            for(i=0;i<256*256*256;i++)
            {
                *(char*)((ElementBibliotheque2D*)bibliotheque2D+i)=0;
            }
            //---------------------------------------------------

            //LE PROFIL EST TOUJOURS CREE EN PREMIER MEME S'IL N'EST PAS UTILISE
            if(chargerProfil2D(couleurPapier,couleur1,couleur2,profil2D,entete)==0) //Rechargement du profil s'il existe ou creation si ce n'est pas le cas
            {
                printf("Le profil %s + %s sur papier %s n'existe pas \nVoulez-vous le creer ?[O-oui/N-non, quitter le programme]\n", couleur1.nom, couleur2.nom, couleurPapier.nom);
                //------Creation du nauncier des couleurs imprimables avec le jeu de couleurs choisies-----
                nuancierRgb=malloc_erreurs(RESOLUTION*RESOLUTION*sizeof(RgbColor));
                creationNuancier2D(couleurPapier.couleur,&couleur1.couleur,&couleur2.couleur,nuancierRgb);
                
                //------Estimation du temps de calcul d'un nouveau profil 2 couleurs-----------------------
                int *tableauDesDifferences=malloc_erreurs(RESOLUTION*RESOLUTION*sizeof(int));
                estimationTempsCalul(2, nuancierRgb, tableauDesDifferences);


                lire(ouiNon,2); //----Est ce que l'utilisateur veut ou non creer un nouveau profil ?
                while((ouiNon[0]!='O')&&(ouiNon[0]!='N'))
                {
                    printf("Le profil n'existe pas \nVoulez-vous le creer ?[O/N]\n");
                    lire(ouiNon,2);
                }
                if (ouiNon[0]=='N') exit(0); //Le programme s'arrete si l'on choisit de ne pas creer le profil
                
                creerProfil2D(couleurPapier,couleur1,couleur2,profil2D,entete,nuancierRgb,tableauDesDifferences);
                free(nuancierRgb);
                free(tableauDesDifferences);
            }


            //TRAITEMENT D'UN REPERTOIRE D'IMAGES
            if(dflag==1){
                //DIR *ddossier=NULL;
                struct dirent *contenu;
                DIR *ddossier=opendir(nomDossier); //descripteur de dossier
                int nombreMagique; //permet d'identifier un fichier jpeg
                
                

                //CREATION DES DOSSIERS POUR STOCKER LES FICHIERS CALCULES
                sprintf(x,"%s/Images_Traitees-%s-%s_papier-%s",nomDossier,couleur1.nom,couleur2.nom,couleurPapier.nom);
                mkdir(x,0700);
                if(sflag!=1)//si -s est positionné on ne fait que la simulation
                {
                    sprintf(x,"%s/Images_Traitees-%s-%s_papier-%s/1-%s",nomDossier,couleur1.nom,couleur2.nom,couleurPapier.nom,couleur1.nom); //Dossier couleur 1
                    mkdir(x,0700);
                    sprintf(x,"%s/Images_Traitees-%s-%s_papier-%s/2-%s",nomDossier,couleur1.nom,couleur2.nom,couleurPapier.nom,couleur2.nom); //Dossier couleur 2
                    mkdir(x,0700);
                }
                sprintf(x,"%s/Images_Traitees-%s-%s_papier-%s/SIMULATIONS",nomDossier,couleur1.nom,couleur2.nom,couleurPapier.nom); //Dossier simualtions
                mkdir(x,0700);

                while((contenu=readdir(ddossier))!=NULL)
                {
                    strcpy(x,nomDossier);
                    strcat(x,"/");
                    FILE *dimage=fopen(strcat(x,contenu->d_name),"rb");
                    stat(x,&fichier);
                    fread(&nombreMagique,sizeof(int),1,dimage);
                    fclose(dimage);
                    if((nombreMagique==ISJPEGEXIF||nombreMagique==ISJPEGJFIF)&&(S_ISDIR(fichier.st_mode)!=1)) //est-ce bien un JPEG ?
                    {
                        img=stbi_load(x,&width,&height,&channels,0);

                        //-------------creation des images en niveau de gris destinees a la riso-------

                        unsigned char *imageComposante1=malloc_erreurs(width*height*sizeof(char));
                        unsigned char *imageComposante2=malloc_erreurs(width*height*sizeof(char));

                        calculerFichiersImpression2D(img,width,height,profil2D,bibliotheque2D,taux_encre);
                        printf("image %s traitee ",contenu->d_name);
                        fflush(stdout);

                        for(i=0;i<width*height;i++)
                        {
                            imageComposante1[i]=bibliotheque2D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante1;
                            imageComposante2[i]=bibliotheque2D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante2;
                        }

                        //-------------creation de l'image simulee de l'impression-----------------------

                        imageSimulee=simulerImpression2D(imageComposante1,imageComposante2,couleurPapier.couleur,couleur1.couleur,couleur2.couleur,width*height);

                        //ENREGISTREMENT DES IMAGES
                        if(sflag!=1)//si -s est positionné on ne fait que la simulation
                        {    //Couleur1
                        sprintf(x,"%s/Images_Traitees-%s-%s_papier-%s/1-%s/%s",nomDossier,couleur1.nom,couleur2.nom,couleurPapier.nom,couleur1.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,1,imageComposante1,100);
                        
                            //Couleur2
                        sprintf(x,"%s/Images_Traitees-%s-%s_papier-%s/2-%s/%s",nomDossier,couleur1.nom,couleur2.nom,couleurPapier.nom,couleur2.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,1,imageComposante2,100);
                        }
                            //Simulation
                        sprintf(x,"%s/Images_Traitees-%s-%s_papier-%s/SIMULATIONS/%s",nomDossier,couleur1.nom,couleur2.nom,couleurPapier.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,3,imageSimulee,80);
                        
                        
                        free(imageComposante1);
                        free(imageComposante2);
                        free(imageSimulee);

                        printf("et enregistree\n");
                        

                        stbi_image_free(img);
                    }
                
                }
                printf("\nImages enregistrees dans le dossier : %s/Images_Traitees-%s-%s_papier-%s\n\n",nomDossier,couleur1.nom,couleur2.nom,couleurPapier.nom);
                free(bibliotheque2D);
                free(profil2D);
                free(entete);

            }
            else //cas d'une image seule
            {
                //-------------Chargement de l'image------------------------
                img=stbi_load(nomFichierImage,&width,&height,&channels,0);
                //-------------creation des images en niveau de gris destinees a la riso-------

                unsigned char *imageComposante1=malloc_erreurs(width*height*sizeof(char));
                unsigned char *imageComposante2=malloc_erreurs(width*height*sizeof(char));

                calculerFichiersImpression2D(img,width,height,profil2D,bibliotheque2D,taux_encre);

                for(i=0;i<width*height;i++)
                {
                    imageComposante1[i]=bibliotheque2D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante1;
                    imageComposante2[i]=bibliotheque2D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante2;
                }

                //-------------creation de l'image simulee de l'impression-----------------------

                imageSimulee=simulerImpression2D(imageComposante1,imageComposante2,couleurPapier.couleur,couleur1.couleur,couleur2.couleur,width*height);

                //--------------------enregistrement des fichiers (images et maj bibliotheque)---------
                
                
                sprintf(x,"Images_Traitees/%s-traitee-%s-%s_papier-%s/",nomFichierImage,couleur1.nom,couleur2.nom,couleurPapier.nom);
                mkdir(x,0700);

                if(sflag!=1)
                {
                    sprintf(x,"Images_Traitees/%s-traitee-%s-%s_papier-%s/1-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleurPapier.nom,couleur1.nom,nomFichierImage);
                    stbi_write_jpg(x,width,height,1,imageComposante1,100);
                    sprintf(x,"Images_Traitees/%s-traitee-%s-%s_papier-%s/2-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleurPapier.nom,couleur2.nom,nomFichierImage);
                    stbi_write_jpg(x,width,height,1,imageComposante2,100);
                }

                sprintf(x,"Images_Traitees/%s-traitee-%s-%s_papier-%s/SIMULATION-%s-%s_papier-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleurPapier.nom,couleur1.nom,couleur2.nom,couleurPapier.nom,nomFichierImage);
                stbi_write_jpg(x,width,height,3,imageSimulee,80);
                printf("Images enregistrees dans le dossier : Images_Traitees/%s-traitee-%s-%s_papier-%s\n\n",nomFichierImage,couleur1.nom,couleur2.nom,couleurPapier.nom);
                


                stbi_image_free(img);
                free(bibliotheque2D);
                free(profil2D);
                free(entete);
                free(imageComposante1);
                free(imageComposante2);
                free(imageSimulee); 
            }

        break;
    }
        case 3: //TRICHROMIE
        {
        //CREATION DU PROFIL & INITIALISATION DES VARIABLES DE CALCUL DES FICHIERS D'IMPRESSION    
        ElementBibliotheque3D *bibliotheque3D=malloc_erreurs(256*256*256*sizeof(ElementBibliotheque3D));
        ComposantesNuance3D *profil3D=malloc_erreurs(16*16*16*sizeof(ComposantesNuance3D));
        EnteteFichierProfil *entete=malloc_erreurs(sizeof(EnteteFichierProfil));
        unsigned char *img=NULL; //pointeur vers l'image
        char x[400]; //variable tampon pour stocker les noms et creer les fichiers
        char ouiNon[2]; //Utiliser pour la validation utilisateur
        struct stat fichier;
   
        //----------------------Initialisation de la bibliotheque--------------
        for(i=0;i<256*256*256;i++)
        {
            *(char*)((ElementBibliotheque3D*)bibliotheque3D+i)=0; //Mise a 0 des indicateurs de couleur déja calculee
        }
        //------------------------------------------
        
        if(chargerProfil3D(couleurPapier,couleur1,couleur2, couleur3,profil3D,entete)==0) //Rechargement du profil s'il existe ou creation si ce n'est pas le cas
        {
            printf("Le profil %s + %s + %s sur papier %s n'existe pas \nVoulez-vous le creer ?[O-oui/N-non, quitter le programme]\n", couleur1.nom, couleur2.nom, couleur3.nom, couleurPapier.nom);
            
            //------Creation du nauncier des couleurs imprimables avec le jeu de couleurs choisies-----
            nuancierRgb=malloc_erreurs(RESOLUTION*RESOLUTION*RESOLUTION*sizeof(RgbColor));
            creationNuancier3D(couleurPapier.couleur,&couleur1.couleur,&couleur2.couleur,&couleur3.couleur,nuancierRgb);
            
            //------Estimation du temps de calcul d'un nouveau profil 2 couleurs-----------------------
            int *tableauDesDifferences=malloc_erreurs(RESOLUTION*RESOLUTION*RESOLUTION*sizeof(int));
            estimationTempsCalul(3, nuancierRgb, tableauDesDifferences);

            lire(ouiNon,2);
            while((ouiNon[0]!='O')&&(ouiNon[0]!='N'))
            {
                printf("Le profil n'existe pas \nVoulez-vous le creer ?[O/N]\n");
                lire(ouiNon,2);
            }
            if (ouiNon[0]=='N') exit(0); //Le programme s'arrete si l'on choisit de ne pas creer le profil
            creerProfil3D(couleurPapier,couleur1,couleur2, couleur3,profil3D,entete,nuancierRgb,tableauDesDifferences);
            
            free(nuancierRgb);
            free(tableauDesDifferences);
        }

        //TRAITEMENT D'UN REPERTOIRE D'IMAGES
            if(dflag==1){
                //DIR *ddossier=NULL;
                struct dirent *contenu;
                DIR *ddossier=opendir(nomDossier); //descripteur de dossier
                int nombreMagique; //permet d'identifier un fichier jpeg
                
                

                //CREATION DES DOSSIERS POUR STOCKER LES FICHIERS CALCULES
                sprintf(x,"%s/Images_Traitees-%s-%s-%s_papier-%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom);
                mkdir(x,0700);
                if(sflag!=1)//si -s est positionné on ne fait que la simulation
                {
                    sprintf(x,"%s/Images_Traitees-%s-%s-%s_papier-%s/1-%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,couleur1.nom); //Dossier couleur 1
                    mkdir(x,0700);
                    sprintf(x,"%s/Images_Traitees-%s-%s-%s_papier-%s/2-%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,couleur2.nom); //Dossier couleur 2
                    mkdir(x,0700);
                    sprintf(x,"%s/Images_Traitees-%s-%s-%s_papier-%s/3-%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,couleur3.nom); //Dossier couleur 2
                    mkdir(x,0700);
                }
                sprintf(x,"%s/Images_Traitees-%s-%s-%s_papier-%s/SIMULATIONS",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom); //Dossier simualtions
                mkdir(x,0700);

                while((contenu=readdir(ddossier))!=NULL)
                {
                    strcpy(x,nomDossier);
                    strcat(x,"/");
                    FILE *dimage=fopen(strcat(x,contenu->d_name),"rb");
                    stat(x,&fichier);
                    fread(&nombreMagique,sizeof(int),1,dimage);
                    fclose(dimage);
                    if((nombreMagique==ISJPEGEXIF||nombreMagique==ISJPEGJFIF)&&(S_ISDIR(fichier.st_mode)!=1)) //est-ce bien un JPEG ?
                    {
                        img=stbi_load(x,&width,&height,&channels,0);

                        //-------------creation des images en niveau de gris destinees a la riso-------

                        unsigned char *imageComposante1=malloc_erreurs(width*height*sizeof(char));
                        unsigned char *imageComposante2=malloc_erreurs(width*height*sizeof(char));
                        unsigned char *imageComposante3=malloc_erreurs(width*height*sizeof(char));

                        calculerFichiersImpression3D(img,width,height,profil3D,bibliotheque3D,taux_encre);
                        printf("image %s traitee ",contenu->d_name);
                        fflush(stdout);

                        for(i=0;i<width*height;i++)
                        {
                            imageComposante1[i]=bibliotheque3D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante1;
                            imageComposante2[i]=bibliotheque3D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante2;
                            imageComposante3[i]=bibliotheque3D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante3;  
                        }

                        //-------------creation de l'image simulee de l'impression-----------------------

                        imageSimulee=simulerImpression3D(imageComposante1,imageComposante2,imageComposante3,couleurPapier.couleur,couleur1.couleur,couleur2.couleur,couleur3.couleur,width*height);

                        //ENREGISTREMENT DES IMAGES
                        if(sflag!=1)//si -s est positionné on ne fait que la simulation
                        {    //Couleur1
                        sprintf(x,"%s/Images_Traitees-%s-%s-%s_papier-%s/1-%s/%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,couleur1.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,1,imageComposante1,100);
                        
                            //Couleur2
                        sprintf(x,"%s/Images_Traitees-%s-%s-%s_papier-%s/2-%s/%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,couleur2.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,1,imageComposante2,100);

                            //Couleur3
                        sprintf(x,"%s/Images_Traitees-%s-%s-%s_papier-%s/3-%s/%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,couleur3.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,1,imageComposante3,100);
                        }
                            //Simulation
                        sprintf(x,"%s/Images_Traitees-%s-%s-%s_papier-%s/SIMULATIONS/%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,3,imageSimulee,80);
                        
                        
                        free(imageComposante1);
                        free(imageComposante2);
                        free(imageComposante3);
                        free(imageSimulee);

                        printf("et enregistree\n");
                        

                        stbi_image_free(img);
                    }
                
                }
                printf("\nImages enregistrees dans le dossier : %s/Images_Traitees-%s-%s-%s_papier-%s\n\n",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom);
                free(bibliotheque3D);
                free(profil3D);
                free(entete);

            }else //cas d'une image seule
            {
                //-------------Chargement de l'image------------------------
                img=stbi_load(nomFichierImage,&width,&height,&channels,0);
                //-------------creation des images en niveau de gris destinees a la riso-------

                unsigned char *imageComposante1=malloc_erreurs(width*height*sizeof(char));
                unsigned char *imageComposante2=malloc_erreurs(width*height*sizeof(char));
                unsigned char *imageComposante3=malloc_erreurs(width*height*sizeof(char));

                calculerFichiersImpression3D(img,width,height,profil3D,bibliotheque3D,taux_encre);

                for(i=0;i<width*height;i++)
                    {
                        imageComposante1[i]=bibliotheque3D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante1;
                        imageComposante2[i]=bibliotheque3D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante2;
                        imageComposante3[i]=bibliotheque3D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante3;  
                    }

                //-------------creation de l'image simulee de l'impression-----------------------

                imageSimulee=simulerImpression3D(imageComposante1,imageComposante2,imageComposante3,couleurPapier.couleur,couleur1.couleur,couleur2.couleur,couleur3.couleur,width*height);
                
                //--------------------enregistrement des fichiers (images et maj bibliotheque)---------
                
                
                sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s_papier-%s/",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom);
                mkdir(x,0700);

                if(sflag!=1)
                {
                    sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s_papier-%s/1-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,couleur1.nom,nomFichierImage);
                    stbi_write_jpg(x,width,height,1,imageComposante1,100);
                    sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s_papier-%s/2-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,couleur2.nom,nomFichierImage);
                    stbi_write_jpg(x,width,height,1,imageComposante2,100);
                    sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s_papier-%s/3-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,couleur3.nom,nomFichierImage);
                    stbi_write_jpg(x,width,height,1,imageComposante3,100);
                }

                sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s_papier-%s/SIMULATION-%s-%s-%s_papier-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom,nomFichierImage);
                stbi_write_jpg(x,width,height,3,imageSimulee,80);

                printf("Images enregistrees dans le dossier : Images_Traitees/%s-traitee-%s-%s-%s_papier-%s\n\n",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleurPapier.nom);
                


                stbi_image_free(img);
                free(bibliotheque3D);
                free(profil3D);
                free(entete);
                free(imageComposante1);
                free(imageComposante2);
                free(imageComposante3);
                free(imageSimulee); 
            }


        
        break;
        }
        case 4: //QUADRICHROMIE
        {
        //CREATION DU PROFIL & INITIALISATION DES VARIABLES DE CALCUL DES FICHIERS D'IMPRESSION    
        ElementBibliotheque4D *bibliotheque4D=malloc_erreurs(256*256*256*sizeof(ElementBibliotheque4D));
        ComposantesNuance4D *profil4D=malloc_erreurs(16*16*16*sizeof(ComposantesNuance4D));
        EnteteFichierProfil *entete=malloc_erreurs(sizeof(EnteteFichierProfil));
        unsigned char *img=NULL; //pointeur vers l'image
        char x[400]; //variable tampon pour stocker les noms et creer les fichiers
        char ouiNon[2]; //Utiliser pour la validation utilisateur
        struct stat fichier;
   
        //----------------------Initialisation de la bibliotheque--------------
        for(i=0;i<256*256*256;i++)
        {
            bibliotheque4D[i].dejaCalcule=0; //Mise a 0 des indicateurs de couleur déja calculee
        }
        //------------------------------------------
        
        if(chargerProfil4D(couleurPapier,couleur1,couleur2,couleur3,couleur4,profil4D,entete)==0) //Rechargement du profil s'il existe ou creation si ce n'est pas le cas
        {
            printf("Le profil %s + %s + %s + %s sur papier %s n'existe pas \nVoulez-vous le creer ?[O-oui/N-non, quitter le programme]\n", couleur1.nom, couleur2.nom, couleur3.nom, couleur4.nom, couleurPapier.nom);
            
            //------Creation du nauncier des couleurs imprimables avec le jeu de couleurs choisies-----
            
            nuancierRgb=malloc_erreurs(RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*sizeof(RgbColor));
            
            creationNuancier4D(couleurPapier.couleur,&couleur1.couleur,&couleur2.couleur,&couleur3.couleur,&couleur4.couleur,nuancierRgb);
            
            //------Estimation du temps de calcul d'un nouveau profil 2 couleurs-----------------------
           
            int *tableauDesDifferences=malloc_erreurs(RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*sizeof(int));
            
            estimationTempsCalul(4, nuancierRgb, tableauDesDifferences);

            lire(ouiNon,2);
            while((ouiNon[0]!='O')&&(ouiNon[0]!='N'))
            {
                printf("Le profil n'existe pas \nVoulez-vous le creer ?[O/N]\n");
                lire(ouiNon,2);
            }
            if (ouiNon[0]=='N') exit(0); //Le programme s'arrete si l'on choisit de ne pas creer le profil
            creerProfil4D(couleurPapier,couleur1,couleur2, couleur3,couleur4,profil4D,entete,nuancierRgb,tableauDesDifferences);
            
            free(nuancierRgb);
            free(tableauDesDifferences);
        }

        //TRAITEMENT D'UN REPERTOIRE D'IMAGES
            if(dflag==1){
                //DIR *ddossier=NULL;
                struct dirent *contenu;
                DIR *ddossier=opendir(nomDossier); //descripteur de dossier
                int nombreMagique; //permet d'identifier un fichier jpeg
                
                

                //CREATION DES DOSSIERS POUR STOCKER LES FICHIERS CALCULES
                sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom);
                mkdir(x,0700);
                if(sflag!=1)//si -s est positionné on ne fait que la simulation
                {
                    sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s/1-%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur1.nom); //Dossier couleur 1
                    mkdir(x,0700);
                    sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s/2-%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur2.nom); //Dossier couleur 2
                    mkdir(x,0700);
                    sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s/3-%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur3.nom); //Dossier couleur 3
                    mkdir(x,0700);
                    sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s/4-%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur4.nom); //Dossier couleur 4
                    mkdir(x,0700);
                }
                sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s/SIMULATIONS",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom); //Dossier simualtions
                mkdir(x,0700);

                while((contenu=readdir(ddossier))!=NULL)
                {
                    strcpy(x,nomDossier);
                    strcat(x,"/");
                    FILE *dimage=fopen(strcat(x,contenu->d_name),"rb");
                    stat(x,&fichier);
                    fread(&nombreMagique,sizeof(int),1,dimage);
                    fclose(dimage);
                    if((nombreMagique==ISJPEGEXIF||nombreMagique==ISJPEGJFIF)&&(S_ISDIR(fichier.st_mode)!=1)) //est-ce bien un JPEG ?
                    {
                        img=stbi_load(x,&width,&height,&channels,0);

                        //-------------creation des images en niveau de gris destinees a la riso-------

                        unsigned char *imageComposante1=malloc_erreurs(width*height*sizeof(char));
                        unsigned char *imageComposante2=malloc_erreurs(width*height*sizeof(char));
                        unsigned char *imageComposante3=malloc_erreurs(width*height*sizeof(char));
                        unsigned char *imageComposante4=malloc_erreurs(width*height*sizeof(char));

                        calculerFichiersImpression4D(img,width,height,profil4D,bibliotheque4D,taux_encre);
                        printf("image %s traitee ",contenu->d_name);
                        fflush(stdout);

                        for(i=0;i<width*height;i++)
                        {
                            imageComposante1[i]=bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante1;
                            imageComposante2[i]=bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante2;
                            imageComposante3[i]=bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante3;
                            imageComposante4[i]=bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante4;  
                        }

                        //-------------creation de l'image simulee de l'impression-----------------------

                        imageSimulee=simulerImpression4D(imageComposante1,imageComposante2,imageComposante3,imageComposante4,couleurPapier.couleur,couleur1.couleur,couleur2.couleur,couleur3.couleur,couleur4.couleur,width*height);

                        //ENREGISTREMENT DES IMAGES
                        if(sflag!=1)//si -s est positionné on ne fait que la simulation
                        {    //Couleur1
                        sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s/1-%s/%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur1.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,1,imageComposante1,100);
                        
                            //Couleur2
                        sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s/2-%s/%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur2.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,1,imageComposante2,100);

                            //Couleur3
                        sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s/3-%s/%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur3.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,1,imageComposante3,100);

                            //Couleur4
                        sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s/4-%s/%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur4.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,1,imageComposante4,100);
                        }
                            //Simulation
                        sprintf(x,"%s/Images_Traitees-%s-%s-%s-%s_papier-%s/SIMULATIONS/%s",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,contenu->d_name);
                        stbi_write_jpg(x,width,height,3,imageSimulee,80);
                        
                        
                        free(imageComposante1);
                        free(imageComposante2);
                        free(imageComposante3);
                        free(imageComposante4);
                        free(imageSimulee);

                        printf("et enregistree\n");
                        

                        stbi_image_free(img);
                    }
                
                }
                printf("\nImages enregistrees dans le dossier : %s/Images_Traitees-%s-%s-%s-%s_papier-%s\n\n",nomDossier,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom);
                free(bibliotheque4D);
                free(profil4D);
                free(entete);

            }else //cas d'une image seule
            {
                //-------------Chargement de l'image------------------------
                img=stbi_load(nomFichierImage,&width,&height,&channels,0);
                //-------------creation des images en niveau de gris destinees a la riso-------

                unsigned char *imageComposante1=malloc_erreurs(width*height*sizeof(char));
                unsigned char *imageComposante2=malloc_erreurs(width*height*sizeof(char));
                unsigned char *imageComposante3=malloc_erreurs(width*height*sizeof(char));
                unsigned char *imageComposante4=malloc_erreurs(width*height*sizeof(char));

                calculerFichiersImpression4D(img,width,height,profil4D,bibliotheque4D,taux_encre);

                for(i=0;i<width*height;i++)
                    {
                        imageComposante1[i]=bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante1;
                        imageComposante2[i]=bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante2;
                        imageComposante3[i]=bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante3; 
                        imageComposante4[i]=bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes.composante4;  
                    }

                //-------------creation de l'image simulee de l'impression-----------------------

                imageSimulee=simulerImpression4D(imageComposante1,imageComposante2,imageComposante3,imageComposante4,couleurPapier.couleur,couleur1.couleur,couleur2.couleur,couleur3.couleur,couleur4.couleur,width*height);
                
                //--------------------enregistrement des fichiers (images et maj bibliotheque)---------
                
                
                sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s-%s_papier-%s/",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom);
                mkdir(x,0700);

                if(sflag!=1)
                {
                    sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s-%s_papier-%s/1-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur1.nom,nomFichierImage);
                    stbi_write_jpg(x,width,height,1,imageComposante1,100);
                    sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s-%s_papier-%s/2-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur2.nom,nomFichierImage);
                    stbi_write_jpg(x,width,height,1,imageComposante2,100);
                    sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s-%s_papier-%s/3-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur3.nom,nomFichierImage);
                    stbi_write_jpg(x,width,height,1,imageComposante3,100);
                    sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s-%s_papier-%s/4-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur4.nom,nomFichierImage);
                    stbi_write_jpg(x,width,height,1,imageComposante4,100);
                }

                sprintf(x,"Images_Traitees/%s-traitee-%s-%s-%s-%s_papier-%s/SIMULATION-%s-%s-%s-%s_papier-%s_%s",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom,nomFichierImage);
                stbi_write_jpg(x,width,height,3,imageSimulee,80);

                printf("Images enregistrees dans le dossier : Images_Traitees/%s-traitee-%s-%s-%s-%s_papier-%s\n\n",nomFichierImage,couleur1.nom,couleur2.nom,couleur3.nom,couleur4.nom,couleurPapier.nom);
                


                stbi_image_free(img);
                free(bibliotheque4D);
                free(profil4D);
                free(entete);
                free(imageComposante1);
                free(imageComposante2);
                free(imageComposante3);
                free(imageComposante4);
                free(imageSimulee); 
            }


        
        break;
        }
        default:
        {
            exit(1);
        }
    }

}

void utilisation(){
    printf("\nFonctionnement du programme : Indiquez l'image ou le dossier d'images a traiter.\n\tExemple : ./2B3Chromie mon_image.jpg ou ./2B3Chromie mon_dossier\n");
    printf("Pour ne calculer que la simulation du rendu utilisez l'option -s\n");
    printf("\tExemple : ./2B3Chromie -s mon_image\n");
    printf("Pour ajouter ou supprimer des couleurs d'impression ou de papier, utilisez l'option -a\n");
    printf("\tExemple : ./2B3Chromie -a mon_image\n");
    printf("Les option sont cumulables\n\n");

}

//fonction de reservation de memoire avec verif d'erreur
void *malloc_erreurs(unsigned int tailleMemoire)
{
    void *ptr;
    ptr=malloc(tailleMemoire);
    if(ptr==NULL)
    {
        printf("dans malloc_erreur() sur l'allocation memoire");
        exit(0);
    }
    return ptr;
}

 
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
 
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void printLogo()
{
    printf("  ___            ___      \n");
    printf(" // \\\\   ___    // \\\\     +\n");
    printf(" ^  ||  || \\\\   ^  ||    + +\n");
    printf("   //   ||_//     _//    _____\n");
    printf("  //    ||  \\\\    -\\\\   / +  /\n");
    printf(" //___  ||__||  _  ||  /____/_\n");
    printf("|_____| ||___/  \\\\_//   //////\n");
    printf("*C  H  R  O  M  I  E*  //////\n");
    printf("Version : %s-%s\n\n",OS,VERSION);

}