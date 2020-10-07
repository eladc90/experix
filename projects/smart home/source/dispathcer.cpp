#include "dispatcher.hpp"
#include "dispaher_utils.hpp"

namespace smartHome {

Dispather::Dispather(size_t a_size) 
{
}

Dispather::~Dispather() 
{
}

void Dispather::Dispath(ControllerList& a_list, SharedPtr<Event> a_event) {
    SubcriberListItr begin = a_list.BeginItr();
    SubcriberListItr end = a_list.EndItr();
    while (begin != end) {

        begin->get()->HandleEvent(a_event);
        ++begin;
    }
}

}//smartHome