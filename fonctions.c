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

void save1D (double* tab, int nbCols) {
	FILE *fp = fopen("tmp.txt", "w");
	int i;
	
	fprintf(fp, "%d\n", nbCols);

	for (i=0; i<nbCols; i++)
		fprintf(fp, "%.2lf,", tab[i]);
	
	fprintf(fp, "%.2lf\n", tab[nbCols-1]);
	
	fclose(fp);
}

void save2D (double** tab, int nbLignes, int nbCols) {
	FILE *fp = fopen("tmp.txt", "w");
	int i, j;
	
	fprintf(fp, "%d,%d\n", nbLignes, nbCols);

	for (i=0; i<nbLignes; i++) {
		for (j=0; j<nbCols-1; j++)
			fprintf(fp, "%.2lf,", tab[i][j]);
		fprintf(fp, "%.2lf\n", tab[i][nbCols-1]);
	}
	
	fclose(fp);
}

double *init1D (char *fileName, int *nbCols) {
	double *tab;
	int i;
	*nbCols = 0;
	FILE *fp;
		
	printf("Ouverture de \"%s\"\n", fileName);
	
	fp = fopen(fileName, "r"); // read mode
	
	if (fp == NULL) {
		fprintf(stderr, "Erreur lors de l'ouverture de %s\n", fileName);
		exit(EXIT_FAILURE);
	}
	
	printf("Fichier \"%s\" ouvert\n", fileName);
	
	fscanf(fp, "%d\n", nbCols);
	
	if (*nbCols == 0) {
		fprintf(stderr, "Nombre de colonnes invalide\n");
		exit(EXIT_FAILURE);
	}
	
	tab = (double*) malloc(sizeof(double) * *nbCols);
	
	for (i=0; i<*nbCols; i++) 
		fscanf(fp, "%lf,", tab+i);
	
	fclose(fp);
	
	return tab;
}

double **init2D (char *fileName, int *nbLignes, int *nbCols) {
	double **tab;
	int i, j;
	FILE *fp;
		
	*nbCols = 0;
	*nbLignes = 1;
	
	printf("Ouverture de \"%s\"\n", fileName);

	fp = fopen(fileName, "r"); // read mode

	if (fp == NULL) {
		fprintf(stderr, "Erreur lors de l'ouverture de %s\n", fileName);
		exit(EXIT_FAILURE);
	}
	
	printf("Fichier \"%s\" ouvert\n", fileName);
	
	fscanf(fp, "%d,%d\n", nbCols, nbLignes);
	
	if (*nbCols == 0 || *nbLignes == 0) {
		fprintf(stderr, "Nombre de colonnes ou nbLignes invalide\n");
		exit(EXIT_FAILURE);
	}
	
	tab = (double**) malloc(sizeof(double*) * *nbLignes);
	for(i=0; i<*nbLignes; i++)
		tab[i] = (double *) malloc(sizeof(double) * *nbCols);

	for (i=0; i<*nbLignes; i++) {
		for (j=0; j<*nbCols; j++) 
			fscanf(fp, "%lf,", &tab[i][j]);
		fgetc(fp);
	}
	
	fclose(fp);
	
	return tab;
}

// tab must be initialized before calling these functions
void step1D (double* tab, int nbCols) {}
void step2D (double* tab, int nbLignes, int nbCols){}
