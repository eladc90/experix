TARGET	= a.out
CC	= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include -Wall -Werror
OBJS 	= BSTTEST.o BST.o 
INC_DIR =../include/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
BSTTEST.o: BSTTEST.c $(INC_DIR)BinTree.h
	$(CC) $(CFLAGS) -c BSTTEST.c

BST.o: BST.c $(INC_DIR)BinTree.h BSTTEST.c
	$(CC) $(CFLAGS) -c BST.c
	
valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 


