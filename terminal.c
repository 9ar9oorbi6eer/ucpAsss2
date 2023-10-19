#define _DEFAULT_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>


/* sleeping function*/
void newSleep(float sec)
{
	struct timespec ts;
	ts.tv_sec = (int) sec;
	ts.tv_nsec = (sec - ((int) sec)) * 1000000000;
	nanosleep(&ts,NULL);
}


/* this is for the buffer */
void disableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

void enableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

/* random number generator:*/
void initRandom()
{
    srand(time(NULL));
}
int randomUCP(int low, int high)
{
    int number = -1;

    if(low <= high)
    {
        number = (rand() % (high-low+1)) + low;
    }

    return number;
}

/* the instructions for the game as a function*/
void displayInstructions()
{
    printf("press w to move north\n");
    printf("press s to move south\n");
    printf("press a to move west\n");
    printf("press d to move east\n");
}

void clearScreen()
{
    system("clear");
}