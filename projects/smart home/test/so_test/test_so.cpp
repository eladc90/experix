#include <dlfcn.h>
#include <iostream>

//forword declaration
    class Pizza; 
int main() {
    //forword declaration
    class Pizza; 

    //pointers to funcs
    Pizza* (*create)();
    void (*addTop)(Pizza* a_pizza, std::string a_top);
    void (*makePizza)(Pizza* a_pizza);

    //opening shared object
    void *handle = dlopen("./lib_pizza.so", RTLD_NOW);
    if (!handle) {
        std::cout << dlerror() << std::endl;
    }

    //preparing funcs
    create = (Pizza* (*)())dlsym(handle, "CreatingPizza");
    if (!create) {
        std::cout << dlerror() << std::endl;
    }

    addTop = (void (*)(Pizza* a_pizza, std::string a_top))dlsym(handle, "AddTopToPizza");
    if (!addTop) {
        std::cout << dlerror() << std::endl;
    }

    makePizza = (void (*)(Pizza* a_pizza))dlsym(handle, "startMake");
    if (!makePizza) {
        std::cout << dlerror() << std::endl;
    }

    Pizza* pz = create();
    addTop(pz, "olives");
    addTop(pz, "onion");
    addTop(pz, "pepperoni");
    makePizza(pz);    
    return 0;
}
