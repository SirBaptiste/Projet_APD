#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "fonctions.h"
#include <time.h>

int main(int argc, char** argv) {
	int nbLignes, nbCol,rang,nbProcess,offset,nbElem;
	int duree, i,j, tailleSousMat,nbLignesRecues;
	double seuil;
	//lecture des données saisies par l'utilisateur
	double *tab,*sousMat;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	MPI_Comm_size(MPI_COMM_WORLD, &nbProcess);

	//Verif taille tab avec nb proc
	if(nbLignes%nbProcess != 0){
		srand(time(NULL)+rang);
		fprintf(stderr, "%d EST PAS UN DIVISEUR DE %d\n", nbProcess, nbLignes);
		return EXIT_FAILURE;
	}


	if (rang==0)
	{
		tab  = init2D("tmp.txt", &nbLignes, &nbCol, &duree, &seuil);
		
	}
	MPI_Bcast(&nbLignes,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&nbCol,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&duree,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&seuil,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

	nbElem = (int) nbCol*(nbLignes/nbProcess);
	
	if (rang != 0 && rang != nbProcess-1) {
		tailleSousMat = nbElem + 2*nbCol;
		nbLignesRecues = (int) nbElem/nbCol + 2;
	} else {
		tailleSousMat = nbElem + nbCol;
		nbLignesRecues = (int) nbElem/nbCol + 1;
	}

	sousMat = (double*) malloc(sizeof(double) * tailleSousMat);
	
	
	
	for(j=0; j<duree; j++) {	
		if(rang == 0) {	
			// Envoi des sous matrices
			for(i=0; i<nbProcess; i++) {
				// Ps 0
				if (i==0)
					MPI_Send(tab, nbElem+nbCol, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
				else if (i != nbProcess -1)
					MPI_Send(tab + (i*nbElem - nbCol), nbElem+nbCol*2, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
				// Dernier Ps
				else
					MPI_Send(tab + i*nbElem - nbCol, nbElem+nbCol, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			}
		}
	
		MPI_Recv(sousMat, tailleSousMat, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
		// Iteration
		Calcul_Temp_2d(sousMat, nbLignesRecues, nbCol,seuil); 
	
		// Regroupement des sous matrices à root
		offset = (rang==0)? 0:nbCol;
		MPI_Gather(sousMat+offset, nbElem, MPI_DOUBLE, tab, nbElem, MPI_CHAR, 0, MPI_COMM_WORLD);
		if(rang == 0){
			//Enregistrement de la matrice 2D
			save2D(tab, nbLignes, nbCol, duree);
		}
	}

	//Enregistre les images 	
	if (argc == 2) {
		if(execlp("python", "python", "img_gen.py", "1", NULL) == -1)
			printf("Erreur execution python\n");
	} 
	//N'enregistre pas les images	
	else {
		if(execlp("python", "python", "img_gen.py", "0", NULL) == -1)
			printf("Erreur execution python\n");
	}
	
	MPI_Finalize();
	return EXIT_SUCCESS;
}
