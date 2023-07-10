#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "recherche.h"
#include "conversion.h"
#include <math.h>

//FONCTIONS DE CREATION DES PROFILS DE COULEUR
ComposantesNuance1D rechercheNuanceProche1D(const RgbColor couleur,const RgbColor *nuancier1D, int *tableauErreur)
{
    int i=0;
    int positionMinimum=0;
    
    ComposantesNuance1D composantesTrouvees={0};

    for(i=0;i<RESOLUTION;i+=1)
    {
        tableauErreur[i]=calculDistanceCouleur(nuancier1D[i],couleur);
    }
    positionMinimum=rechercheMinimum(tableauErreur,RESOLUTION);
    composantesTrouvees.composante1=255-positionMinimum;
   
    return composantesTrouvees;
}

ComposantesNuance2D rechercheNuanceProche2D(const RgbColor couleur,const RgbColor *nuancier2D, int *tableauErreur)
{
    int i=0, j=0;
    int positionMinimum=0;
    
    ComposantesNuance2D composantesTrouvees={0,0};

    for(i=0;i<RESOLUTION;i+=1)
    {
        for(j=0;j<RESOLUTION;j+=1)
        {
            tableauErreur[RESOLUTION*i+j]=calculDistanceCouleur(nuancier2D[RESOLUTION*i+j],couleur);
        }
    }
    positionMinimum=rechercheMinimum(tableauErreur,RESOLUTION*RESOLUTION);
    composantesTrouvees.composante1=255-(positionMinimum%RESOLUTION);
    composantesTrouvees.composante2=255-(positionMinimum/RESOLUTION);
   
    return composantesTrouvees;
}


ComposantesNuance3D rechercheNuanceProche3D(const RgbColor couleur,
                                            const RgbColor *nuancier3D,int *tableauErreur)
{
    int i=0, j=0, k=0;
    int positionMinimum=0;
    ComposantesNuance3D composantesTrouvees={0,0,0};
    
    for(i=0;i<RESOLUTION;i++)
    {
        for(j=0;j<RESOLUTION;j++)
        {
            for(k=0;k<RESOLUTION;k++)
            {
                tableauErreur[i*RESOLUTION*RESOLUTION+j*RESOLUTION+k]=calculDistanceCouleur(nuancier3D[i*RESOLUTION*RESOLUTION+j*RESOLUTION+k],couleur);
            }
        }
    }
    positionMinimum=rechercheMinimum(tableauErreur,RESOLUTION*RESOLUTION*RESOLUTION);
    composantesTrouvees.composante3=255-(positionMinimum/(RESOLUTION*RESOLUTION));
    composantesTrouvees.composante2=255-((positionMinimum%(RESOLUTION*RESOLUTION))/RESOLUTION);
    composantesTrouvees.composante1=255-((positionMinimum%(RESOLUTION*RESOLUTION))%RESOLUTION);


    return composantesTrouvees;
}

ComposantesNuance4D rechercheNuanceProche4D(const RgbColor couleur,
                                            const RgbColor *nuancier4D,int *tableauErreur)
{
    int i, j, k, l;
    int positionMinimum=0;
    ComposantesNuance4D composantesTrouvees={0,0,0,0};
    
    for(i=0;i<RESOLUTION_DIMINUE;i++)
    {
        for(j=0;j<RESOLUTION_DIMINUE;j++)
        {
            for(k=0;k<RESOLUTION_DIMINUE;k++)
            {
                for(l=0;l<RESOLUTION_DIMINUE;l++)
                {
                    tableauErreur[i*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE+j*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE+k*RESOLUTION_DIMINUE+l]
                            =calculDistanceCouleur(nuancier4D[i*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE+j*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE+k*RESOLUTION_DIMINUE+l],couleur);
                }
                
            }
        }
    }
    positionMinimum=rechercheMinimum(tableauErreur,RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE);
    composantesTrouvees.composante4=255-PAS_RESOLUTION_DIMINUE*(positionMinimum/(RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE));
    composantesTrouvees.composante3=255-PAS_RESOLUTION_DIMINUE*((positionMinimum%(RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE))/(RESOLUTION_DIMINUE*RESOLUTION_DIMINUE));
    composantesTrouvees.composante2=255-PAS_RESOLUTION_DIMINUE*(((positionMinimum%(RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE))%(RESOLUTION_DIMINUE*RESOLUTION_DIMINUE))/RESOLUTION_DIMINUE);
    composantesTrouvees.composante1=255-PAS_RESOLUTION_DIMINUE*(((positionMinimum%(RESOLUTION_DIMINUE*RESOLUTION_DIMINUE*RESOLUTION_DIMINUE))%(RESOLUTION_DIMINUE*RESOLUTION_DIMINUE))%RESOLUTION_DIMINUE);


    return composantesTrouvees;
}


