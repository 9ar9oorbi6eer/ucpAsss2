#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include "linkedlist.h"
#include <string.h>
/* fix the problem, when the player p bumps into the car when it is coming like this <, the player goes on top of it and more cars are printed suddenly and the player doesnt lose*/

/* reading from the text files*/
int loadMapFromFile(int argc, char *argv[], char ***map, int *map_row, int *map_col) 
{
    int i, j, temp;


    if (argc != 2) 
    {
        printf("Incorrect argument format\n");
        printf("Correct usage is: ./traffic <textfile>\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) 
    {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }

    if (fscanf(file, "%d %d", map_row, map_col) != 2) 
    {
        printf("Error reading the dimensions from the file: %s\n", filename);
        fclose(file);
        return 1;
    }

    *map = malloc(*map_row * sizeof(char *));
    if (!*map) 
    {
        printf("Memory allocation failed for map rows.\n");
        fclose(file);
        return 1;
    }
    for (i = 0; i < *map_row; i++) 
    {
        (*map)[i] = malloc(*map_col * sizeof(char));
        if (!(*map)[i]) 
        {
            printf("Memory allocation failed for map columns at row %d.\n", i);
            fclose(file);
            return 1;
        }
    }

    for (i = 0; i < *map_row; i++) 
    {
        for (j = 0; j < *map_col; j++) 
        {
            if (fscanf(file, "%d", &temp) == 1) 
            {
                if (temp == 0) 
                {
                    if (i == 0 || i == *map_row - 1 || j == 0 || j == *map_col - 1) 
                    {
                        (*map)[i][j] = '*';
                    } else {
                        (*map)[i][j] = ' ';
                    }
                } else 
                {
                    switch (temp) 
                    {
                        case 1:
                            (*map)[i][j] = '.';
                            break;
                        case 2:
                            (*map)[i][j] = '>';
                            break;
                        case 3:
                            (*map)[i][j] = 'P';
                            break;
                        case 4:
                            (*map)[i][j] = 'G';
                            break;
                        default:
                            printf("Invalid value in the map at (%d, %d)\n", i, j);
                            fclose(file);
                            return 1;
                    }
                }
            } 
            else 
            {
                printf("Error reading the map values from the file: %s\n", filename);
                fclose(file);
                return 1;
            }
        }
    }


    fclose(file);


    for (i = 0; i < *map_row; i++) 
    {
        for (j = 0; j < *map_col; j++) 
        {
            printf("%c", (*map)[i][j]);
        }
        printf("\n");
    }


    return 0;
}


/* we will be using a struct to store the position of the car*/
void moveCar(char **map, int rows, int cols, int *x, int *y, char *direction) 
{
    int newX, newY, leftX, leftY, rightX, rightY;
    char nextTile, leftDir, rightDir;

    newX = *x;
    newY = *y;
    
    if (*direction == '^') newY--;
    if (*direction == '>') newX++;
    if (*direction == 'v') newY++;
    if (*direction == '<') newX--;

    if (newX >= 0 && newX < cols && newY >= 0 && newY < rows)
    {
        nextTile = map[newY][newX];
    }
    else
    {
        nextTile = ' ';
    }
    
    if (nextTile == '.' || nextTile == '>' || nextTile == 'P' || nextTile == 'G') 
    {
        *x = newX;
        *y = newY;
        return;
    }

    leftX = *x;
    leftY = *y;
    rightX = *x;
    rightY = *y;
    
    if (*direction == '^') 
    {
        leftX--; rightX++; 
        leftDir = '<'; rightDir = '>';
    }
    if (*direction == '>') 
    {
        leftY--; rightY++; 
        leftDir = '^'; rightDir = 'v';
    }
    if (*direction == 'v') 
    {
        leftX++; rightX--; 
        leftDir = '>'; rightDir = '<';
    }
    if (*direction == '<') 
    {
        leftY++; rightY--; 
        leftDir = 'v'; rightDir = '^';
    }

    if (leftX >= 0 && leftX < cols && leftY >= 0 && leftY < rows && map[leftY][leftX] == '.') 
    {
        *x = leftX;
        *y = leftY;
        *direction = leftDir;
        return;
    }

    if (rightX >= 0 && rightX < cols && rightY >= 0 && rightY < rows && map[rightY][rightX] == '.') 
    {
        *x = rightX;
        *y = rightY;
        *direction = rightDir;
        return;
    }
}

void movePlayer(Position *playerPos, int rows, int cols, char key, char **map, int* carX, int* carY, linkedlist_t *list) 
{
    int newX = playerPos->x, newY = playerPos->y;
    int i;

    if (key == 'w') newY--;
    if (key == 's') newY++;
    if (key == 'a') newX--;
    if (key == 'd') newX++;

    if (key == 'u') 
    {
        undoFunction(rows, cols, map, list);
        searchPlayer(playerPos, rows, cols, map);
        searchCar(carX, carY, rows, cols, map);
        return;
    }

    if (newX >= 0 && newX < cols && newY >= 0 && newY < rows && map[newY][newX] != '*') 
    {
        playerPos->x = newX;
        playerPos->y = newY;
    }


    if (key != 'u')
    {
        for(i = 0; i < rows; i++)
        {
            InsertLast(list, map[i], (sizeof(char) * cols));
        }
    }
}



void undoFunction(int rows, int cols, char **map, linkedlist_t *list)
{
	int i;
	char* data;

	for (i = rows-1; i >= 0; i--)
	{
		data = removeLast(list);
		if (data != NULL)
		{ memcpy(map[i], data, sizeof(char) * cols); }
		free(data);
	}
}

void searchPlayer(Position *playerPos, int rows, int cols, char **map)
{
    int i, j;

    for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			if (map[i][j] == 'P')  
            {
                playerPos->x = i; 
                playerPos->y = j; 
            } 
		}
	}
}

void searchCar(int* carX, int* carY, int rows, int cols, char **map)
{
    int i, j;

    for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			if (map[i][j] == '^' || map[i][j] == '>' || map[i][j] == '<' || map[i][j] == 'v')  
            {
                *carX = i; 
                *carY = j; 
            } 
		}
	}
}
