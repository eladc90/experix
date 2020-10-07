#ifndef DISRIBUTION_LIST_EXCEPTION_HPP
#define DISRIBUTION_LIST_EXCEPTION_HPP

#include <exception>

namespace smartHome {

struct NoListExist : public std::exception {

    virtual const char* what() const throw() {
      return ("lisd is invalid");
    }
};

}// smartHome

#endif //DISRIBUTION_LIST_EXCEPTION_HPP