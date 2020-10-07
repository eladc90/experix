#ifndef DISTRIBUTION_LIST_HPP
#define DISTRIBUTION_LIST_HPP
#include <map>
#include <vector>
#include <vector>
#include "common.hpp"
#include "event.hpp"
#include "I_event_handler.hpp"
#include "mutex.hpp"
#include "subcriber_list.hpp"
#include <boost/unordered/unordered_map.hpp>
#include "i_registrar.hpp"
#include "type.hpp"
#include "location.hpp"
#include "key_generator.hpp"

namespace smartHome {

class ControllerAgent;

typedef boost::unordered_map<std::string , SubcriberList > mailingList;//TODO
typedef std::vector<SubcriberList> ListToDispath;

class DistributionList : public IRegistrar{
public:
    DistributionList();
    //~DistributionList() = default;
    
    ListToDispath GetMailListByEvent(SharedPtr<Event> a_event);
    virtual void AddController(SharedPtr<IEventHandler> a_controller, Type a_type, Location a_location);
private:
    std::string GenarateKey(Type a_type, Location a_location);
    void AddToList(std::string a_key, ListToDispath& a_list);

private:    
    mailingList m_mailList;
    Mutex m_mutex;
    
};

}//smartHome

#endif // !DISTRIBUTION_LIST_HPP