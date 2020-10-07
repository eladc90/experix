SERVER_TARGET	= ser.out
CLIENT_TARGET	= cli.out

CC	= gcc
CFLAGS	= -g -ansi -pedantic -I../inc/ 
SERVER_OBJS		=  serverNetwork.o serverManager.o userDB.o userManager.o serverMain.o hashmap.o queue.o groupMng.o
CLIENT_OBJS 	=  clientManager.o clientNetwork.o ui.o clientMain.o chatMan.o hashmap.o

OBJS = protocol.o 
INC_DIR =../inc/
LIB_PATH = ../inc/

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_OBJS) $(OBJS)
	$(CC) -o $(SERVER_TARGET) $(SERVER_OBJS) $(OBJS) -L../inc -lList

$(CLIENT_TARGET): $(CLIENT_OBJS) $(OBJS)
	$(CC) -o $(CLIENT_TARGET) $(CLIENT_OBJS) $(OBJS) -L../inc -lList

serverMain.o: serverMain.c 
	$(CC) $(CFLAGS) -c serverMain.c

clientMain.o: clientMain.c 
	$(CC) $(CFLAGS) -c clientMain.c

clientManager.o: clientManager.c $(INC_DIR)clientManager.h
	$(CC) $(CFLAGS) -c clientManager.c

clientNetwork.o: clientNetwork.c $(INC_DIR)clientNetwork.h
	$(CC) $(CFLAGS) -c clientNetwork.c

protocol.o: protocol.c $(INC_DIR)chatProtocol.h $(INC_DIR)ChatProtocolLimits.h
	$(CC) $(CFLAGS) -c protocol.c

userManager.o: userManager.c $(INC_DIR)userManager.h 
	$(CC) $(CFLAGS) -c userManager.c

userDB.o: userDB.c $(INC_DIR)userDB.h $(INC_DIR)hashmap.h 
	$(CC) $(CFLAGS) -c userDB.c

hashmap.o: hashmap.c $(INC_DIR)hashmap.h  $(LIB_PATH)libList.a
	$(CC) $(CFLAGS) -c hashmap.c 
	
ui.o: ui.c $(INC_DIR)ui.h 
	$(CC) $(CFLAGS) -c ui.c

serverNetwork.o: serverNetwork.c $(INC_DIR)serverNetwork.h 
	$(CC) $(CFLAGS) -c serverNetwork.c

serverManager.o: serverManager.c $(INC_DIR)serverManager.h 
	$(CC) $(CFLAGS) -c serverManager.c

groupMng.o: groupMng.c $(INC_DIR)groupMng.h 
	$(CC) $(CFLAGS) -c groupMng.c

queue.o: queue.c $(INC_DIR)queue.h 
	$(CC) $(CFLAGS) -c queue.c

chatMan.o: chatMan.c $(INC_DIR)chatMan.h $(INC_DIR)hashmap.h $(LIB_PATH)libList.a hashmap.c 
	$(CC) $(CFLAGS) -c chatMan.c


chatWrite.o: chatWrite.c 
	$(CC) $(CFLAGS) -c chatWrite.c

chatRead.o: chatRead.c 
	$(CC) $(CFLAGS) -c chatRead.c



valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) *.o *.out


