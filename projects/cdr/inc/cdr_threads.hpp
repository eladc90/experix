#ifndef __CDRTHREADS_HPP__
#define __CDRTHREADS_HPP__

#include <list>
#include <stddef.h>  //size_t
#include "runnable.hpp"
#include "thread.hpp"
#include "cyc_waitable_queue.hpp"
#include "cdr.hpp"
#include "cdr_dispatcher.hpp"


namespace experis
{

class ThreadPool: public Runnable{

public:
    ThreadPool(size_t a_numOfThreads , CdrDispatcher* a_disp , WaitableQueue< Cdr* > *  a_cdrQ);
    ~ThreadPool();
    virtual void Run();
    void ShoutDown();

private:

    std::list<Thread*> m_threads;
    CdrDispatcher*  m_disp;
    std::vector<Runnable*> m_runners;
    WaitableQueue<Cdr*>* m_cdrs;
    bool m_workMode;

};

} // namespace experis

#endif /* __CDRTHREADS_HPP__ */
