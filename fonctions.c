// Authors: Anthony LEJA, Baptiste GUILLEMOT, Stefan ROSSE

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <ctype.h>

#include "fonctions.h"

#define NUM_SIZE 5

void show (double* tab, int lignes, int cols) {
	
}

double *init1D (char *fileName) {
	double *tab;
	int i, nbCols = 0;
	FILE *fp;
		
	printf("Ouverture de %s\n", fileName);
	
	fp = fopen(fileName, "r"); // read mode
	
	if (fp == NULL) {
		fprintf(stderr, "Erreur lors de l'ouverture de %s\n", fileName);
		exit(EXIT_FAILURE);
	}
	
	printf("Fichier %s ouvert\n", fileName);
	
	fscanf(fp, "%d\n", &nbCols);
	
	if (nbCols == 0) {
		fprintf(stderr, "Nombre de colonnes invalide\n");
		exit(EXIT_FAILURE);
	}
	
	tab = (double*) malloc(sizeof(double) * nbCols);
	
	for (i=0; i<nbCols; i++) 
		fscanf(fp, "%lf,", tab+i);
	
	fclose(fp);
	
	return tab;
}

// tab must be initialized before calling this function.
void step1D (double* tab, int nbElem) {

}
