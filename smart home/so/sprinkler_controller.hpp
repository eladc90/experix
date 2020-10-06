#include <vector>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include "common.hpp"
#include "i_controller.hpp"
#include "distributaion_list.hpp"
#include "event.hpp"
#include "common.hpp"
#include "i_agent.hpp"
#include "event_pusher.hpp"

namespace smartHome {
    
typedef std::vector<SharedPtr<Event> > eventContainer;

class Sprinkler : public Icontroller, public IEventHandler, public IAgent
    , public std::tr1::enable_shared_from_this<Sprinkler> {
public:
    Sprinkler(std::string a_room, std::string a_floor);
    //~Sprinkler() = default;

    virtual void SubcribeSelf(DistributionList& a_dl);
    virtual void HandleEvent(SharedPtr<Event> a_event);
    virtual void Connent(IRegistrar& a_registrar, SharedPtr<EventPusher> a_pusher);
    
    virtual size_t GetNumOfEventRecived();
private:
    eventContainer m_events;
    std::string m_room;
    std::string m_floor;

};

}//smartHome