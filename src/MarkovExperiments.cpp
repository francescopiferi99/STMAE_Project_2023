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
    mm.setMaxOrder(6);
    state_sequence sequence;
    sequence.emplace_back("A");
    for (auto i=1;i<5;++i){
        sequence.push_back(mm.getEvent(sequence));
    }
    for(auto i = 0; i < 5; i++){
        std::cout << "Next state " << sequence[i] << std::endl;

    }
}