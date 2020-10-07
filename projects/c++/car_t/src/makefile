TARGET	= a.out
CC		= g++
CFLAGS	= -ansi -pedantic -g -I../include
OBJS 	= car_t.o  privat.o bus.o carMain.o 

INC_DIR = ../include/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
car_t.o: car_t.cpp $(INC_DIR)car_t.h
	$(CC) $(CFLAGS) -c car_t.cpp


privat.o: privat.cpp $(INC_DIR)private.h
	$(CC) $(CFLAGS) -c privat.cpp

bus.o: bus.cpp $(INC_DIR)bus.h
	$(CC) $(CFLAGS) -c bus.cpp

carMain.o: carMain.cpp $(INC_DIR)car_t.h
	$(CC) $(CFLAGS) -c carMain.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 


