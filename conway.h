#ifndef _CONWAY_H_
#define _CONWAY_H_

#include <sys/time.h>
#include <stdint.h>

// A good choice for your experiments :)
#define DEFAULT_DENSITY  0.25

// Prints out the game board
void show (char* tab, int m, int n);

// Allocates and randomly initializes a game board, 
// density (from 0 to 1) indicates the density of cells initially alive
char *init (int m, int n, double density);

/* Starts with a reversed U that may leads to a clown after 110 iterations
 * if m and n >=40 */
char *initClown(int m, int n);

/* Plays one iteration of the game, updating the board 'tab' */
void game (char* tab, int m, int n);
#endif
