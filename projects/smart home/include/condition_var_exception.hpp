#ifndef CONDITIONVAR_EXCEPTIONS_HPP_
#define CONDITIONVAR_EXCEPTIONS_HPP_
#include <exception>


namespace smartHome
{

/* -----------------------------Init---------------------------------- */

struct InitNoResourcesException:std::exception
{
	const char* what() const throw () { return "The system lacked the necessary resources to initialize another ";}
};

/* --------------------------Destroy----------------------------------- */

struct DestroyLockOrRefException:std::exception
{
	const char* what()const throw(){ return "try to destroy the object referenced by  while it is locked or referenced";}
};
	

struct DestroyInvalidException:std::exception
{
	const char* what()const throw(){ return "The value specified by  is invalid";}
};

/* ---------------------------Wait------------------------------------- */


struct WaitNotOwnException:std::exception
{
	const char* what()const throw(){ return "The mutex was not owned by the current thread at the time of the call";}
};


struct WaitInvalidException:std::exception
{
	const char* what() const throw () { return "The value specified by cond, mutex, or abstime is invalid or- Different mutexes were supplied for concurrent pthread_cond_wait() operations on the same condition variable";}
};

/* ---------------------------Signal------------------------------------- */


struct SignalInvalidException:std::exception
{
	const char* what() const throw () { return "  The value cond does not refer to an initialized condition variable";}
};

/* ---------------------------BroadCast------------------------------------- */

struct BRlInvalidException:std::exception
{
	const char* what() const throw () { return "  The value cond does not refer to an initialized condition variable";}
};

/* ---------------------------------------------------------------- */


}//namespace smartHome

#endif /* CONDITIONVAR_EXCEPTIONS_HPP_ */