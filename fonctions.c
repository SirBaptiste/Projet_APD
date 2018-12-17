// Authors: Anthony LEJA, Baptiste GUILLEMOT, Stefan ROSSE

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>

#include "fonctions.h"

#define NUM_SIZE 5
#define COLSEPARATOR ";"
#define LINESEPARATOR "\n"

void save1D (double* tab, int nbCols, int duree) {
	FILE *fp = fopen("out.txt", "a");
	int i;

	fprintf(fp, "%d\n", nbCols);

	for (i=0; i<nbCols; i++)
		fprintf(fp, "%.2lf;", tab[i]);
	
	fprintf(fp, "%.2lf;", tab[nbCols-1]);
	
	fclose(fp);
}

void save2D (double* tab, int nbLignes, int nbCols, int duree) {
	int existed = access("out.txt", F_OK);
	FILE *fp = fopen("out.txt", "a");
	int i,j=0;
	
	if(existed == -1) // Fichier cree
		fprintf(fp, "%d\n%d;%d\n", duree, nbLignes, nbCols);

	for (i=0; i<nbLignes * nbCols; i++) {
		j++;
		fprintf(fp, "%.2lf", tab[i]);
		if(j == nbCols)
		{
			fprintf(fp, "\n");
			j=0;
		} else
			fprintf(fp, ";");
	}
	
	fclose(fp);
}

double *init1D (char *fileName, int *nbCols, int *duree, double *seuil) {
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
	
	fscanf(fp, "%d\n%d\n%lf\n", nbCols, duree, seuil);
	
	if (*nbCols == 0) {
		fprintf(stderr, "Nombre de colonnes invalide\n");
		exit(EXIT_FAILURE);
	}
	
	tab = (double*) malloc(sizeof(double) * *nbCols);
	
	for (i=0; i<*nbCols; i++) 
		fscanf(fp, "%lf;", tab+i);
	
	fclose(fp);
	
	return tab;
}

double *init2D (char *fileName, int *nbLignes, int *nbCols, int *duree, double *seuil) {
	double *tab;
	int i;
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
	
	fscanf(fp, "%d;%d\n%d\n%lf\n", nbLignes, nbCols, duree, seuil);
	
	if (*nbCols == 0 || *nbLignes == 0) {
		fprintf(stderr, "Nombre de colonnes ou nbLignes invalide\n");
		exit(EXIT_FAILURE);
	}
	
	tab = (double*) malloc(sizeof(double) * *nbLignes * *nbCols);
	

	for (i=0; i<*nbLignes * *nbCols; i++) {
		fscanf(fp, "%lf;", &tab[i]);
		//if(i%*nbLignes ==0)		
			//fgetc(fp);
	}
	
	fclose(fp);
	
	return tab;
}

//Calcul de la repartission de la chaleur pour une matrice 1D

void Calcul_Temp_1d(double *tab, int tailleLigne, int duree, double seuil_temp)
{
	int i,j;
	double* tmp_tab;
	double tmp;
	tmp_tab = (double *) malloc(sizeof(double) * tailleLigne);

	//Boucle de calcul des valeurs pour un instant j
	for(j=0;j<duree;j++)
	{			
			//Calcul de la valeur pour un point i
			for(i=1;i<tailleLigne-1;i++)
			{		
				tmp = (tab[i-1]+4*tab[i]+tab[i+1] );
				tmp_tab[i] = tmp ;
			}
			
			tmp_tab[0] = (4* tab[0] + 2*tab[1])/6;
			tmp_tab[tailleLigne-1] = (4* tab[tailleLigne-1] + 2*tab[tailleLigne-2])/6;
			
			//Affectation des valeurs
			for(i=1;i<tailleLigne-1;i++)
			{
				tmp = (tmp_tab[i])/6;
				
				if(tmp > seuil_temp)
					tab[i] = tmp;
				else
					tab[i] = seuil_temp;
			}	

	}
}


//Calcul de la repartission de la chaleur pour une matrice 2D
void Calcul_Temp_2d(double *tab, int nbLigne, int tailleLigne, double seuil_temp) {
	double *tmp_tab;
	int i,j;
	double tmp;
	
	tmp_tab = (double *) malloc(sizeof(double) * tailleLigne*nbLigne);
	
	//init tab temp
	for(i=0;i<tailleLigne*nbLigne;i++)
		tmp_tab[i] = seuil_temp;

	//diffusion
		//diffusion selon J
		for(i=0;i<nbLigne;i++) {
			for(j=1;j<tailleLigne-1;j++) {
				//Somme sur les valeurs horizontales
				tmp = tab[(j-1)+(i)*tailleLigne]+4*tab[j+(i)*tailleLigne]+tab[(j+1)+(i)*tailleLigne];

				tmp_tab[j+i*tailleLigne] = tmp;
			}
		}

		//Recopie du tableau
		for(i=0;i<nbLigne;i++) {
			for(j=1;j<tailleLigne-1;j++)
				tab[i*tailleLigne+j] = tmp_tab[i*tailleLigne+j]/6;
		}

		//diffusion selon I
		for(i=1;i<nbLigne-1;i++) {
			for(j=0;j<tailleLigne;j++) {
				//Somme sur les valeurs horizontales
				tmp = tab[(j)+(i-1)*tailleLigne]+4*tab[j+(i)*tailleLigne]+tab[(j)+(i+1)*tailleLigne];
				tmp_tab[j+(i)*tailleLigne]=tmp;	
			}
		}

		//Recopie du tableau
		for(i=1;i<nbLigne-1;i++) {
			for(j=0;j<tailleLigne;j++)
				tab[i*tailleLigne+j] = tmp_tab[i*tailleLigne+j]/6;
		}
		

}
//Affichage de la matrice (uniquement pour les tests)
void show_tab(double *tab,int nbLigne, int tailleLigne) {
	int i,j;
	for(i=0;i<nbLigne;i++) {
		for(j=0;j<tailleLigne;j++)
			printf("|%lf",tab[j+i*tailleLigne]);

		printf("\n");

	}

}


void show_tab_1d(double *tab, int tailleLigne) {
	int i;
	for(i=0;i<tailleLigne;i++)
		printf("%lf\n",tab[i]);
}




