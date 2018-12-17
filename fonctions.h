#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

#include <sys/time.h>
#include <stdint.h>
#include <mpi.h>

// Affiche une image representant la chaleur dans la matrice 1D
void save1D (double* tab, int nbLignes, int duree);
// Affiche une image representant la chaleur dans la matrice 2D
void save2D (double* tab, int nbLignes, int nbCols, int duree);

// Initialise un tableau 1D a partir du fichier fileName
double *init1D (char *fileName, int *nbCols, int *duree, double *seuil);
// Initialise un tableau 2D a partir du fichier fileName
double *init2D (char *fileName, int *nbLignes, int *nbCols, int *duree, double *seuil);

void Calcul_Temp_1d(double *tab, int tailleLigne, int duree, double seuil_temp);

void Calcul_Temp_2d(double *tab,int nbLigne, int tailleLigne,double seuil_temp);

void show_tab(double *tab,int nbLigne, int tailleLigne);

void show_tab_1d(double *tab, int tailleLigne);


#endif
