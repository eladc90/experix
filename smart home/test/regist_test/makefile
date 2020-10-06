
CC	= g++ -pthread 
CXX = g++

CFLAGS = -ansi -pedantic -Wall -Werror
CFLAGS+= -g3
CXXFLAGS = $(CFLAGS) -std=c++03 

CPPFLAGS = -I$(SRC_DIR) -I$(INC_DIR) 
LDFLAGS = 
LDLIBS = 

SRC_DIR = ../../source/
INC_DIR = ../../include/


OBJS = regist_test.o $(SRC_DIR)location.o $(SRC_DIR)type.o $(SRC_DIR)event_creator.o $(SRC_DIR)sensor_agent.o\
$(SRC_DIR)agent_info.o $(SRC_DIR)mutex.o $(SRC_DIR)event_pusher.o $(SRC_DIR)event_puller.o\
$(SRC_DIR)condition_var.o $(SRC_DIR)id.o $(SRC_DIR)common_utils.o $(SRC_DIR)event.o\
$(SRC_DIR)controller_container.o $(SRC_DIR)controller_agent.o $(SRC_DIR)dispathcer.o $(SRC_DIR)dispather_utils.o\
$(SRC_DIR)thread.o $(SRC_DIR)task_consumer.o $(SRC_DIR)thread_container.o $(SRC_DIR)thread_pool.o \
$(SRC_DIR)distribution_list.o $(SRC_DIR)hub.o $(SRC_DIR)hub_utils.o $(SRC_DIR)sensor_utils.o $(SRC_DIR)event_bus.o\
$(SRC_DIR)subcriber_list.o $(SRC_DIR)dispather_pool.o $(SRC_DIR)dispather_runnable.o $(SRC_DIR)key_generator.o\
$(SRC_DIR)distributer_pool.o $(SRC_DIR)distributer_pool_utils.o $(SRC_DIR)disribute_predicate.o 

TARGET =regist_test

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

#dependency on header file.

regist_test.o: $(INC_DIR)mu_test.h

check: $(TARGET) $(OBJS)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind ./$(TARGET)
	
all:

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: clean  vlagrind check