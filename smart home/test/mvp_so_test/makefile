CC	= g++ 
CXX = $(CC)

CFLAGS = -ansi  -pedantic -Werror -Wall -fpic
CFLAGS += -g3 

CPPFLAGS = $(addprefix -I,$(INC_DIR) $(SRC_DIR) $(SO_DIR))
CPPFLAGS += -MMD 

CXXFLAGS = $(CFLAGS) -std=c++03 
SO_FLAGS = -shared
LDFLAGS = -ldl
LDLIBS = -pthread 

SOURCES = $(TARGET).cpp
SOURCES += $(wildcard ../../source/*.cpp)


SO_SOURCES = $(wildcard ../../so/*.cpp)

OBJS = $(SOURCES:.cpp=.o)
SO_OBJS = $(SO_DIR)extern.o $(SO_DIR)fire_sensor.o $(SO_DIR)sprinkel_controller.o $(SO_DIR)door_controller_2_floor.o

TARGET = mvp_so_test
SO_TARGET = lib_controllers.so


INC_DIR = ../../include
SRC_DIR = ../../source
SO_DIR = ../../so/

DEPENDS = $(OBJS:%.o=%.d)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(SO_TARGET): $(SO_OBJS)
	$(CC) $(CPPFLAGS) $(SO_FLAGS) $(LDLIBS) -o $(SO_TARGET) $(OBJS) $(SO_OBJS) $(LDFLAGS)


all: $(SO_TARGET) $(SO_OBJS) $(TARGET) $(OBJS) 
	./$(TARGET) 
	`
check: $(TARGET) $(OBJS) $(SO_TARGET) $(SO_OBJS) 
	./$(TARGET)

valgrind:
	valgrind --leak-check=full ./$(TARGET)

clean: 
	rm -f $(OBJS) $(SO_OBJS) $(TARGET) $(SO_TARGET) $(DEPENDS)

-include $(DEPENDS)

.PHONY: clean check all valgrind