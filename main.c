#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "fonctions.h"

int main(int argc, char** argv) {
	int lignes, cols;
	int duree, i;
	double seuil;
	double **tab = init2D("tmp.txt", &lignes, &cols, &duree, &seuil);
	
	for (i=0; i<duree; i++)
		save2D(tab, lignes, cols, duree);
		
	if (argc == 2)
		execlp("img_gen.py", "1", NULL);
	else
		execlp("img_gen.py", "0", NULL);

	return EXIT_SUCCESS;
}
