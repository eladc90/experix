#include "id.hpp"

namespace smartHome {

ID::ID(std::string a_id)
    : m_id(a_id)
{
}

ID::~ID()
{
}

std::string ID::GetId() {
    return m_id;
}

}// smartHome