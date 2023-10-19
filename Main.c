#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "terminal.h"
#include "linkedlist.h"

int main(int argc, char *argv[]) 
{
    int i, j, lastPlayerX, lastPlayerY;
    char **map;
    int map_row, map_col;
    int x = -1, y = -1;  /* Car's position */
    char direction = ' '; 
    int px = -1, py = -1; /* Player's position */
    char LastTile = ' ';
    Position playerPos;
    playerPos.x = -1;
    playerPos.y = -1;
    linkedlist_t* list = InitLinkedList();


    if (loadMapFromFile(argc, argv, &map, &map_row, &map_col) != 0) 
    {
        return 1;  
    }

    for (i = 0; i < map_row; i++) 
    {
        for (j = 0; j < map_col; j++) 
        {
            if (map[i][j] == '>') 
            {  
                x = j;
                y = i;
                direction = '>';  
            } else if (map[i][j] == 'P') 
            {
                playerPos.x = j;
                playerPos.y = i;
            }
        }

        if (px != -1 && py != -1 && x != -1 && y != -1) 
        {  
            break;
        }
    }

    if (playerPos.x == -1 || playerPos.y == -1) 
    {
        printf("Position of player not found on the map!\n");
        return 1;
    }

    displayInstructions();
    disableBuffer();


    clearScreen();
    while (1) 
    {
        char key = getchar();
        if (key == 'q') 
        {
            break;
        }

        /* Clear the screen before printing the updated map */
        clearScreen();


        lastPlayerX = playerPos.x;
        lastPlayerY = playerPos.y;

        movePlayer(&playerPos, map_row, map_col, key, map, &x, &y, list);  
        map[lastPlayerY][lastPlayerX] = LastTile;
        LastTile = map[playerPos.y][playerPos.x];
        map[playerPos.y][playerPos.x] = 'P';






        /* Update car */
        map[y][x] = '.';
        moveCar(map, map_row, map_col, &x, &y, &direction);
        map[y][x] = direction;

        /* Check for win/lose conditions */
        if (playerPos.x == x && playerPos.y == y) 
        {
            printf("You lost!\n");
            break;
        }

        if (LastTile == 'G') 
        {
            printf("You won!\n");
            break;
        }

        /* Refresh display */
        for (i = 0; i < map_row; i++) 
        {
            for (j = 0; j < map_col; j++) 
            {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
