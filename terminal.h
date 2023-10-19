#ifndef TERMINAL_H
#define TERMINAL_H

/* sleeping: */
void newSleep(float sec);

/* buffer for terminal*/
void disableBuffer();

void enableBuffer();

/* this is from random.c*/
void initRandom();

int randomUCP(int low, int high);

/* game instructions*/
void displayInstructions();

void clearScreen();

#endif


