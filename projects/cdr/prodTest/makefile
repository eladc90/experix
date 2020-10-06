
TARGET	= a.out
CPP		= g++ -pthread
CFLAGS	= -ansi -g3 -pedantic -I../inc/
OBJS 	= tcp_producer.o tcp_producer_test.o i_channel.o

INC_SRC = ../src/
INC_DIR = ../inc/
 
$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

tcp_producer.o: tcp_producer.cpp tcp_producer.hpp 
	$(CPP) $(CFLAGS) -c tcp_producer.cpp

tcp_producer_test.o: tcp_producer_test.cpp tcp_producer.hpp
	$(CPP) $(CFLAGS) -c tcp_producer_test.cpp

i_channel.o: $(INC_SRC)i_channel.cpp $(INC_DIR)i_channel.hpp
	$(CPP) $(CFLAGS) -c $(INC_SRC)i_channel.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

