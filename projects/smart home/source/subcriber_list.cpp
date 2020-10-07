#include <algorithm>
#include "subcriber_list.hpp"

namespace smartHome {

void SubcriberList::Add(SharedPtr<IEventHandler> a_eventHanler) {
    m_list.push_back(a_eventHanler);
}

SubcriberListItr SubcriberList::BeginItr() {
    return m_list.begin();
}
SubcriberListItr SubcriberList::EndItr() {
    return m_list.end();
}

SubcriberList& SubcriberList::operator+=(SubcriberList a_other) {
    SubcriberListItr begin = a_other.BeginItr();
    SubcriberListItr end = a_other.EndItr();
    while (begin != end) {
        m_list.push_back(*begin);
        ++begin;
    } 
    return *this;
}

}//smartHome