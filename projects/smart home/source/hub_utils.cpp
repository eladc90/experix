#include "hub_utils.hpp"

namespace smartHome {

HubRunnable::HubRunnable(Hub& a_hub)
    :m_hub(a_hub) 
{
}

HubRunnable::~HubRunnable()
{
}

void HubRunnable::Run() {
    while (!m_hub.IsShutingDown()){
        m_hub.Distribute();
        if (m_hub.IsShutingDown()) {
            
            break;
        }
    }
}

}//smartHome