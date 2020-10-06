#include <algorithm>
#include "distribution_list_exception.hpp"
#include "distributaion_list.hpp"
#include "common_utils.hpp"
#include "key_generator.hpp"

namespace smartHome {

DistributionList::DistributionList() 
    : m_mailList()
    , m_mutex()
{
}

std::string DistributionList::GenarateKey(Type a_type, Location a_location) {
    std::string rtString = a_type.GetType();
    rtString += a_location.GetRoom();
    rtString += a_location.GetFloor();
    return rtString;
}

void DistributionList::AddController(SharedPtr<IEventHandler> a_controller, Type a_type, Location a_location) {
    MutexGuard mutexGuard(m_mutex);
    {
        std::string Key = GenarateKey(a_type, a_location);
        mailingList::iterator controllerList = m_mailList.find(Key);
        mailingList::iterator end = m_mailList.end();
        if (controllerList == end) {

            SubcriberList newList;
            newList.Add(a_controller);
            std::pair<std::string, SubcriberList >pairToList(Key, newList);
            m_mailList.insert(pairToList);
        }
        else {
            controllerList->second.Add(a_controller);
        }
    }
}

ListToDispath DistributionList::GetMailListByEvent(SharedPtr<Event> a_event) {
    MutexGuard mutexGuard(m_mutex);
    {   
        EventKeyGenerator eventKeys(a_event);
        ListToDispath mailingList;
        keysCont keys = eventKeys.GetKeys();
        keysCont::iterator begin = keys.begin();
        keysCont::iterator end = keys.end();

        while (begin != end) {
            AddToList(*begin, mailingList); 
            ++begin;  
        }

        return mailingList;
    }
}

void DistributionList::AddToList(std::string a_key, ListToDispath& a_list) {
    mailingList::iterator controllerList = m_mailList.find(a_key);
    if (controllerList == m_mailList.end()){
        return;
    }
    a_list.push_back(controllerList->second);
}

}//smartHome