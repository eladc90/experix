#ifndef _THREAD_EXCEPTIONS_HPP_
#define _THREAD_EXCEPTIONS_HPP_

#include <exception>

namespace experis
{

struct ThreadPermissionException:std::exception
{
	const char* what() const throw () { return"No permission to set the scheduling policy and parameters specified in attr"; }
};

struct ThreadResourcesException:std::exception
{
	const char* what()const throw(){ return "The system lacked the necessary resources to create another thread";}
};
	

}//namespace experis

#endif /* _THREAD_EXCEPTIONS_HPP_ */