//FONCTIONS DE CALCUL DES FICHIERS POUR LIMPRESSION DES IMAGES
ComposantesNuance1D interpolation1D(const RgbColor couleur, ComposantesNuance1D *profil)
{
    int bRInf=0, bRSup=0; //Bornes inferieure et superieure du voxel de couleur
    int bGInf=0, bGSup=0;
    int bBInf=0, bBSup=0;
    int iR,iG,iB; //index de la couleur dans le profil
    float fR=0, fG=0, fB=0; //Fraction de rouge, vert et bleu dans le voxel de couleur
    ComposantesNuance1D composantesTrouvees={0};

    iR=couleur.r/17;
    iG=couleur.g/17;
    iB=couleur.b/17;

    if(couleur.r==255)
    {
        bRInf=238; bRSup=255; fR=1;
        iR=bRInf/17;
    }else
    {
        bRInf=iR*17; bRSup=bRInf+17; fR=(float)(couleur.r%17)/17;
    }

    if(couleur.g==255)
    {
        bGInf=238; bGSup=255; fG=1;
        iG=bGInf/17;
    }else
    {
        bGInf=iG*17; bGSup=bGInf+17; fG=(float)(couleur.g%17)/17;
    }

    if(couleur.b==255)
    {
        bBInf=238; bBSup=255; fB=1;
        iB=bBInf/17;
    }else
    {
        bBInf=iB*17; bBSup=bBInf+17; fB=(float)(couleur.b%17)/17;
    }
    //INTERPOLATION
    float v1=(1-fR)*profil[iR*16*16+iG*16+iB].composante1+fR*profil[(iR+1)*16*16+iG*16+iB].composante1;
    float v2=(1-fR)*profil[iR*16*16+(iG+1)*16+iB].composante1+fR*profil[(iR+1)*16*16+(iG+1)*16+iB].composante1;
    float v3=(1-fR)*profil[iR*16*16+iG*16+(iB+1)].composante1+fR*profil[(iR+1)*16*16+iG*16+(iB+1)].composante1;
    float v4=(1-fR)*profil[iR*16*16+(iG+1)*16+(iB+1)].composante1+fR*profil[(iR+1)*16*16+(iG+1)*16+(iB+1)].composante1;
    float v12=(1-fG)*v1+fG*v2;
    float v34=(1-fG)*v3+fG*v4;
    composantesTrouvees.composante1=(unsigned char)((1-fB)*v12+fB*v34);

    return composantesTrouvees;
}

