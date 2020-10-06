
TARGET	= a.out
CPP		= g++ -pthread
CFLAGS	= -ansi -g3 -pedantic -I../inc/
OBJS 	= cdr.o cdr_maneger.o  conditional_variable.o customer.o file_maneger.o cdr_sender.o\
i_channel.o mobile_operator.o mutex.o operator_aggregator.o parser.o tcp_consumer.o tcp_producer.o thread.o to_do_parse.o\
aggregator.o cdr_dispatcher.o cdr_threads.o\
protocol.o file_watcher.o  file_to_message.o customer_aggregator.o initilizer.o\


INC_DIR = ../inc/
 
$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

cdr.o: cdr.cpp  $(INC_DIR)cdr.hpp
	$(CPP) $(CFLAGS) -c cdr.cpp

file_to_message.o: file_to_message.cpp $(INC_DIR)file_to_message.hpp
	$(CPP) $(CFLAGS) -c file_to_message.cpp

file_watcher.o: file_watcher.cpp  $(INC_DIR)file_watcher.hpp
	$(CPP) $(CFLAGS) -c file_watcher.cpp

parser.o: parser.cpp  $(INC_DIR)parser.hpp
	$(CPP) $(CFLAGS) -c parser.cpp

tcp_consumer.o: tcp_consumer.cpp  $(INC_DIR)tcp_consumer.hpp
	$(CPP) $(CFLAGS) -c tcp_consumer.cpp

tcp_producer.o: tcp_producer.cpp  $(INC_DIR)tcp_producer.hpp
	$(CPP) $(CFLAGS) -c tcp_producer.cpp

thread.o: thread.cpp  $(INC_DIR)thread.hpp
	$(CPP) $(CFLAGS) -c thread.cpp

to_do_parse.o: to_do_parse.cpp  $(INC_DIR)to_do_parse.hpp
	$(CPP) $(CFLAGS) -c to_do_parse.cpp

protocol.o: protocol.cpp  $(INC_DIR)protocol.hpp
	$(CPP) $(CFLAGS) -c protocol.cpp

mobile_operator.o: mobile_operator.cpp  $(INC_DIR)mobile_operator.hpp
	$(CPP) $(CFLAGS) -c mobile_operator.cpp

mutex.o: mutex.cpp  $(INC_DIR)mutex.hpp
	$(CPP) $(CFLAGS) -c mutex.cpp

file_maneger.o: file_maneger.cpp  $(INC_DIR)file_maneger.hpp
	$(CPP) $(CFLAGS) -c file_maneger.cpp

i_channel.o: i_channel.cpp  $(INC_DIR)i_channel.hpp
	$(CPP) $(CFLAGS) -c i_channel.cpp

cdr_maneger.o: cdr_maneger.cpp  $(INC_DIR)cdr_maneger.hpp
	$(CPP) $(CFLAGS) -c cdr_maneger.cpp

cdr_sender.o: cdr_sender.cpp  $(INC_DIR)cdr_sender.hpp
	$(CPP) $(CFLAGS) -c cdr_sender.cpp

initilizer.o: initilizer.cpp 
	$(CPP) $(CFLAGS) -c initilizer.cpp

conditional_variable.o: conditional_variable.cpp  $(INC_DIR)conditional_variable.hpp
	$(CPP) $(CFLAGS) -c conditional_variable.cpp

customer.o: customer.cpp  $(INC_DIR)customer.hpp
	$(CPP) $(CFLAGS) -c customer.cpp


#cdr_main.o: cdr_main.cpp
#	$(CPP) $(CFLAGS) -c cdr_main.cpp

#-------


aggregator.o: aggregator.cpp $(INC_DIR)aggregator.hpp $(INC_DIR)cdr_dispatcher.hpp 
	$(CPP) $(CFLAGS) -c  aggregator.cpp

cdr_dispatcher.o:  cdr_dispatcher.cpp $(INC_DIR)cdr_dispatcher.hpp $(INC_DIR)cdr.hpp  $(INC_DIR)cyc_waitable_queue.hpp $(INC_DIR)mutex.hpp $(INC_DIR)runnable.hpp $(INC_DIR)mutex.hpp
	$(CPP) $(CFLAGS) -c cdr_dispatcher.cpp


cdr_threads.o: cdr_threads.cpp $(INC_DIR)cdr_threads.hpp $(INC_DIR)thread.hpp $(INC_DIR)cyc_waitable_queue.hpp $(INC_DIR)cdr.hpp  $(INC_DIR)runnable.hpp   $(INC_DIR)cdr_dispatcher.hpp  $(INC_DIR)cyc_waitable_queue.hpp
	$(CPP) $(CFLAGS) -c cdr_threads.cpp


customer_aggregator.o: customer_aggregator.cpp $(INC_DIR)aggregator.hpp $(INC_DIR)cdr.hpp $(INC_DIR)query.hpp $(INC_DIR)record.hpp $(INC_DIR)customer.hpp $(INC_DIR)mutex.hpp $(INC_DIR)hash_mt.hpp $(INC_DIR)hash_mt_inl.hpp $(INC_DIR)functor.hpp  $(INC_DIR)update_functor.hpp $(INC_DIR)cdr_dispatcher.hpp
	$(CPP) $(CFLAGS) -c customer_aggregator.cpp


operator_aggregator.o: operator_aggregator.cpp $(INC_DIR)operator_aggregator.hpp  $(INC_DIR)aggregator.hpp $(INC_DIR)cdr.hpp $(INC_DIR)query.hpp $(INC_DIR)mobile_operator.hpp $(INC_DIR)functor.hpp $(INC_DIR)update_functor.hpp $(INC_DIR)hash_mt.hpp 
	$(CPP) $(CFLAGS) -c operator_aggregator.cpp

#test dispatcher and other 
#test.o: test.cpp    $(INC_DIR)cdr_threads.hpp  $(INC_DIR)aggregator.hpp  $(INC_DIR)cyc_waitable_queue.hpp $(INC_DIR)thread.hpp $(INC_DIR)cdr.hpp $(INC_DIR)query.hpp 
#	$(CPP) $(CFLAGS) -c test.cpp

# ___Tests_____
#test.o
# cdr_main.o
#______________


valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch




