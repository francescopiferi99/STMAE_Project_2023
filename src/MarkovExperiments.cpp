#include "MarkovManager.h"
#include <iostream>

int main()
{
    MarkovManager mm{};
    mm.putEvent("A");
    mm.putEvent("B");
    mm.putEvent("C");
    mm.putEvent("A");
    mm.putEvent("B");
    mm.putEvent("H");
    mm.putEvent("H");
    mm.putEvent("A");


    std::cout << mm.getModelAsString();
    mm.setMaxOrder(3);
    for (auto i=0;i<50;++i){
        state_single next = mm.getEvent();
        int order = mm.getOrderOfLastEvent();
        std::cout << "Next state " << next << " order " << order << std::endl;
    }
}