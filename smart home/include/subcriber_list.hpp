#ifndef SUBSCRIBER_LIST_HPP
#define SUBSCRIBER_LIST_HPP
#include <vector>
#include "common.hpp"
#include "I_event_handler.hpp"
#include "key_generator.hpp"

namespace smartHome {

typedef std::vector<SharedPtr<IEventHandler> >::iterator SubcriberListItr;
typedef std::vector<SharedPtr<IEventHandler> > SubcriberContainer;
typedef std::vector<std::string> keysCont;

class SubcriberList {
public:
    //SubcriberList() = default;
    //~SubcriberList() = default;

    void Add(SharedPtr<IEventHandler> a_eventHanler);
    SubcriberListItr BeginItr() ;
    SubcriberListItr EndItr() ;
    SubcriberList& operator+=(SubcriberList a_other);
private:
    SubcriberContainer m_list;

};

}//smartHome

#endif // SUBSCRIBER_LIST_HPP