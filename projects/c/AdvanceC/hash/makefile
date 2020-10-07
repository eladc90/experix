TARGET	= a.out
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include/ -I../LinkList/ -Wall -Werror
OBJS 	= hash.o hashMain.o

INC_DIR =../include/
SRC_DIR =../LinkList/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
hash.o: hash.c $(INC_DIR)HashMap.h
	$(CC) $(CFLAGS) -c hash.c

hashMain.o: hashMain.c $(INC_DIR)HashMap.h
	$(CC) $(CFLAGS) -c hashMain.c

doublelink.o: $(SRC_DIR)doublelink.c $(INC_DIR)list.h liststruct.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)doublelink.c

iterlist.o: $(SRC_DIR)iterlist.c $(INC_DIR)list.h $(INC_DIR)iter.h liststruct.h $(SRC_DIR)doublelink.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)iterlist.c

listFuncs.o: $(SRC_DIR)listFuncs.c $(INC_DIR)listfunctions.h $(INC_DIR)iter.h $(SRC_DIR)doublelink.c $(INC_DIR)list.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)listFuncs.c
	
    	
valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 
