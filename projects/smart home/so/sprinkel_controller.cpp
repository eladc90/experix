#include <iostream>
#include "sprinkler_controller.hpp"
#include "common.hpp"
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace smartHome {

Sprinkler::Sprinkler(std::string a_room, std::string a_floor)
    : m_events()
    , m_room(a_room)
    , m_floor(a_floor)
{
}

void Sprinkler::SubcribeSelf(DistributionList& a_dl){

}

void  Sprinkler::HandleEvent(SharedPtr<Event> a_event) {
    //a_event->Print();
    m_events.push_back(a_event);
}

void Sprinkler::Connent(IRegistrar& a_registrar, SharedPtr<EventPusher> a_pusher) {
    Location loc(m_room, m_floor);
    Type type("fire");
    SharedPtr<IEventHandler> self = shared_from_this();
    a_registrar.AddController(self, type, loc);
}

size_t Sprinkler::GetNumOfEventRecived() {
    return m_events.size();
}

}//smartHome