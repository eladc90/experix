#ifndef __RECORD_HPP__
#define __RECORD_HPP__

#include "cdr.hpp"

namespace experis{

class Record{

public:
    Record(){}
    virtual ~Record(){}
    
    //Record(const Record& a_other);
    //Record& operator=(const Record& a_other);
    //virtual Record& operator+=(const Record& a_other)=0;
    //virtual Record& operator()(const Record& a_other)=0;

private:

};

} //namespace experis

#endif /* __RECORD_HPP__ */

