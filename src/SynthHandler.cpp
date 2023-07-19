//
// Created by Francesco Piferi on 29/06/23.
//

#include "SynthHandler.h"
#include "CustomOscillator.h"

#pragma once

SynthHandler* SynthHandler::synthHandler = NULL;

SynthHandler::SynthHandler() {
    for (int i = 0; i < 128; i++) {
        oscillators[i] = new CustomOscillator(); // TODO: create a function that modifies the order accordingly with a slider
    }
}

// Singleton
SynthHandler* SynthHandler::getSynthHandler() {
    if (synthHandler == NULL) {
        synthHandler = new SynthHandler();
    }
    return synthHandler;
}

void SynthHandler::createOscillator(int index, double freq) {
    jassert(index >= 0 && index <= 128);
    SineOscillator* sineOscillator;
    oscillators[index]->resetOscillators();
    double gain = 1.0;

    sineOscillator = new SineOscillator(gain*30);
    sineOscillator->setFrequency(freq, sampleRate);
    oscillators[index]->addSineOscillator(sineOscillator);
}

void SynthHandler::getNextAudioBlock(juce::AudioBuffer<float> &bufferToFill) {
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
                levelSample += oscillator->getNextSample() * gain;
            }
            leftBuffer[sample] += levelSample;
            rightBuffer[sample] += levelSample;
        }
    }
}

void SynthHandler::setSampleRate(double sampleRate_){
    sampleRate = sampleRate_;
}

void SynthHandler::setMasterLevel(double masterLevel_)
{
    masterLevel = masterLevel_;
}

void SynthHandler::reset(int index) {
    jassert(index >= 0 && index <= 127);
    oscillators[index]->resetOscillators();
}

void SynthHandler::resetAll() {
    for(auto & oscillator : oscillators) {
        oscillator->resetOscillators();
    }
}

void SynthHandler::setIsOn(bool isOn_){
    isOn = isOn_;
}