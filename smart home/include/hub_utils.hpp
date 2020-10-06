#ifndef HUB_UTILS_HPP
#define HUB_UTILS_HPP
#include "runnable.hpp"
#include "hub.hpp"

namespace smartHome {

class HubRunnable : public Runnable {
public:
    HubRunnable(Hub& a_hub);
    ~HubRunnable();

    virtual void Run();
private:
    Hub& m_hub;
};

}//smartHome


#endif // !HUB_UTILS_HPP