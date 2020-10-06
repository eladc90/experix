
#ifndef _PARSER_MANAGER_HPP_
#define _PARSER_MANAGER_HPP_
#include <iostream>
#include <fstream>
#include "cyc_waitable_queue.hpp"
#include "../inc/thread.hpp"
#include <string>
#include "../inc/to_do_parse.hpp"
#include "../inc/file_maneger.hpp"
#include <vector>


namespace experis
{

static const int g_deafContSize=40;

class ParserManager{

typedef std::string* Message; 
typedef typename experis::WaitableQueue<Message> Container;


public :
     ParserManager( FileMng* a_fileMan, std::vector<Message*> a_fileMsges); 
    ~ParserManager(){delete m_run;}
    
private:
    FileMng* a_fileMan;
    experis::Runnable* m_run;

};


    ParserManager::ParserManager( FileMng* a_fileMan, std::vector<Message*> a_fileMsges)
    : a_fileMan(a_fileMan)
    , m_run(0) 
    {
        experis::Runnable* parseRun = new  experis::FileParse(a_fileMan->GetNewFile(), a_fileMsges);
        Thread msgThread(parseRun); 

    }



} // namespace experis

#endif /* _PARSER_MANAGER_HPP_ */
