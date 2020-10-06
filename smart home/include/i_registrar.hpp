#ifndef I_REGISTRAR_HPP
#define I_REGISTRAR_HPP
#include "I_event_handler.hpp"
#include "common.hpp"

namespace smartHome {

class IRegistrar {
public:
    IRegistrar() {}
    virtual ~IRegistrar() {}

    virtual void AddController(SharedPtr<IEventHandler> a_controller, Type a_type, Location a_location) = 0;
private:


};

}//smartHome

#endif // !I_REGISTRAR_HPP