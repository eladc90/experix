#include "pizza.hpp"

extern "C" {
    
Pizza* CreatingPizza() {
    return new Pizza();
}

void AddTopToPizza(Pizza* a_pizza, std::string a_top) {
        a_pizza->AddTop(a_top);
}

void startMake(Pizza* a_pizza) {
    a_pizza->MakePizza();
}

}// extern C
