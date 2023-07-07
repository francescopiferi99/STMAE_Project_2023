//
// Created by Francesco Piferi on 02/07/23.
//

#include "Armonizer.h"
#pragma once

Armonizer* Armonizer::armonizer = NULL;

Armonizer::Armonizer() {
    updateOscillators();
}

Armonizer* Armonizer::getArmonizer(){
    if (armonizer == NULL) {
        armonizer = new Armonizer();
    }
    return armonizer;
}

void Armonizer::setOrderValue(int newValue)
{
    sliderValue = newValue;
    updateOscillators();
}

int Armonizer::getOrder(){
    std::cout << "HELLOOO" << std::endl;
    std::cout << sliderValue;
    return sliderValue;
}

void Armonizer::updateOscillators()
{
    // Clear existing oscillators
    oscillators.clear();

    for (int i = 0; i < sliderValue; ++i)
    {
        SineOscillator sineOscillator;
        oscillators.push_back(sineOscillator);
    }
}

void Armonizer::getNextAudioBlock(juce::AudioBuffer<float> &bufferToFill) {
    if (isOn) {
        auto* leftBuffer = bufferToFill.getWritePointer(0);
        auto* rightBuffer = bufferToFill.getWritePointer(1);
        float gain;
        float levelSample = 0;

        for (auto sample = 0; sample < bufferToFill.getNumSamples(); ++sample)
        {
            levelSample = 0;
            gain = masterLevel;
            for (auto & oscillator : oscillators) {
                levelSample += oscillator.getNextSample() * gain;
            }
            leftBuffer[sample] += levelSample;
            rightBuffer[sample] += levelSample;
        }
    }
}

void Armonizer::setIsOn(bool isOn_){
    isOn = isOn_;
}

void Armonizer::setMasterLevel(double masterLevel_)
{
    masterLevel = masterLevel_;
}

void Armonizer::setSampleRate(double sampleRate_){
    sampleRate = sampleRate_;
}

void Armonizer::createOscillator(int index, double freq) {
    jassert(index >= 0 && index <= 128);
    SineOscillator sineOscillator;
    oscillators.clear();
    double gain = 1.0;

    sineOscillator.setGain(gain*30);
    sineOscillator.setFrequency(freq, sampleRate);
    oscillators.push_back(sineOscillator);
}