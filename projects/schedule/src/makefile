# this is my target
TARGET = a.out
LIBS = DS

.PHONY: run clean gdb

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc

# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS =  -g 

# The debugger flags will be... ("LDFLAGS" is MAKE variable)
LDFLAGS = -g

# Include directory
INC_STS = ../include
INC_DS = ../../../c/AdvanceC/include
LIB_PATH= ../../../c/AdvanceC/lib
CFLAGS += -I$(INC_STS)
CFLAGS += -I$(INC_DS)

# All .c files in this directory are my sources
SOURCES =  Task.c STS.c time.c zlog.c Pqueue.c schedMain.c
LIB_SRC = 

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)
LIB_OBJ = $(LIB_SRC:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS) libs
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) -Wl,-rpath=$(LIB_PATH) -L$(LIB_PATH) -lDS 

libDS.a: $(LIB_OBJ) #let's link library files into a static library
	ar rcs $(LIB_PATH)/libDS.a $(LIB_OBJ)

# Built-in recipe for link("include" is MAKE command), include call "depends"

include depends

# Compile the sources, going over the c.files and create new file with list of the h.files that need to be included to each c.file.
# In the next time, if there where no changes in the h.files thet are needed, the depends file will be exist so the include will go to the file instead of build new one. 
depends:
	$(CC) -MM -I$(INC_STS) -I$(INC_DS) $(SOURCES) $(LIB_SRC) > depends

libs: mklib libDS.a

mklib:
	mkdir -p $(LIB_PATH)

clean:
	-rm $(TARGET) *.o depends

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)
	  
	
