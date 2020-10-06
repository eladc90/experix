#ifndef __TCP_EXCEPTION_HPP__
#define __TCP_EXCEPTION_HPP__

#include <exception>

namespace experis {

class NotAvaliable : public std::exception {
public:
    virtual const char* what() const throw() { 
        return "Protocol not avaliable";
    }
};

class LimitReached : public std::exception {
public:
    virtual const char* what() const throw() { 
        return "Reached limit of FD";
    }
};

class InsufficientMemory : public std::exception {
    virtual const char* what() const throw() { 
        return "The socket cannot be created until sufficient resources are freed";
    }
};

class ConnectionRefused : public std::exception {
    virtual const char* what() const throw() { 
        return "No one listening on the remote address";
    }
};

class RecivedSignal : public std::exception {
    virtual const char* what() const throw() {
        return "Interrupted by a signal that was caught";
    }
};

class UnreachableNetwork : public std::exception {
    virtual const char* what() const throw() {
        return "Network is unreachable";
    }
};

class Timeout : public std::exception {
    virtual const char* what() const throw() {
        return "Timeout while attempting connection";
    }
};

class Block : public std::exception {
    virtual const char* what() const throw() {
        return "The requested operation would block";
    }
};     

class ConnectionReset : public std::exception {
    virtual const char* what() const throw() {
        return "Connection reset by peer";
    }
};

class NullError : public std::exception {
    virtual const char* what() const throw() {
        return "Recived null buffer";
    }
};

class NoMemory : public std::exception {
    virtual const char* what() const throw() {
        return "No memory available";
    }
};

class ShutDown : public std::exception {
    virtual const char* what() const throw() {
        return "Local  end  has  been  shut  down";
    }
};

class AddInUse : public std::exception {
    virtual const char* what() const throw() {
        return "The given address is already in use";
    }
};

class ConnectionAborted : public std::exception {
    virtual const char* what() const throw() {
        return "A connection has been aborted";
    }
};

class ProtocolErr : public std::exception {
    virtual const char* what() const throw() {
        return "Protocol error";
    }
};

} //experis 

#endif //__TCP_EXCEPTION_HPP__