TARGET	= a.out
CC		= gcc
CFLAGS	= -g -I../include -I../vector/ 
OBJS 	= heap.o vector.o heapMain.o

INC_DIR =../include/
SRC_DIR =../vector/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
heap.o: heap.c $(INC_DIR)heap.h
	$(CC) $(CFLAGS) -c heap.c

heapMain.o: heapMain.c $(INC_DIR)heap.h
	$(CC) $(CFLAGS) -c heapMain.c

vector.o: $(SRC_DIR)vector.c $(INC_DIR)vector.h 
	$(CC) $(CFLAGS) -c $(SRC_DIR)vector.c
		
valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 


