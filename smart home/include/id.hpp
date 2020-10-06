#ifndef ID_HPP
#define ID_HPP
#include <string>

namespace smartHome{

class ID {
public:
    ID(std::string a_id);
    ~ID();
    std::string GetId();
private:
    std::string m_id;
};

}// smartHome

#endif // ID_HPP