#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"

int main(int argc, char** argv) {
	int lignes, cols;
	double **tab = init2D("test.txt", &lignes, &cols);
	
	save2D(tab, lignes, cols);

	return EXIT_SUCCESS;
}
