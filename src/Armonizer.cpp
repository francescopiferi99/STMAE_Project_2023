//
// Created by Francesco Piferi on 02/07/23.
//

#include "Armonizer.h"
#include "MarkovManager.h"

#pragma once

Armonizer* Armonizer::armonizer = NULL;

Armonizer::Armonizer() {
    updateOscillators();
}

Armonizer* Armonizer::getArmonizer(){
    if (armonizer == NULL) {
        armonizer = new Armonizer();
        armonizer->setLengthOfList(3);
        armonizer->setMaxOrder(1);
        armonizer->exampleArmonizer();
        armonizer->createSequence("A");
    }
    return armonizer;
}

void Armonizer::setLengthOfList(int newValue)
{
    length = newValue;
    updateOscillators();
}

int Armonizer::getLength(){
    return length;
}

void Armonizer::setMaxOrder(int newMaxOrder){
    mm.setMaxOrder(newMaxOrder);
}


int Armonizer::getMaxOrder(){
    return order;
}

int Armonizer::getVelocity() {
    return velocity;
}


void Armonizer::updateOscillators()
{
    // Clear existing oscillators
    oscillators.clear();

    for (int i = 0; i < length; ++i)
    {
        SineOscillator sineOscillator;
        oscillators.push_back(sineOscillator);
    }
}

std::vector<state_single> Armonizer::createSequence(state_single first){
    std::vector<state_single> sequence;
    sequence.emplace_back(first);
    for(int i = 1; i < length; i++){
        sequence.push_back(mm.getEvent(sequence));
    }
    return sequence;
}

void Armonizer::getNextAudioBlock(juce::AudioBuffer<float>& bufferToFill) {
    if (isOn) {
        auto* leftBuffer = bufferToFill.getWritePointer(0);
        auto* rightBuffer = bufferToFill.getWritePointer(1);
        float gain;
        float levelSample = 0;
        for (auto sample = 0; sample < bufferToFill.getNumSamples(); ++sample)
        {
            levelSample = 0;
            gain = masterLevel;
            for (int i = 0; i < length; i++) {
                levelSample += oscillators[i].getNextSample();
            }
            leftBuffer[sample] += levelSample;
            rightBuffer[sample] += levelSample;
        }
    }
    else updateOscillators();
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

void Armonizer::createOscillators(int index, double freq) {
    jassert(index >= 0 && index <= 128);
    double gain = 1.0;
    updateOscillators();
    for(int i = 0; i < length; i++){
        oscillators[i].setGain(gain*30);
        oscillators[i].setFrequency(freq + i, sampleRate);
    }
}

void Armonizer::reset() {
    oscillators.clear();
}

void Armonizer::changeModel(const std::string& filename){
    mm.loadModel(filename);
}

// Return the oscillator with index number equals to index
SineOscillator Armonizer::getOscillator(int index){
    return oscillators[index];
}

void Armonizer::exampleArmonizer(){
    mm.reset();
    mm.putEvent("A");
    mm.putEvent("B");
    mm.putEvent("C");
    mm.putEvent("A");
    mm.putEvent("B");
    mm.putEvent("H");
    mm.putEvent("H");
    mm.putEvent("A");
}


void Armonizer::initialize(){
    armonizer->updateOscillators();
}