TARGET	= a.out
CC		= g++
CFLAGS	= -ansi -pedantic -g -I../include/
OBJS 	= MainIO.o

INC_DIR = ../include/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

	
memTest.o: MainIO.cpp  virtIO_t.h asciiIO_t.h binIO_t.h
	$(CC) $(CFLAGS) -c MainIO.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 


