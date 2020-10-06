#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include "i_controller.hpp"
#include "distributaion_list.hpp"
#include "event.hpp"

namespace smartHome {

class Sprinkler : public Icontroller, public IEventHandler
    , public std::tr1::enable_shared_from_this<Sprinkler> {
public:
    Sprinkler();
    //~Sprinkler() = default;

    virtual void SubcribeSelf(DistributionList& a_dl);
    virtual void HandleEvent(SharedPtr<Event> a_event);
    
private:

};

}//smartHome