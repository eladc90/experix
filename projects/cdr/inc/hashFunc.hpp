#ifndef _HASHFUNCTION_HPP_
#define _HASHFUNCTION_HPP_

#include <string>
#include <stdio.h>

namespace experis
{
    
class Functor{

public:
    Functor(){}
    unsigned int operator()(const std::string& a_key) const {
            return a_key.c_str()[0];
    }

private:


};



} // namespace experis


#endif //