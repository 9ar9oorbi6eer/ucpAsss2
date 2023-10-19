CC = gcc
CFLAGS = -Wall -pedantic -ansi
OBJ = Main.o functions.o terminal.o linkedlist.o
EXEC = traffic

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

Main.o : Main.c functions.h terminal.h linkedlist.h
	$(CC) -c Main.c $(CFLAGS)

functions.o : functions.c functions.h linkedlist.h
	$(CC) -c functions.c $(CFLAGS)

terminal.o : terminal.c terminal.h
	$(CC) -c terminal.c $(CFLAGS)

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) -c linkedlist.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)