ComposantesNuance2D interpolation2D(const RgbColor couleur, ComposantesNuance2D *profil)
{
    int bRInf=0, bRSup=0; //Bornes inferieure et superieure du voxel de couleur
    int bGInf=0, bGSup=0;
    int bBInf=0, bBSup=0;
    int iR,iG,iB; //index de la couleur dans le profil
    float fR=0, fG=0, fB=0; //Fraction de rouge, vert et bleu dans le voxel de couleur
    ComposantesNuance2D composantesTrouvees={0,0};

    iR=couleur.r/17;
    iG=couleur.g/17;
    iB=couleur.b/17;

    if(couleur.r==255)
    {
        bRInf=238; bRSup=255; fR=1;
        iR=bRInf/17;
    }else
    {
        bRInf=iR*17; bRSup=bRInf+17; fR=(float)(couleur.r%17)/17;
    }

    if(couleur.g==255)
    {
        bGInf=238; bGSup=255; fG=1;
        iG=bGInf/17;
    }else
    {
        bGInf=iG*17; bGSup=bGInf+17; fG=(float)(couleur.g%17)/17;
    }

    if(couleur.b==255)
    {
        bBInf=238; bBSup=255; fB=1;
        iB=bBInf/17;
    }else
    {
        bBInf=iB*17; bBSup=bBInf+17; fB=(float)(couleur.b%17)/17;
    }
    //INTERPOLATION
    float v1=(1-fR)*profil[iR*16*16+iG*16+iB].composante1+fR*profil[(iR+1)*16*16+iG*16+iB].composante1;
    float v2=(1-fR)*profil[iR*16*16+(iG+1)*16+iB].composante1+fR*profil[(iR+1)*16*16+(iG+1)*16+iB].composante1;
    float v3=(1-fR)*profil[iR*16*16+iG*16+(iB+1)].composante1+fR*profil[(iR+1)*16*16+iG*16+(iB+1)].composante1;
    float v4=(1-fR)*profil[iR*16*16+(iG+1)*16+(iB+1)].composante1+fR*profil[(iR+1)*16*16+(iG+1)*16+(iB+1)].composante1;
    float v12=(1-fG)*v1+fG*v2;
    float v34=(1-fG)*v3+fG*v4;
    composantesTrouvees.composante1=(unsigned char)((1-fB)*v12+fB*v34);

    v1=(1-fR)*profil[iR*16*16+iG*16+iB].composante2+fR*profil[(iR+1)*16*16+iG*16+iB].composante2;
    v2=(1-fR)*profil[iR*16*16+(iG+1)*16+iB].composante2+fR*profil[(iR+1)*16*16+(iG+1)*16+iB].composante2;
    v3=(1-fR)*profil[iR*16*16+iG*16+(iB+1)].composante2+fR*profil[(iR+1)*16*16+iG*16+(iB+1)].composante2;
    v4=(1-fR)*profil[iR*16*16+(iG+1)*16+(iB+1)].composante2+fR*profil[(iR+1)*16*16+(iG+1)*16+(iB+1)].composante2;
    v12=(1-fG)*v1+fG*v2;
    v34=(1-fG)*v3+fG*v4;
    composantesTrouvees.composante2=(unsigned char)((1-fB)*v12+fB*v34);


    return composantesTrouvees;
}

