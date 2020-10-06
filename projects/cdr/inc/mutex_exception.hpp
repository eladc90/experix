#ifndef _MUTEX_EXCEPTIONS_HPP_
#define _MUTEX_EXCEPTIONS_HPP_

#include <exception>

namespace experis
{

struct InvalidException:std::exception
{
	const char* what() const throw () { return "The value specified by attr is invalid";}
};

struct InitPrevException:std::exception
{
	const char* what()const throw(){ return "a previously initialized";}
};
	
struct InitPrivilegeException:std::exception
{
	const char* what() const throw () { return "The caller does not have the privilege to perform the operation.";}
};

struct InitNoResourcesException:std::exception
{
	const char* what() const throw () { return"The system lacked the necessary resources to initialize another ";}
};



/* ---------------------------------------------------------------- */



struct MUDestroyLockOrRefException:std::exception
{
	const char* what()const throw(){ return "try to destroy the object referenced by  while it is locked or referenced";}
};
	

struct MUDestroyInvalidException:std::exception
{
	const char* what()const throw(){ return "The value specified by  is invalid";}
};

/* -------------lock---------------- */


struct AlreadyOwnException:std::exception
{
	const char* what()const throw(){ return "The current thread already owns the ";}
};



struct NotOwnException:std::exception
{
	const char* what()const throw(){ return "The current thread does not own the ";}
};


struct LimitException:std::exception
{
	const char* what()const throw(){ return "    The limit on the number of simultaneously held es has been exceeded";}
};







}//namespace experis

#endif /* __EXCEPTIONS_HPP_ */