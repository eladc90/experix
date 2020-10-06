TARGET	= a.out
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include -Wall -Werror
OBJS 	=vector.o mainVec.o

INC_DIR =../include/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
vector.o: vector.c $(INC_DIR)vector.h
	$(CC) $(CFLAGS) -c vector.c

mainVec.o: mainVec.c $(INC_DIR)vector.h vector.c
	$(CC) $(CFLAGS) -c mainVec.c
    	
valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 