ComposantesNuance3D interpolation3D(const RgbColor couleur, ComposantesNuance3D *profil)
{
    int bRInf=0, bRSup=0; //Bornes inferieure et superieure du voxel de couleur
    int bGInf=0, bGSup=0;
    int bBInf=0, bBSup=0;
    int iR,iG,iB; //index de la couleur dans le profil
    float fR=0, fG=0, fB=0; //Fraction de rouge, vert et bleu dans le voxel de couleur
    ComposantesNuance3D composantesTrouvees={0,0,0};

    iR=couleur.r/17;
    iG=couleur.g/17;
    iB=couleur.b/17;

    if(couleur.r==255)
    {
        bRInf=238; bRSup=255; fR=1;
        iR=bRInf/17;
    }else
    {
        bRInf=iR*17; bRSup=bRInf+17; fR=(float)(couleur.r%17)/17;
    }

    if(couleur.g==255)
    {
        bGInf=238; bGSup=255; fG=1;
        iG=bGInf/17;
    }else
    {
        bGInf=iG*17; bGSup=bGInf+17; fG=(float)(couleur.g%17)/17;
    }

    if(couleur.b==255)
    {
        bBInf=238; bBSup=255; fB=1;
        iB=bBInf/17;
    }else
    {
        bBInf=iB*17; bBSup=bBInf+17; fB=(float)(couleur.b%17)/17;
    }
    //INTERPOLATION
    float v1=(1-fR)*profil[iR*16*16+iG*16+iB].composante1+fR*profil[(iR+1)*16*16+iG*16+iB].composante1;
    float v2=(1-fR)*profil[iR*16*16+(iG+1)*16+iB].composante1+fR*profil[(iR+1)*16*16+(iG+1)*16+iB].composante1;
    float v3=(1-fR)*profil[iR*16*16+iG*16+(iB+1)].composante1+fR*profil[(iR+1)*16*16+iG*16+(iB+1)].composante1;
    float v4=(1-fR)*profil[iR*16*16+(iG+1)*16+(iB+1)].composante1+fR*profil[(iR+1)*16*16+(iG+1)*16+(iB+1)].composante1;
    float v12=(1-fG)*v1+fG*v2;
    float v34=(1-fG)*v3+fG*v4;
    composantesTrouvees.composante1=(unsigned char)((1-fB)*v12+fB*v34);

    v1=(1-fR)*profil[iR*16*16+iG*16+iB].composante2+fR*profil[(iR+1)*16*16+iG*16+iB].composante2;
    v2=(1-fR)*profil[iR*16*16+(iG+1)*16+iB].composante2+fR*profil[(iR+1)*16*16+(iG+1)*16+iB].composante2;
    v3=(1-fR)*profil[iR*16*16+iG*16+(iB+1)].composante2+fR*profil[(iR+1)*16*16+iG*16+(iB+1)].composante2;
    v4=(1-fR)*profil[iR*16*16+(iG+1)*16+(iB+1)].composante2+fR*profil[(iR+1)*16*16+(iG+1)*16+(iB+1)].composante2;
    v12=(1-fG)*v1+fG*v2;
    v34=(1-fG)*v3+fG*v4;
    composantesTrouvees.composante2=(unsigned char)((1-fB)*v12+fB*v34);

    v1=(1-fR)*profil[iR*16*16+iG*16+iB].composante3+fR*profil[(iR+1)*16*16+iG*16+iB].composante3;
    v2=(1-fR)*profil[iR*16*16+(iG+1)*16+iB].composante3+fR*profil[(iR+1)*16*16+(iG+1)*16+iB].composante3;
    v3=(1-fR)*profil[iR*16*16+iG*16+(iB+1)].composante3+fR*profil[(iR+1)*16*16+iG*16+(iB+1)].composante3;
    v4=(1-fR)*profil[iR*16*16+(iG+1)*16+(iB+1)].composante3+fR*profil[(iR+1)*16*16+(iG+1)*16+(iB+1)].composante3;
    v12=(1-fG)*v1+fG*v2;
    v34=(1-fG)*v3+fG*v4;
    composantesTrouvees.composante3=(unsigned char)((1-fB)*v12+fB*v34);


    return composantesTrouvees;
}

