TARGET	= a.out
CC	= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include -Wall -Werror
OBJS 	=doublelink.o linkMain.o iterlist.o listFuncs.o

INC_DIR =../include/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
doublelink.o: doublelink.c $(INC_DIR)list.h liststruct.h
	$(CC) $(CFLAGS) -c doublelink.c

linkMain.o: linkMain.c $(INC_DIR)list.h liststruct.h doublelink.c
	$(CC) $(CFLAGS) -c linkMain.c

iterlist.o: iterlist.c $(INC_DIR)list.h $(INC_DIR)iter.h liststruct.h doublelink.c
	$(CC) $(CFLAGS) -c iterlist.c

listFuncs.o: listFuncs.c $(INC_DIR)listfunctions.h $(INC_DIR)iter.h doublelink.c $(INC_DIR)list.h
	$(CC) $(CFLAGS) -c listFuncs.c
	
valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 


