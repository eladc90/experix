#ifndef _POISION_APPLE_HPP_
#define _POISION_APPLE_HPP_
#include <exception>
#include "runnable.hpp"

namespace smartHome{

struct PoisionAppleException : std::exception
{
	const char* what() const throw () {  return "poision apple"; }
};

class PoisionApple : public Runnable {
public:
    virtual void Run();
};

inline void PoisionApple::Run() {
    throw PoisionAppleException(); 
}

}//smartHome

#endif // !_POISION_APPLE_HPP_