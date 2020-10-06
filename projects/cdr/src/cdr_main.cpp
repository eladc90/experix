#include <string>
#include "cyc_waitable_queue.hpp"
#include "file_watcher.hpp"
#include "cdr_sender.hpp"
#include "tcp_consumer.hpp"
#include "file_to_message.hpp"
#include "thread.hpp"

using namespace experis;

void MainTest();

int main() {

    MainTest();
    return 0;
}

void MainTest() {
    WaitableQueue<std::string> fileQueue(20);
    WaitableQueue<std::string> lineQueue(20);

    FileWatcher fileWatch("../test_dir", &fileQueue);
    FileToMsg fileToMessage(&fileQueue, &lineQueue);
    Thread thrdFileWatch(&fileWatch);
    Thread thrdFileToMsg(&fileToMessage);
    TCPConsumer consumer(8080, "127.0.0.1");
    CdrSender sender(&lineQueue, &consumer);
    Thread sendterToCdr(&sender);
}

