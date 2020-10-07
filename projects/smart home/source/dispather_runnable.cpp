#include "dispath_runnable.hpp"

namespace smartHome {
    
DispthRun::DispthRun(Dispather& a_dispather, SubcriberList& a_subcribeList, SharedPtr<Event> a_event) 
    : m_dispather(a_dispather)
    , m_subcribeList(a_subcribeList)
    , m_event(a_event)
{
}

void DispthRun::Run() {
    m_dispather.Dispath(m_subcribeList, m_event);
}

}//smartHome