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
		
	if (argc == 2) {
		if(execlp("python", "python", "img_gen.py", "1", NULL) == -1)
			printf("Erreur execution python\n");
	} else {
		if(execlp("python", "python", "img_gen.py", "0", NULL) == -1)
			printf("Erreur execution python\n");
	}

	return EXIT_SUCCESS;
}
