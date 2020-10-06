TARGET	= a.out
CC		= g++
CFLAGS	= -ansi -pedantic -g -I../include/
OBJS 	= memManager_t.o memPage_t.o memPool_t.o memTest.o

INC_DIR = ../include/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
memManager_t.o: memManager_t.cpp $(INC_DIR)memManager_t.h
	$(CC) $(CFLAGS) -c memManager_t.cpp

memPage_t.o: memPage_t.cpp $(INC_DIR)memPage_t.h 
	$(CC) $(CFLAGS) -c memPage_t.cpp

memPool_t.o: memPool_t.cpp $(INC_DIR)memPool_t.h 
	$(CC) $(CFLAGS) -c memPool_t.cpp
	
memTest.o: memTest.cpp  $(INC_DIR)memPool_t.h $(INC_DIR)memPage_t.h $(INC_DIR)memManager_t.h
	$(CC) $(CFLAGS) -c memTest.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 


