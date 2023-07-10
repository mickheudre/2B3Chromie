#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "structures.h"
#include "conversion.h"
#include "main.h"
#include "recherche.h"

void creationNuancier1D(const RgbColor couleurPapier,const RgbColor *couleur1,RgbColor *nuancierRgb1D)
{
    //CETTE FONCTION CREE UNE LISTE DE TAILLE "RESOLUTION" DE TOUTES
    //LES COMBINAISONS DE COULEURS POSSIBLES AVEC LES COULEURS CHOISIES
    RgbColor *nuancesCouleur1=malloc_erreurs(RESOLUTION*sizeof(RgbColor));

    int i=0;

    for(i=0;i<RESOLUTION;i++) //CREATION DES NUANCES PAR COULEUR
    {
        nuancesCouleur1[i].r=couleur1->r*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur1[i].g=couleur1->g*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur1[i].b=couleur1->b*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
    }
    
    
    for(i=0;i<RESOLUTION;i++) //Calcul des differentes nuances
    {
        nuancierRgb1D[i].r=(unsigned char)((float)couleurPapier.r*(float)nuancesCouleur1[i].r/255.0);
        nuancierRgb1D[i].g=(unsigned char)((float)couleurPapier.g*(float)nuancesCouleur1[i].g/255.0);
        nuancierRgb1D[i].b=(unsigned char)((float)couleurPapier.b*(float)nuancesCouleur1[i].b/255.0);
    }

    free(nuancesCouleur1);
}

void creationNuancier2D(const RgbColor couleurPapier,const RgbColor *couleur1,const RgbColor *couleur2,RgbColor *nuancierRgb2D)
{
    //CETTE FONCTION CREE UNE LISTE DE TAILLE RESOLUTION*resolutionCouleur2 DE TOUTES
    //LES COMBINAISONS DE COULEURS POSSIBLES AVEC LES COULEURS CHOISIES
    RgbColor *nuancesCouleur1=malloc_erreurs(RESOLUTION*sizeof(RgbColor));
    RgbColor *nuancesCouleur2=malloc_erreurs(RESOLUTION*sizeof(RgbColor));

    int i=0,j=0;

    for(i=0;i<RESOLUTION;i++) //CREATION DES NUANCES PAR COULEUR
    {
        nuancesCouleur1[i].r=couleur1->r*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur1[i].g=couleur1->g*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur1[i].b=couleur1->b*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));

        nuancesCouleur2[i].r=couleur2->r*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur2[i].g=couleur2->g*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur2[i].b=couleur2->b*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
    }
    
    
    for(i=0;i<RESOLUTION;i++) //Calcul des differentes nuances
    {
        for(j=0;j<RESOLUTION;j++)
        {
            nuancierRgb2D[RESOLUTION*i+j].r=(unsigned char)((float)couleurPapier.r*(float)nuancesCouleur1[j].r*(float)nuancesCouleur2[i].r/(255.0*255));
            nuancierRgb2D[RESOLUTION*i+j].g=(unsigned char)((float)couleurPapier.g*(float)nuancesCouleur1[j].g*(float)nuancesCouleur2[i].g/(255.0*255));
            nuancierRgb2D[RESOLUTION*i+j].b=(unsigned char)((float)couleurPapier.b*(float)nuancesCouleur1[j].b*(float)nuancesCouleur2[i].b/(255.0*255));
        }
    }

    free(nuancesCouleur1);
    free(nuancesCouleur2);
}

void creationNuancier3D(const RgbColor couleurPapier,
                        const RgbColor *couleur1,
                        const RgbColor *couleur2,
                        const RgbColor *couleur3,
                        RgbColor *nuancierRgb3D)
{
    RgbColor *nuancesCouleur1=malloc_erreurs(RESOLUTION*sizeof(RgbColor));
    RgbColor *nuancesCouleur2=malloc_erreurs(RESOLUTION*sizeof(RgbColor));
    RgbColor *nuancesCouleur3=malloc_erreurs(RESOLUTION*sizeof(RgbColor));

    int i=0,j=0,k=0;

    for(i=0;i<RESOLUTION;i++) //CREATION DES NUANCES PAR COULEUR
    {
        nuancesCouleur1[i].r=couleur1->r*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur1[i].g=couleur1->g*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur1[i].b=couleur1->b*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));

        nuancesCouleur2[i].r=couleur2->r*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur2[i].g=couleur2->g*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur2[i].b=couleur2->b*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));

        nuancesCouleur3[i].r=couleur3->r*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur3[i].g=couleur3->g*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
        nuancesCouleur3[i].b=couleur3->b*(float)i/(RESOLUTION-1)+255.0*(1-(float)i*1/(RESOLUTION-1));
    }
    
    
    for(i=0;i<RESOLUTION;i++) //Calcul des differentes nuances
    {
        for(j=0;j<RESOLUTION;j++)
        {
            for(k=0;k<RESOLUTION;k++)
            {
                nuancierRgb3D[RESOLUTION*RESOLUTION*i+j*RESOLUTION+k].r=(unsigned char)((float)couleurPapier.r*(float)nuancesCouleur1[k].r*(float)nuancesCouleur2[j].r*(float)nuancesCouleur3[i].r/(255*255*255));
                nuancierRgb3D[RESOLUTION*RESOLUTION*i+j*RESOLUTION+k].g=(unsigned char)((float)couleurPapier.g*(float)nuancesCouleur1[k].g*(float)nuancesCouleur2[j].g*(float)nuancesCouleur3[i].g/(255*255*255));
                nuancierRgb3D[RESOLUTION*RESOLUTION*i+j*RESOLUTION+k].b=(unsigned char)((float)couleurPapier.b*(float)nuancesCouleur1[k].b*(float)nuancesCouleur2[j].b*(float)nuancesCouleur3[i].b/(255*255*255));

            }
        }           
    }

    free(nuancesCouleur1);
    free(nuancesCouleur2);
    free(nuancesCouleur3);

}

