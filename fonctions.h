#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

#include <sys/time.h>
#include <stdint.h>

// Affiche une image representant la chaleur dans la matrice
void show (char* tab, int lignes, int cols);

// Initialise un tableau 1D a partir d'un fichier
char *init1D (char *fileName);

// Effectue une iteration de la propagation
void step1D (char* tab, int nbElem);
#endif
