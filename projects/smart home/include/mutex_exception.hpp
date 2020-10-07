#ifndef __MUTEX_EXCEPTIONS_HPP__
#define __MUTEX_EXCEPTIONS_HPP__

#include <exception>

namespace smartHome {

struct ENOMEMMutexInit : public std::exception {

    virtual const char* what() const throw() {
      return ("ENOMEM error: Insufficient memory ");
    }
};

struct EAGAINMutexInit : public std::exception {

    virtual const char* what() const throw()
    {
      return ("EAGAIN error: can't initialized try again");
    }
};

struct MutexlockEAGAIN : public std::exception {

    virtual const char* what() const throw()
    {
      return ("EAGAIN error: the maximum number of recursive locks for mutex has been exceeded");//TODO
    }
};

// ----------------------------------------------
struct MutexUnlockEAGAIN : public std::exception {

    virtual const char* what() const throw()
    {
      return ("EAGAIN error: the maximum number of recursive locks for mutex has been exceeded");//TODO
    }
};

struct EPERMMutexUnlock : public std::exception {

    virtual const char* what() const throw()
    {
      return ("EPERM: The current thread does not own the mutex");
    }
};

// ---------------------------------

struct EDEADLKMutexlock : public std::exception {

    virtual const char* what() const throw()
    {
      return ("EDEADLK error: the thread already have the mutex");
    }
};

}// namespace smartHome
#endif //__MUTEX_EXCEPTIONS_HPP__