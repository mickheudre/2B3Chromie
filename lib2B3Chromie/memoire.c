#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

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

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
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
}


