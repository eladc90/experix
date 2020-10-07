#include <iostream>
#include <unistd.h>
#include "pizza.hpp"

Pizza::Pizza() 
    : m_top()
{
}

void Pizza::AddTop(std::string a_top) {
    m_top.push_back(a_top);
}

void Pizza::MakePizza() {
    std::cout << "start making dough..." << std::endl;
    sleep(4);
    std::cout << "dough is ready!" << std::endl;
    sleep(1);
    std::cout << "put pizza sauce.." << std::endl;
    sleep(2);
    std::cout << "scattering cheese on the pizza..." << std::endl;
    sleep(2);
    std::cout << "adding your topics..." << std::endl;
    topsCont::iterator begin = m_top.begin();
    topsCont::iterator end = m_top.end();
    sleep(1);
    while (begin != end) {
        std::cout << "adding " << *begin << "..." << std::endl;
        sleep(1);
        ++begin;
    }
    
    int bakingTime = 7;
    std::cout << "baking...";
    for (int i = 0; i < bakingTime; ++i) {
        sleep(1);
        std::cout << "." << std::flush;
    }
    std::cout << std::endl;
    std::cout << "all ready!  bon apetite" << std::endl;
}
