#include <iostream>
#include "door_controller_2_floor.hpp"
#include "common.hpp"
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace smartHome {

DoorController::DoorController(std::string a_room, std::string a_floor)
    : m_events()
    , m_room(a_room)
    , m_floor(a_floor)
{
}

void DoorController::SubcribeSelf(DistributionList& a_dl){

}

void  DoorController::HandleEvent(SharedPtr<Event> a_event) {
    a_event->Print();
    m_events.push_back(a_event);
}

void DoorController::Connent(IRegistrar& a_registrar, SharedPtr<EventPusher> a_pusher) {
    Location loc(m_room, m_floor);
    Type type("door");
    SharedPtr<IEventHandler> self = shared_from_this();
    a_registrar.AddController(self, type, loc);
}

size_t DoorController::GetNumOfEventRecived() {
    return m_events.size();
}

}//smartHome