ComposantesNuance4D interpolation4D(const RgbColor couleur, ComposantesNuance4D *profil)
{
    int bRInf=0, bRSup=0; //Bornes inferieure et superieure du voxel de couleur
    int bGInf=0, bGSup=0;
    int bBInf=0, bBSup=0;
    int iR,iG,iB; //index de la couleur dans le profil
    float fR=0, fG=0, fB=0; //Fraction de rouge, vert et bleu dans le voxel de couleur
    ComposantesNuance4D composantesTrouvees={0,0,0,0};

    iR=couleur.r/17;
    iG=couleur.g/17;
    iB=couleur.b/17;

    if(couleur.r==255)
    {
        bRInf=238; bRSup=255; fR=1;
        iR=bRInf/17;
    }else
    {
        bRInf=iR*17; bRSup=bRInf+17; fR=(float)(couleur.r%17)/17;
    }

    if(couleur.g==255)
    {
        bGInf=238; bGSup=255; fG=1;
        iG=bGInf/17;
    }else
    {
        bGInf=iG*17; bGSup=bGInf+17; fG=(float)(couleur.g%17)/17;
    }

    if(couleur.b==255)
    {
        bBInf=238; bBSup=255; fB=1;
        iB=bBInf/17;
    }else
    {
        bBInf=iB*17; bBSup=bBInf+17; fB=(float)(couleur.b%17)/17;
    }
    //INTERPOLATION
    float v1=(1-fR)*profil[iR*16*16+iG*16+iB].composante1+fR*profil[(iR+1)*16*16+iG*16+iB].composante1;
    float v2=(1-fR)*profil[iR*16*16+(iG+1)*16+iB].composante1+fR*profil[(iR+1)*16*16+(iG+1)*16+iB].composante1;
    float v3=(1-fR)*profil[iR*16*16+iG*16+(iB+1)].composante1+fR*profil[(iR+1)*16*16+iG*16+(iB+1)].composante1;
    float v4=(1-fR)*profil[iR*16*16+(iG+1)*16+(iB+1)].composante1+fR*profil[(iR+1)*16*16+(iG+1)*16+(iB+1)].composante1;
    float v12=(1-fG)*v1+fG*v2;
    float v34=(1-fG)*v3+fG*v4;
    composantesTrouvees.composante1=(unsigned char)((1-fB)*v12+fB*v34);

    v1=(1-fR)*profil[iR*16*16+iG*16+iB].composante2+fR*profil[(iR+1)*16*16+iG*16+iB].composante2;
    v2=(1-fR)*profil[iR*16*16+(iG+1)*16+iB].composante2+fR*profil[(iR+1)*16*16+(iG+1)*16+iB].composante2;
    v3=(1-fR)*profil[iR*16*16+iG*16+(iB+1)].composante2+fR*profil[(iR+1)*16*16+iG*16+(iB+1)].composante2;
    v4=(1-fR)*profil[iR*16*16+(iG+1)*16+(iB+1)].composante2+fR*profil[(iR+1)*16*16+(iG+1)*16+(iB+1)].composante2;
    v12=(1-fG)*v1+fG*v2;
    v34=(1-fG)*v3+fG*v4;
    composantesTrouvees.composante2=(unsigned char)((1-fB)*v12+fB*v34);

    v1=(1-fR)*profil[iR*16*16+iG*16+iB].composante3+fR*profil[(iR+1)*16*16+iG*16+iB].composante3;
    v2=(1-fR)*profil[iR*16*16+(iG+1)*16+iB].composante3+fR*profil[(iR+1)*16*16+(iG+1)*16+iB].composante3;
    v3=(1-fR)*profil[iR*16*16+iG*16+(iB+1)].composante3+fR*profil[(iR+1)*16*16+iG*16+(iB+1)].composante3;
    v4=(1-fR)*profil[iR*16*16+(iG+1)*16+(iB+1)].composante3+fR*profil[(iR+1)*16*16+(iG+1)*16+(iB+1)].composante3;
    v12=(1-fG)*v1+fG*v2;
    v34=(1-fG)*v3+fG*v4;
    composantesTrouvees.composante3=(unsigned char)((1-fB)*v12+fB*v34);

    v1=(1-fR)*profil[iR*16*16+iG*16+iB].composante4+fR*profil[(iR+1)*16*16+iG*16+iB].composante4;
    v2=(1-fR)*profil[iR*16*16+(iG+1)*16+iB].composante4+fR*profil[(iR+1)*16*16+(iG+1)*16+iB].composante4;
    v3=(1-fR)*profil[iR*16*16+iG*16+(iB+1)].composante4+fR*profil[(iR+1)*16*16+iG*16+(iB+1)].composante4;
    v4=(1-fR)*profil[iR*16*16+(iG+1)*16+(iB+1)].composante4+fR*profil[(iR+1)*16*16+(iG+1)*16+(iB+1)].composante4;
    v12=(1-fG)*v1+fG*v2;
    v34=(1-fG)*v3+fG*v4;
    composantesTrouvees.composante4=(unsigned char)((1-fB)*v12+fB*v34);


    return composantesTrouvees;
}

