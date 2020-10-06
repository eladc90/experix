TARGET =testMain.out
CC	= gcc
CFLAGS = -ansi -g3 -pedantic  -I../include -I../../../basicDS/include/  -Wall -Werror

SRC_DIR =../src/
INC_DIR =../include/

DS_INC_DIR =../../../basicDS/include/
DS_SRC_DIR =../../../basicDS/src/


OBJS = Deck.o game.o hand.o player.o round.o table.o trick.o queue.o vector.o heap.o stratagy.o testMain.o ui.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
hand.o: $(SRC_DIR)hand.c $(INC_DIR)hand.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)hand.c

Deck.o: $(SRC_DIR)Deck.c $(INC_DIR)Deck.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)Deck.c 

trick.o: $(SRC_DIR)trick.c $(INC_DIR)trick.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)trick.c

player.o: $(SRC_DIR)player.c $(INC_DIR)player.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)player.c
    
queue.o: $(DS_SRC_DIR)queue.c $(DS_INC_DIR)queue.h
	$(CC) $(CFLAGS) -c $(DS_SRC_DIR)queue.c

vector.o: $(DS_SRC_DIR)vector.c $(DS_INC_DIR)vector.h
	$(CC) $(CFLAGS) -c $(DS_SRC_DIR)vector.c

heap.o: $(DS_SRC_DIR)heap.c $(DS_INC_DIR)heap.h
	$(CC) $(CFLAGS) -c $(DS_SRC_DIR)heap.c
    
round.o: $(SRC_DIR)round.c $(INC_DIR)Deck.h  $(INC_DIR)game.h  
	$(CC) $(CFLAGS) -c $(SRC_DIR)round.c

game.o: $(SRC_DIR)game.c 
	$(CC) $(CFLAGS) -c $(SRC_DIR)game.c

stratagy.o: $(SRC_DIR)stratagy.c $(INC_DIR)stratagy.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)stratagy.c

ui.o: $(SRC_DIR)ui.c $(INC_DIR)ui.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)ui.c

table.o: $(SRC_DIR)table.c $(INC_DIR)table.h $(DS_INC_DIR)queue.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)table.c
	
 


testMain.o: testMain.c 
	$(CC) $(CFLAGS) -c testMain.c


	
valgrind: $(TARGET)
	valgrind ./$(TARGET)
clean:
	rm -f $(TARGET) $(OBJS) 




