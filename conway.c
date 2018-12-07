// Authors: Camille Coti, Franck Butelle, Cesar Rodriguez

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

#include "conway.h"

void
show (char *tab, int m, int n) {
	int i, j;

	printf ("  ");
	for (j = 0; j < n; j++)
		if ((j % 2) == 0)
			printf ("%02d", j);
		else
			printf ("  ");
	printf ("\n");

	for (i = 0; i < m; i++) {
		printf ("%02d", i);
		for (j = 0; j < n; j++) {
			if (0 == tab[i * n + j]) {
				printf ("  ");
			} else {
				printf ("\342\226\210");	// plain block utf8
				printf ("\342\226\212");	// left 3/4 block
			}
		}
		printf ("\n");
	}
	printf ("\n");
}

char *
init (int m, int n, double density) {
	char *espace;
	int i;
	float nb;

	assert (density >= 0);
	assert (density <= 1);

	// allocate and init with zeros.
	espace = calloc (m * n, sizeof (char));

	if (espace == NULL) {
		fprintf (stderr, "array of %lu bytes, may be too much\n",
				 m * n * sizeof (char));
		exit (1);
	}

	for (i = 0; i < m * n; i++) {
		nb = (double) rand () / (RAND_MAX + 1.0);
		if (nb < density)
			espace[i] = 1;
		else
			espace[i] = 0;
	}
	return espace;
}

/* macro to convert from cartesian coordinates to linear 1 dim array */
#define MAT(tab,i,j)  tab[i+(j)*n]


/* The starting position of the clown is a reversed U.
 * it needs at least m and n >=40 and exactly 110 iterations*/
char *
initClown (int m, int n) {
	int i = m / 2 -2, j = n / 2 +3;
	char *tab;

	tab = calloc (m * n, sizeof (char));
	if (tab == NULL) {
		fprintf (stderr, "array of %lu bytes, may be too much\n",
				 m * n * sizeof (char));
		exit (1);
	}

	MAT (tab, i - 1, j - 1) = 1;
	MAT (tab, i, j - 1) = 1;
	MAT (tab, i + 1, j - 1) = 1;
	MAT (tab, i + 1, j) = 1;
	MAT (tab, i - 1, j) = 1;
	MAT (tab, i + 1, j + 1) = 1;
	MAT (tab, i - 1, j + 1) = 1;

	return(tab);
}

/* tab must be initialized before calling this function. m lines, n rows */
void
game (char *tab, int m, int n) {
	int i, j;
	int nb_neighbors;

/* simple local functions to simplify writing of the following function game,
 * sides are considered as dead cells. */
	int UP(int i, int j)      {return((j>0) ? MAT(tab,i,j-1) : 0);}
	int DOWN(int i,int j)     {return((j<m-1) ? MAT(tab,i,j+1) : 0);}
	int RIGHT(int i,int j)    {return((i<n-1) ? MAT(tab,i+1,j) : 0);}
	int LEFT(int i,int j)     {return((i>0) ? MAT(tab,i-1,j) : 0);}
	int LEFTUP(int i,int j)   {return((i>0) && (j>0) ? MAT(tab,i-1,j-1) : 0);}	
	int RIGHTUP(int i,int j)  {return((i<n-1) && (j>0) ? MAT(tab,i+1,j-1) : 0);}
	int LEFTDOWN(int i,int j) {return((i>0) && (j<m-1) ? MAT(tab,i-1,j+1) : 0);}
	int RIGHTDOWN(int i,int j){return((i<n-1) && (j<n-1) ? MAT(tab,i+1,j+1) : 0);}

	// static to get rid of multiple allocation of tmp
	static char *tmp = NULL;
	if (tmp == NULL)
		tmp = malloc (m * n * sizeof (char));

	for (j = 0; j < m; j++) {
		for (i = 0; i < n; i++) {
			/* count number of living neighbors of cell i, j:
			 * since a cell is 1 if living and 0 if dead, it is just a sum.*/
			nb_neighbors = UP (i, j) + DOWN (i, j) 
					+ LEFT (i, j) + RIGHT (i, j)
					+ LEFTUP (i, j) + RIGHTUP (i, j) 
					+ LEFTDOWN (i, j) + RIGHTDOWN (i, j);

			/* more than 3 neighbors or less than 2 : die, exactly 3: born,
			 * exactly 2 : do not change */
			MAT (tmp, i, j) = (nb_neighbors == 3) || (nb_neighbors == 2
							  && MAT (tab, i, j) == 1);
		}
	}

	memcpy (tab, tmp, m * n * sizeof (char));
}
