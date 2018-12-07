#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

#include <sys/time.h>
#include <stdint.h>

// Affiche une image representant la chaleur dans la matrice
void show (double* tab, int lignes, int cols);

// Initialise un tableau 1D a partir d'un fichier
double *init1D (char *fileName);

// Effectue une iteration de la propagation
void step1D (double* tab, int nbElem);
#endif
