#include "type.hpp"

namespace smartHome{

Type::Type(std::string a_type)
    :m_type(a_type)
{
}

Type::~Type()
{
}

const std::string Type::GetType() const {
    return m_type;
}

}//smartHome