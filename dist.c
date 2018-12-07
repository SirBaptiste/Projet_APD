#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "conway.h"

int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "Y A PAS LES ARGUMENTS C******");
		return EXIT_FAILURE;
	}

	char champion[][20] = {"TROU DU C**", "C*******", "PEDONCULE", "CHAMEAU CONSTIPE", "HANDICAPE"};

	int rang, nbProcess;
	int nbLignes, nbCol, nbIt, i, nbElem, tailleSousMat, offset, nbLignesRecues, j;
	char* tab;
	char* sousMat;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	MPI_Comm_size(MPI_COMM_WORLD, &nbProcess);
	
	nbLignes = atoi(argv[1]);
	nbCol = atoi(argv[2]);
	nbIt = atoi(argv[3]);
	
	if (nbLignes%nbProcess != 0){
		srand(time(NULL)+rang);
		fprintf(stderr, "%d EST PAS UN DIVISEUR DE %d %s\n", nbProcess, nbLignes, champion[rand()%5]);
		return EXIT_FAILURE;
	}
	
	nbElem = (int) nbCol*(nbLignes/nbProcess);
	
	if (rang != 0 && rang != nbProcess-1) {
		tailleSousMat = nbElem + 2*nbCol;
		nbLignesRecues = (int) nbElem/nbCol + 2;
	} else {
		tailleSousMat = nbElem + nbCol;
		nbLignesRecues = (int) nbElem/nbCol + 1;
	}

	sousMat = (char*) malloc(sizeof(char) * tailleSousMat);
	
	if (rang==0)
		tab = init(nbLignes, nbCol, 0.33);
	
	for (j=0; j<nbIt; j++) {	
		if (rang == 0) {	
			// Envoi des sous matrices
			for (i=0; i<nbProcess; i++) {
				// Ps 0
				if (i==0)
					MPI_Send(tab, nbElem+nbCol, MPI_CHAR, i, 0, MPI_COMM_WORLD);
				else if (i != nbProcess -1)
					MPI_Send(tab + i*nbElem - nbCol, nbElem+nbCol*2, MPI_CHAR, i, 0, MPI_COMM_WORLD);
				// Dernier Ps
				else
					MPI_Send(tab + i*nbElem - nbCol, nbElem+nbCol, MPI_CHAR, i, 0, MPI_COMM_WORLD);
			}
		}
	
		MPI_Recv(sousMat, tailleSousMat, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
		// Iteration
		game(sousMat, nbLignesRecues, nbCol);
	
		// Regroupement des sous matrices à root
		offset = (rang==0)? 0:nbCol;
		MPI_Gather(sousMat+offset, nbElem, MPI_CHAR, tab, nbElem, MPI_CHAR, 0, MPI_COMM_WORLD);
		if (rang == 0){
			show(tab, nbLignes, nbCol);
			usleep(100000);
			system("clear");
		}
	}
		
	if (rang == 0)
		show(tab, nbLignes, nbCol);

	MPI_Finalize();
	return EXIT_SUCCESS;
}
