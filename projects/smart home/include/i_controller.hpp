#ifndef I_CONTROLLER_HPP
#define I_CONTROLLER_HPP
#include "event.hpp"
#include "common.hpp"
#include "distributaion_list.hpp"

namespace smartHome {

class ControllerContainer;

class Icontroller {
public:
    Icontroller() {}
    virtual ~Icontroller() {}
    
    virtual void SubcribeSelf(DistributionList& a_dl) = 0;
    virtual void HandleEvent(SharedPtr<Event> a_event) = 0;
    
private:

};

}//smartHome

#endif // !I_CONTROLLER_HPP