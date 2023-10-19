#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "linkedlist.h"


/* struct for storing player movment*/
typedef struct {
    int x;
    int y;
} Position;


/* this is to read from the text file*/
int loadMapFromFile(int argc, char *argv[], char ***map, int *map_row, int *map_col);

/* moving the cars*/
void moveCar(char **map, int rows, int cols, int *x, int *y, char *direction);

/* this is to move the player (P)*/
void movePlayer(Position *playerPos, int rows, int cols, char key, char **map, int* carX, int* carY, linkedlist_t *list); 

/* this is to undo the previous move of the player and the car */
void undoFunction(int rows, int cols, char **map, linkedlist_t *list);

/* this searches for the player position in the map */
void searchPlayer(Position *playerPos, int rows, int cols, char **map);

/* this searches for the car position in the map */
void searchCar(int* carX, int* carY, int rows, int cols, char **map);

#endif