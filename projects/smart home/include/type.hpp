#ifndef TYPE_HPP
#define TYPE_HPP
#include <string>

namespace smartHome{

class Type {
public:
    Type(std::string a_type);    
    ~Type();
    const std::string GetType() const;

private:
    std::string m_type;

};

}// smartHome

#endif // TYPE_HPP