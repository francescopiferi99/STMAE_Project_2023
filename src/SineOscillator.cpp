#include "SineOscillator.h"
#include <JuceHeader.h>

/**
 * SineOscillator is a single sine wave that is played in the Armonizer
 */
SineOscillator::SineOscillator() {
}

SineOscillator::SineOscillator(float gain_) {
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

void SineOscillator::setGain(float gain_) {
    gain = gain_;
}

void SineOscillator::resetOscillator() {
    currentAngle = 0.0f;
}