void creationNuancier4D(const RgbColor couleurPapier,
                        const RgbColor *couleur1,
                        const RgbColor *couleur2,
                        const RgbColor *couleur3,
                        const RgbColor *couleur4,
                        RgbColor *nuancierRgb4D)
{
    RgbColor *nuancesCouleur1=malloc_erreurs(RESOLUTION_DIMINUE*sizeof(RgbColor));
    RgbColor *nuancesCouleur2=malloc_erreurs(RESOLUTION_DIMINUE*sizeof(RgbColor));
    RgbColor *nuancesCouleur3=malloc_erreurs(RESOLUTION_DIMINUE*sizeof(RgbColor));
    RgbColor *nuancesCouleur4=malloc_erreurs(RESOLUTION_DIMINUE*sizeof(RgbColor));

    int i=0,j=0,k=0,l=0;
    int increment=0;
    unsigned long int indiceNuancier=0;

    for(i=0;i<RESOLUTION_DIMINUE;i++) //CREATION DES NUANCES PAR COULEUR
    {   
        increment=PAS_RESOLUTION_DIMINUE*i;
        nuancesCouleur1[i].r=couleur1->r*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));
        nuancesCouleur1[i].g=couleur1->g*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));
        nuancesCouleur1[i].b=couleur1->b*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));

        nuancesCouleur2[i].r=couleur2->r*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));
        nuancesCouleur2[i].g=couleur2->g*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));
        nuancesCouleur2[i].b=couleur2->b*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));

        nuancesCouleur3[i].r=couleur3->r*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));
        nuancesCouleur3[i].g=couleur3->g*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));
        nuancesCouleur3[i].b=couleur3->b*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));

        nuancesCouleur4[i].r=couleur4->r*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));
        nuancesCouleur4[i].g=couleur4->g*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));
        nuancesCouleur4[i].b=couleur4->b*(float)increment/(RESOLUTION-1)+255.0*(1-(float)increment*1/(RESOLUTION-1));
    }
    
    
    for(i=0;i<RESOLUTION_DIMINUE;i++) //Calcul des differentes nuances
    { 
        for(j=0;j<RESOLUTION_DIMINUE;j++)
        {
            for(k=0;k<RESOLUTION_DIMINUE;k++)
            {
                for(l=0;l<RESOLUTION_DIMINUE;l++)
                {
                    nuancierRgb4D[i*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE+j*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE+k*RESOLUTION_DIMINUE+l].r=(unsigned char)((double)couleurPapier.r*(float)nuancesCouleur1[l].r*(float)nuancesCouleur2[k].r*(float)nuancesCouleur3[j].r*(float)nuancesCouleur4[i].r/(255.0*255*255*255));
                    nuancierRgb4D[i*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE+j*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE+k*RESOLUTION_DIMINUE+l].g=(unsigned char)((double)couleurPapier.g*(float)nuancesCouleur1[l].g*(float)nuancesCouleur2[k].g*(float)nuancesCouleur3[j].g*(float)nuancesCouleur4[i].g/(255.0*255*255*255));
                    nuancierRgb4D[i*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE+j*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE+k*RESOLUTION_DIMINUE+l].b=(unsigned char)((double)couleurPapier.b*(float)nuancesCouleur1[l].b*(float)nuancesCouleur2[k].b*(float)nuancesCouleur3[j].b*(float)nuancesCouleur4[i].b/(255.0*255*255*255));
                }
            }
        }           
    }
    free(nuancesCouleur1);
    free(nuancesCouleur2);
    free(nuancesCouleur3);
    free(nuancesCouleur4);

    

}

