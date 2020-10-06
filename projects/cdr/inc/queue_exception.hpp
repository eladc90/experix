#ifndef __QUEUE_EXCEPTION_HPP__
#define __QUEUE_EXCEPTION_HPP__

#include <exception>

namespace experis {

class QueueIsShutingDown : public std::exception {
    virtual const char* what() const throw() {
        return "Queue is shuting down";
    }
};

} //experis

#endif //__QUEUE_EXCEPTION_HPP__