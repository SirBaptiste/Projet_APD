#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

#include <sys/time.h>
#include <stdint.h>

// Affiche une image representant la chaleur dans la matrice 1D
void save1D (double* tab, int nbLignes, int duree);
// Affiche une image representant la chaleur dans la matrice 2D
void save2D (double** tab, int nbLignes, int nbCols, int duree);

// Initialise un tableau 1D a partir du fichier fileName
double *init1D (char *fileName, int *nbCols, int *duree, double *seuil);
// Initialise un tableau 2D a partir du fichier fileName
double **init2D (char *fileName, int *nbLignes, int *nbCols, int *duree, double *seuil);

// Effectue une iteration de la propagation sur matrice 1D
void step1D (double* tab, int nbCols);
// Effectue une iteration de la propagation sur matrice 2D
void step2D (double* tab, int nbLignes, int nbCols);
#endif