void calculerFichiersImpression1D(unsigned char *img,int width,int height,ComposantesNuance1D *profil1D,ElementBibliotheque1D *bibliotheque1D,int taux_encre_max)
{
    ComposantesNuance1D composantes1D={0};
    int somme=0;
    float pourcentage=0;
    for(int i=0;i<width*height;i++)
        {
            if(bibliotheque1D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].dejaCalcule==0)
            {
                composantes1D=interpolation1D(((RgbColor*)img)[i],profil1D);
                somme=255-(composantes1D.composante1);
                if(somme>taux_encre_max)
                {
                    pourcentage=(somme-taux_encre_max)/(float)somme;
                    composantes1D.composante1=255+(composantes1D.composante1-255)*(1-pourcentage/4);
                }
                if((255-(int)composantes1D.composante1)>taux_encre_max)
                {
                    composantes1D.composante1=255-taux_encre_max;
                }
                bibliotheque1D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].dejaCalcule=1;
                bibliotheque1D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes=composantes1D;
            
            }

            if(i%((width*height)/10)==0){
                printf("---");
                fflush(stdout);
            }
        }
        printf("100%%\n");
}

void calculerFichiersImpression2D(unsigned char *img,int width,int height,ComposantesNuance2D *profil2D,ElementBibliotheque2D *bibliotheque2D,int taux_encre_max)
{
    ComposantesNuance2D composantes2D={0,0};
    int somme=0;
    float pourcentage=0;
    for(int i=0;i<width*height;i++)
        {
            if(bibliotheque2D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].dejaCalcule==0)
            {
                composantes2D=interpolation2D(((RgbColor*)img)[i],profil2D);
                somme=2*255-(composantes2D.composante1+composantes2D.composante2);
                if(somme>taux_encre_max)
                {
                    pourcentage=(somme-taux_encre_max)/(float)somme;
                    composantes2D.composante1=255+(composantes2D.composante1-255)*(1-pourcentage/4);
                    composantes2D.composante2=255+(composantes2D.composante2-255)*(1-pourcentage/4);
                }
                bibliotheque2D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].dejaCalcule=1;
                bibliotheque2D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes=composantes2D;
            
            }

            if(i%((width*height)/10)==0){
                printf("---");
                fflush(stdout);
            }
        }
        printf("100%%\n");
}

void calculerFichiersImpression3D(unsigned char *img,int width,int height,ComposantesNuance3D *profil3D,ElementBibliotheque3D *bibliotheque3D,int taux_encre_max)
{
    ComposantesNuance3D composantes3D={0,0,0};
    int somme=0;
    float pourcentage=0;
    for(int i=0;i<width*height;i++)
        {
            if(bibliotheque3D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].dejaCalcule==0)
            {
                composantes3D=interpolation3D(((RgbColor*)img)[i],profil3D);
                somme=3*255-(composantes3D.composante1+composantes3D.composante2+composantes3D.composante3);
                if(somme>taux_encre_max)
                {
                    pourcentage=(somme-taux_encre_max)/(float)somme;
                    composantes3D.composante1=255+(composantes3D.composante1-255)*(1-pourcentage/4);
                    composantes3D.composante2=255+(composantes3D.composante2-255)*(1-pourcentage/4);
                    composantes3D.composante3=255+(composantes3D.composante3-255)*(1-pourcentage/4);
                }
                bibliotheque3D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].dejaCalcule=1;
                bibliotheque3D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes=composantes3D;
            
            }
            if(i%((width*height)/10)==0){
                printf("---");
                fflush(stdout);
            }
        }
        printf("100%%\n");
}

void calculerFichiersImpression4D(unsigned char *img,int width,int height,ComposantesNuance4D *profil4D,ElementBibliotheque4D *bibliotheque4D,int taux_encre_max)
{
    ComposantesNuance4D composantes4D={0,0,0,0};
    int somme=0;
    float pourcentage=0;
    for(int i=0;i<width*height;i++)
        {
            if(bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].dejaCalcule==0)
            {
                composantes4D=interpolation4D(((RgbColor*)img)[i],profil4D);
                somme=4*255-(composantes4D.composante1+composantes4D.composante2+composantes4D.composante3+composantes4D.composante4);
                if(somme>taux_encre_max)
                {
                    pourcentage=(somme-taux_encre_max)/(float)somme;
                    composantes4D.composante1=255+(composantes4D.composante1-255)*(1-pourcentage/4);
                    composantes4D.composante2=255+(composantes4D.composante2-255)*(1-pourcentage/4);
                    composantes4D.composante3=255+(composantes4D.composante3-255)*(1-pourcentage/4);
                    composantes4D.composante4=255+(composantes4D.composante4-255)*(1-pourcentage/4);
                }
                bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].dejaCalcule=1;
                bibliotheque4D[256*256*((RgbColor*)img)[i].r+256*((RgbColor*)img)[i].g+((RgbColor*)img)[i].b].composantes=composantes4D;
            
            }
            if(i%((width*height)/10)==0){
                printf("---");
                fflush(stdout);
            }
        }
        printf("100%%\n");
}


