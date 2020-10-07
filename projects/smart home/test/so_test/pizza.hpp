#ifndef PIZZA_HPP
#define PIZZA_HPP
#include <vector>
#include <string>

typedef std::vector<std::string> topsCont;

class Pizza {
public:
    Pizza();
    //~Pizza() = default;

    void AddTop(std::string a_top);
    void MakePizza();
private:
    topsCont m_top;

};

#endif // PIZZA_HPP