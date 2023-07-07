//
// Created by Francesco Piferi on 29/06/23.
//

#include "SineOscillator.h"
#include <JuceHeader.h>

SineOscillator::SineOscillator() {
}

SineOscillator::SineOscillator(float gain_) {
    gain = gain_;
}

void SineOscillator::setGain(float gain_){
    gain = gain_;
}

void SineOscillator::setFrequency (float frequency, float sampleRate) {
    auto cyclesPerSample = frequency / sampleRate;
    angleDelta = cyclesPerSample * juce::MathConstants<float>::twoPi;
}

float SineOscillator::getNextSample() noexcept {
    auto currentSample = std::sin(currentAngle);
    updateAngle();
    return currentSample;
}

forcedinline void SineOscillator::updateAngle() noexcept {
    currentAngle += angleDelta;
    if (currentAngle >= juce::MathConstants<float>::twoPi)
        currentAngle -= juce::MathConstants<float>::twoPi;
}

float SineOscillator::getGain() {
    return gain;
}
