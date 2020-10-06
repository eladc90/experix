#include <sys/types.h>  // fork
#include <unistd.h>     // fork
#include <fstream>      // ofstream
#include <assert.h>     // assert
#include <iostream>
#include "file_watcher.hpp"
#include "cyc_waitable_queue.hpp"
#include "tcp_consumer.hpp"
#include "tcp_producer.hpp"
#include "thread.hpp"
#include "file_to_message.hpp"
#include "cdr_sender.hpp"

struct Configuration {
    size_t m_waitQSIZE;
    std::string m_fileDirPath;
    std::string m_consumerIp;
    unsigned int m_port;
};

static void ConfigurationFileToStruct(Configuration* a_configStruct);

int main(void) {

    Configuration configStruct;
    ConfigurationFileToStruct(&configStruct);
    pid_t forkRes = fork();
    
    if(forkRes > 0) { // parent - file side
        experis::WaitableQueue<std::string> fileQueue(configStruct.m_waitQSIZE);
        experis::WaitableQueue<std::string> lineQueue(configStruct.m_waitQSIZE);
        experis::FileWatcher fileWatch(configStruct.m_fileDirPath.c_str(), &fileQueue);
        experis::FileToMsg fileToMessage(&fileQueue, &lineQueue);
        experis::Thread thrdFileWatch(&fileWatch);
        experis::Thread thrdFileToMsg(&fileToMessage);
        experis::TCPConsumer consumer(configStruct.m_port, configStruct.m_consumerIp);
        experis::CdrSender sender(&lineQueue, consumer);
        experis::Thread sendterToCdr(&sender);
    }

    else if(0 == forkRes) { // child - agg side + client

    }
    else { // failure
        assert(!"fail to configurate system");
    }

    return 0; 
}


static void ConfigurationFileToStruct(Configuration* a_configStruct){
    std::ifstream configFile;
    configFile.open("../configuration");
    if (configFile.is_open()) {
        configFile >> a_configStruct->m_port;
        configFile >> a_configStruct->m_consumerIp;
        configFile >> a_configStruct->m_fileDirPath;
        configFile >> a_configStruct->m_waitQSIZE;

        std::cout <<"port: " << a_configStruct->m_port << std::endl;
        std::cout <<"consumer ip: " << a_configStruct->m_consumerIp << std::endl;
        std::cout <<"file directory: " << a_configStruct->m_fileDirPath << std::endl;
        std::cout <<"queue size: " << a_configStruct->m_waitQSIZE << std::endl;
    }
    else
    {
        assert("!fail in open configuration file");
    }
    

    configFile.close();
}

/*     WaitableQueue<std::string> fileQueue(20);
    WaitableQueue<std::string> lineQueue(20);

    FileWatcher fileWatch("../test_dir", &fileQueue);
    FileToMsg fileToMessage(&fileQueue, &lineQueue);
    Thread thrdFileWatch(&fileWatch);
    Thread thrdFileToMsg(&fileToMessage);
    TCPConsumer consumer(8080, "127.0.0.1");
    CdrSender sender(&lineQueue, &consumer);
    Thread sendterToCdr(&sender); */