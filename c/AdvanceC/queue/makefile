TARGET	= a.out
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include -Wall -Werror
OBJS 	=queue.o queueMain.o

INC_DIR =../include/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
queue.o: queue.c $(INC_DIR)queue.h
	$(CC) $(CFLAGS) -c queue.c

queueMain.o: queueMain.c $(INC_DIR)queue.h queue.c
	$(CC) $(CFLAGS) -c queueMain.c
    	
valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 

