#ifndef DISPATH_RUNNABLE_HPP
#define DISPATH_RUNNABLE_HPP
#include "runnable.hpp"
#include "dispatcher.hpp"
#include "subcriber_list.hpp"

namespace smartHome {

class DispthRun : public Runnable {
public:
    DispthRun(Dispather& a_dispather, SubcriberList& a_subcribeList, SharedPtr<Event> a_event);
    //~DispthRun() = default;

    virtual void Run();
private:
    Dispather& m_dispather;
    SubcriberList& m_subcribeList;
    SharedPtr<Event> m_event;

};

}//smartHome

#endif // DISPATH_RUNNABLE_HPP