TARGET	= a.out
CC		= gcc
CFLAGS	= -fPIC -Wall -c -I../include
OBJS 	= vector.o heap.o queue.o BST.o doublelink.o iterlist.o listFuncs.o

INC_DIR =../include/
SRC_DIR = ../

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

heap.o: $(SRC_DIR)heap/heap.c $(INC_DIR)heap.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)heap/heap.c

vector.o: $(SRC_DIR)vector/vector.c $(INC_DIR)vector.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)vector/vector.c

queue.o: $(SRC_DIR)queue/queue.c $(INC_DIR)queue.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)queue/queue.c

BST.o: $(SRC_DIR)tree/BST.c $(INC_DIR)BinTree.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)tree/BST.c
	
doublelink.o: $(SRC_DIR)linklist/doublelink.c $(INC_DIR)list.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)linklist/doublelink.c
	
iterlist.o: $(SRC_DIR)linklist/iterlist.c $(INC_DIR)iter.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)linklist/iterlist.c
	
listFuncs.o: $(SRC_DIR)linklist/listFuncs.c $(INC_DIR)listfunctions.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)linklist/listFuncs.c
	

   	
valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 


