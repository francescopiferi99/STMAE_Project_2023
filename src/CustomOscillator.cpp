//
// Created by Francesco Piferi on 29/06/23.
//

#include "CustomOscillator.h"
#include "SineOscillator.h"
#include "MarkovChain.h"
#include "MarkovManager.h"

CustomOscillator::CustomOscillator() {

}

float CustomOscillator::getNextSample() noexcept {
    float nextSample = 0.0f;
    for(int i = 0; i < sineOscillators.size(); i++){
        nextSample += sineOscillators[i]->getGain()*sineOscillators[i]->getNextSample();
    }
    return nextSample;
}



void CustomOscillator::resetOscillators() {
    sineOscillators.clear();
}

void CustomOscillator::addSineOscillator(SineOscillator* oscillator) {
    sineOscillators.push_back(oscillator);
}
