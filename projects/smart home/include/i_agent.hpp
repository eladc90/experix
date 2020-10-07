#ifndef I_AGENT_HPP
#define I_AGENT_HPP
#include "common.hpp"
#include "i_registrar.hpp"
#include "event_pusher.hpp"

namespace smartHome {

class IAgent {
public:
    IAgent() {}
    ~IAgent() {}

    virtual void Connent(IRegistrar& a_registrar, SharedPtr<EventPusher> a_pusher) = 0;
    virtual size_t GetNumOfEventRecived() = 0;
private:


};

}//smartHome

#endif // !I_AGENT_HPP