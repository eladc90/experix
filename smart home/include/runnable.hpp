#ifndef RUNNABLE_HPP__
#define RUNNABLE_HPP__

namespace smartHome{

class Runnable {
public:
    Runnable(){}
    virtual ~Runnable(){}

    virtual void Run() = 0;

private:
    Runnable& operator= (const Runnable& a_thread);
    Runnable(const Runnable& a_thread);

};

}// smartHome::

#endif // RUNNABLE_HPP_