#ifndef _RUNNABLE_HPP_
#define _RUNNABLE_HPP_

namespace experis {

class Runnable{
    
public:
    //Runnable() = default;
    //Runnable(const Runnable & a_other) = default;
    virtual ~Runnable(){}
    virtual void Run()=0;

private:
    Runnable& operator=(const Runnable& a_other); 
    
};

}//namespace experis

#endif /* _RUNNABLE_HPP_ */