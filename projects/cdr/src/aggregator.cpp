#include "aggregator.hpp"
#include "cdr_dispatcher.hpp"

namespace experis {

    IAggregator::IAggregator(CdrDispatcher* a_dispatcher): m_disp(a_dispatcher){ a_dispatcher->Subscribe(this);}
    IAggregator::~IAggregator(){}

}// experis

