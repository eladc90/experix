CC	= g++ 
CXX = $(CC)

CFLAGS = -ansi  -pedantic -Werror -Wall -fpic
CFLAGS += -g3

CPPFLAGS = $(addprefix -I,$(INC_DIR) $(INC_TEST_DIR))
CPPFLAGS += -MMD -MP

CXXFLAGS = $(CFLAGS) -std=c++03

LDFLAGS = -ldl
LDLIBS = -pthread

SOURCES = $(TARGET).cpp
SOURCES += $(wildcard $(SRC_DIR)/*.cpp)
SOURCES += $(wildcard $(SRC_TEST_DIR)/*.cpp)

OBJS = $(SOURCES:.cpp=.o)

TARGET = main

INC_DIR = ./include
SRC_DIR = ./source
INC_TEST_DIR = ./test/mvpTest/
SRC_TEST_DIR = ./test/src
TEST_DIR = test/mvpTest

DEPENDS = $(OBJS:%.o=%.d)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(SO_OBJS) $(LDLIBS) $(LDFLAGS)
	
all: $(TARGET)

check: $(TARGET)
	./$(TARGET) -v

valgrind:
	valgrind --leak-check=full ./$(TARGET)

clean: 
	rm -f $(OBJS) $(TARGET) $(DEPENDS)

-include $(DEPENDS)

.PHONY: clean check all valgrind