int calculDistanceCouleur(RgbColor couleur1, RgbColor couleur2)
{
    return (couleur1.r-couleur2.r)*(couleur1.r-couleur2.r) //La distance est fausse car il n'y a pas la racine
                +(couleur1.g-couleur2.g)*(couleur1.g-couleur2.g) //mais comme on cherche un minimum on peut s'en passer
                +(couleur1.b-couleur2.b)*(couleur1.b-couleur2.b); //Divise le temps de calcul par 2
}

int rechercheMinimum(int *tableauDeFloats, int tailleTableau)
{
    int i=0;
    int positionMinimum=0;
    for (i = 0; i < tailleTableau; i++)
    {
            if (tableauDeFloats[i] < tableauDeFloats[positionMinimum])
                positionMinimum = i;
    }
        
    return positionMinimum;
}

RgbColor *simulerImpression1D(const unsigned char *composante1, const RgbColor couleurPapier, const RgbColor couleur1, const int tailleImage)
{
    float alpha=0;
    int i=0;
    RgbColor *imageSimulee=malloc(tailleImage*sizeof(RgbColor));

    if(imageSimulee==NULL)
    {
        printf("Erreur d'allocation memoire\n");
        exit(0);
    }
    for(i=0;i<tailleImage;i++)
    {
        
        alpha=(255.0-composante1[i])/255;

        imageSimulee[i].r=(unsigned char)(((((float)couleur1.r)*alpha+255.0*(1-alpha))*(float)couleurPapier.r)/255.0);
        imageSimulee[i].g=(unsigned char)(((((float)couleur1.g)*alpha+255.0*(1-alpha))*(float)couleurPapier.g)/255.0);
        imageSimulee[i].b=(unsigned char)(((((float)couleur1.b)*alpha+255.0*(1-alpha))*(float)couleurPapier.b)/255.0);
    }

    return imageSimulee;
}

RgbColor *simulerImpression2D(const unsigned char *composante1, const unsigned char *composante2, const RgbColor couleurPapier, const RgbColor couleur1, const RgbColor couleur2, const int tailleImage)
{
    float alpha[2]={0};
    int i=0;
    RgbColor *imageSimulee=malloc(tailleImage*sizeof(RgbColor));

    if(imageSimulee==NULL)
    {
        printf("Erreur d'allocation memoire\n");
        exit(0);
    }
    for(i=0;i<tailleImage;i++)
    {
        
        alpha[0]=(255.0-composante1[i])/255;
        alpha[1]=(255.0-composante2[i])/255;

        imageSimulee[i].r=(unsigned char)(((((float)couleur1.r)*alpha[0]+255.0*(1-alpha[0]))*(((float)couleur2.r)*alpha[1]+255.0*(1-alpha[1]))*(float)couleurPapier.r)/(255.0*255.0));
        imageSimulee[i].g=(unsigned char)(((((float)couleur1.g)*alpha[0]+255.0*(1-alpha[0]))*(((float)couleur2.g)*alpha[1]+255.0*(1-alpha[1]))*(float)couleurPapier.g)/(255.0*255.0));
        imageSimulee[i].b=(unsigned char)(((((float)couleur1.b)*alpha[0]+255.0*(1-alpha[0]))*(((float)couleur2.b)*alpha[1]+255.0*(1-alpha[1]))*(float)couleurPapier.b)/(255.0*255.0));
    }

    return imageSimulee;
}

