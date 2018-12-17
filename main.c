#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"

int main(int argc, char** argv) {
	int lignes, cols;
	int duree, i;
	double seuil;
	double **tab = init2D("tmp.txt", &lignes, &cols, &duree, &seuil);
	
	for (i=0; i<duree; i++)
		save2D(tab, lignes, cols, duree);

	return EXIT_SUCCESS;
}
