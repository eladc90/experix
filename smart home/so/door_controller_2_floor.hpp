#include <vector>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include "common.hpp"
#include "i_controller.hpp"
#include "distributaion_list.hpp"
#include "event.hpp"
#include "i_agent.hpp"

namespace smartHome {
typedef std::vector<SharedPtr<Event> > eventContainer;

class DoorController : public Icontroller, public IEventHandler , public IAgent
    , public std::tr1::enable_shared_from_this<DoorController> {
public:
    DoorController(std::string a_room, std::string a_floor);
    //~DoorController() = default;

    virtual void SubcribeSelf(DistributionList& a_dl);
    virtual void HandleEvent(SharedPtr<Event> a_event);
     
    size_t GetNumOfEventRecived();
    virtual void Connent(IRegistrar& a_registrar, SharedPtr<EventPusher> a_pusher);
private:
    eventContainer m_events;
    std::string m_room;
    std::string m_floor;

};

}//smartHome