RgbColor *simulerImpression3D(const unsigned char *composante1, const unsigned char *composante2, const unsigned char *composante3,const RgbColor couleurPapier, const RgbColor couleur1, const RgbColor couleur2, const RgbColor couleur3, const int tailleImage)
{
    float alpha[3]={0};
    int i=0;
    RgbColor *imageSimulee=malloc(tailleImage*sizeof(RgbColor));

    if(imageSimulee==NULL)
    {
        printf("Erreur d'allocation memoire\n");
        exit(0);
    }
    for(i=0;i<tailleImage;i++)
    {
        
        alpha[0]=(255.0-composante1[i])/255;
        alpha[1]=(255.0-composante2[i])/255;
        alpha[2]=(255.0-composante3[i])/255;

        imageSimulee[i].r=(unsigned char)(((float)couleur1.r*alpha[0]+255.0*(1-alpha[0]))*((float)couleur2.r*alpha[1]+255.0*(1-alpha[1]))*((float)couleur3.r*alpha[2]+255.0*(1-alpha[2]))*(float)couleurPapier.r/(255.0*255.0*255.0));
        imageSimulee[i].g=(unsigned char)(((float)couleur1.g*alpha[0]+255.0*(1-alpha[0]))*((float)couleur2.g*alpha[1]+255.0*(1-alpha[1]))*((float)couleur3.g*alpha[2]+255.0*(1-alpha[2]))*(float)couleurPapier.g/(255.0*255.0*255.0));
        imageSimulee[i].b=(unsigned char)(((float)couleur1.b*alpha[0]+255.0*(1-alpha[0]))*((float)couleur2.b*alpha[1]+255.0*(1-alpha[1]))*((float)couleur3.b*alpha[2]+255.0*(1-alpha[2]))*(float)couleurPapier.b/(255.0*255.0*255.0));
    }

    return imageSimulee;
}

RgbColor *simulerImpression4D(const unsigned char *composante1, const unsigned char *composante2, const unsigned char *composante3, const unsigned char *composante4,const RgbColor couleurPapier, const RgbColor couleur1, const RgbColor couleur2, const RgbColor couleur3, const RgbColor couleur4, const int tailleImage)
{
    float alpha[4]={0};
    int i=0;
    RgbColor *imageSimulee=malloc(tailleImage*sizeof(RgbColor));

    if(imageSimulee==NULL)
    {
        printf("Erreur d'allocation memoire\n");
        exit(0);
    }
    for(i=0;i<tailleImage;i++)
    {
        
        alpha[0]=(255.0-composante1[i])/255;
        alpha[1]=(255.0-composante2[i])/255;
        alpha[2]=(255.0-composante3[i])/255;
        alpha[3]=(255.0-composante4[i])/255;

        imageSimulee[i].r=(unsigned char)(((float)couleur1.r*alpha[0]+255.0*(1-alpha[0]))*((float)couleur2.r*alpha[1]+255.0*(1-alpha[1]))*((float)couleur3.r*alpha[2]+255.0*(1-alpha[2]))*((float)couleur4.r*alpha[3]+255.0*(1-alpha[3]))*(float)couleurPapier.r/(255.0*255.0*255.0*255));
        imageSimulee[i].g=(unsigned char)(((float)couleur1.g*alpha[0]+255.0*(1-alpha[0]))*((float)couleur2.g*alpha[1]+255.0*(1-alpha[1]))*((float)couleur3.g*alpha[2]+255.0*(1-alpha[2]))*((float)couleur4.g*alpha[3]+255.0*(1-alpha[3]))*(float)couleurPapier.g/(255.0*255.0*255.0*255));
        imageSimulee[i].b=(unsigned char)(((float)couleur1.b*alpha[0]+255.0*(1-alpha[0]))*((float)couleur2.b*alpha[1]+255.0*(1-alpha[1]))*((float)couleur3.b*alpha[2]+255.0*(1-alpha[2]))*((float)couleur4.b*alpha[3]+255.0*(1-alpha[3]))*(float)couleurPapier.b/(255.0*255.0*255.0*255));
    }

    return imageSimulee;
}