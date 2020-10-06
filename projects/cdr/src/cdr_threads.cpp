#include "cdr_threads.hpp"
#include "thread.hpp"
#include <iostream>
#include <unistd.h>

namespace experis
{

ThreadPool::ThreadPool(size_t a_numOfThreads, CdrDispatcher *a_disp, WaitableQueue<Cdr *> *a_cdrQ)
    : m_workMode(true), m_threads(std::list<Thread *>(a_numOfThreads)), m_disp(a_disp), m_runners(a_numOfThreads)
{
    m_cdrs = a_cdrQ;
}

ThreadPool::~ThreadPool()
{
    m_workMode = false;
    std::list<Thread *>::iterator it = m_threads.begin();

    for (; it != m_threads.end(); ++it)
    {
        delete *it;
    }

    for (int i = 0; i < m_runners.size(); ++i)
    {

        delete m_runners[i];
    }
}

void ThreadPool::Run()
{
    Cdr *cdr = 0;

    std::cout << " ThreadPool: " << std::endl;

    while (m_workMode)
    {
        std::list<Thread *>::iterator it = m_threads.begin();

        for (; it != m_threads.end(); ++it)
        {
            m_cdrs->Dequeue(&cdr);
            Runnable *runner = new RunDisp(cdr, m_disp);
            m_runners.push_back(runner);
            *it = new Thread(runner);
        }
                    sleep(0.2);

    }
}

void ThreadPool::ShoutDown()
{
    m_workMode = false;
}

} // namespace experis
