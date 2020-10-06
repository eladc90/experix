#include "distributer_pool_utils.hpp"
#include "distributer_pool.hpp"

namespace smartHome {

//------------------------------ waiting thread predicate --------------------------//

DistributPredicte::DistributPredicte(DistributerPool& a_distPool) 
    : m_distPool(a_distPool)
{
}

DistributPredicte::~DistributPredicte()
{
}

bool DistributPredicte::operator()() {
    return !(m_distPool.GetIfFinishToWork());

}

//------------------------------ ready predicate --------------------------//

ReadyToWorkPredicte::ReadyToWorkPredicte(DistributerPool& a_distPool)
    : m_distPool(a_distPool)
{
}

ReadyToWorkPredicte::~ReadyToWorkPredicte() 
{
}

bool ReadyToWorkPredicte::operator()() {
    return !m_distPool.GetIfReadyToWork(); 

}

}//smartHome
