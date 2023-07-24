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
        // armonizer->createSequence("A");
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
            if (timeElapsed >= oscillatorDuration) {
                // Move to the next oscillator
                currentOscillatorIndex = (currentOscillatorIndex + 1) % length;
                timeElapsed = 0.0;
            }

            levelSample = 0;
            gain = masterLevel;
            levelSample += oscillators[currentOscillatorIndex].getNextSample();
            leftBuffer[sample] += levelSample;
            rightBuffer[sample] += levelSample;

            timeElapsed += 1.0 / sampleRate;
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

void Armonizer::setOscillatorDuration(double durationInSeconds) {
    oscillatorDuration = durationInSeconds;
}

void Armonizer::createOscillators(int index, double freq) {
    jassert(index >= 0 && index <= 128);
    double gain = 1.0;
    updateOscillators();
    int noteNumber = (int)round(69 + 12 * log2(freq / 440.0));
    state_single note = fromNoteNumberToName(noteNumber);
    std::cout << note << " This is the first " << std::endl;
    state_sequence sequence = createSequence(note);

    for(int i = 0; i < length; i++){
        oscillators[i].setGain(gain*30);
        double frequence = fromNameToFirstFrequecy(sequence[i]);
        std::cout << "i: " << i << " Note: " << sequence[i] << " freq: " << frequence << std::endl;
        bool end = true;
        // while to take rebase the octave
        while(end){
            if(frequence < freq) frequence *= 2;
            else end = false;
        }
        oscillators[i].setFrequency(frequence, sampleRate);
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
    mm.putEvent("F");
    mm.putEvent("E");
    mm.putEvent("A");
    mm.putEvent("D");
    mm.putEvent("D");
    mm.putEvent("A#");
    mm.putEvent("C");
    mm.putEvent("F");
    mm.putEvent("C");
    mm.putEvent("D");
    mm.putEvent("G");
    mm.putEvent("A#");
    mm.putEvent("F");
    mm.putEvent("F");
    mm.putEvent("E");
    mm.putEvent("A");
    mm.putEvent("D");
    mm.putEvent("D");
    mm.putEvent("A#");
    mm.putEvent("C");
    mm.putEvent("F");
    mm.putEvent("C");
    mm.putEvent("D");
    mm.putEvent("G");
    mm.putEvent("A#");
    mm.putEvent("F");
    mm.putEvent("A");
    mm.putEvent("A");
    mm.putEvent("D");
    mm.putEvent("C");
    mm.putEvent("A#");
    mm.putEvent("D");
    mm.putEvent("G");
    mm.putEvent("C");
    mm.putEvent("F");
    mm.putEvent("A");
    mm.putEvent("A");
    mm.putEvent("D");
    mm.putEvent("C");
    mm.putEvent("A#");
    mm.putEvent("D");
    mm.putEvent("G");
    mm.putEvent("C");
    mm.putEvent("F");
    mm.putEvent("F");
    mm.putEvent("F");
    mm.putEvent("E");
    mm.putEvent("A");
    mm.putEvent("D");
    mm.putEvent("D");
    mm.putEvent("A#");
    mm.putEvent("C");
    mm.putEvent("F");
    mm.putEvent("C");
    mm.putEvent("D");
    mm.putEvent("G");
    mm.putEvent("A#");
    mm.putEvent("F");
    mm.putEvent("A");
    mm.putEvent("A");
    mm.putEvent("D");
    mm.putEvent("C");
    mm.putEvent("A#");
    mm.putEvent("D");
    mm.putEvent("G");
    mm.putEvent("C");
    mm.putEvent("F");
    mm.putEvent("A");
    mm.putEvent("A");
    mm.putEvent("D");
    mm.putEvent("C");
    mm.putEvent("A#");
    mm.putEvent("D");
    mm.putEvent("G");
    mm.putEvent("C");
    mm.putEvent("F");
    mm.putEvent("F");
    mm.putEvent("F");
    mm.putEvent("E");
    mm.putEvent("A");
    mm.putEvent("D");
    mm.putEvent("D");
    mm.putEvent("A#");
    mm.putEvent("C");
    mm.putEvent("F");
    mm.putEvent("C");
    mm.putEvent("D");
    mm.putEvent("G");
    mm.putEvent("A#");
    mm.putEvent("F");
    mm.putEvent("G");
    mm.putEvent("A#");
    mm.putEvent("F");


}

void Armonizer::initialize(){
    updateOscillators();
}

void Armonizer::newSequence(){
    creation = true;
    mm.reset();
}

void Armonizer::saveSequence(){
    creation = false;
    std::cout << "New Sequence correctly inserted!" << std::endl;
    /*
    std::cout << mm.getModelAsString();
    for (auto i=0;i<50;++i){
        state_single next = mm.getEvent();
        int order = mm.getOrderOfLastEvent();
        std::cout << "Next state " << next << " order " << order << std::endl;
    }
    */
}

void Armonizer::addSequence(int noteNumber){
    state_single note;
    // std::cout << "noteNumber%12:  " << noteNumber%12 << std::endl;
    note = fromNoteNumberToName(noteNumber);
    // std::cout << "note:  " << note << std::endl;
    mm.putEvent(note);
}

state_single Armonizer::fromNoteNumberToName(int noteNumber){
    switch (noteNumber % 12) {
        case 0:
            return "C";
        case 1:
            return "C#";
        case 2:
            return "D";
        case 3:
            return "D#";
        case 4:
            return "E";
        case 5:
            return "F";
        case 6:
            return "F#";
        case 7:
            return "G";
        case 8:
            return "G#";
        case 9:
            return "A";
        case 10:
            return "A#";
        case 11:
            return "B";
        default:
            return "";
    }
}

double Armonizer::fromNameToFirstFrequecy(state_single note){
    double firstFreq;
    if (note == "A") return 440.0/4;
    else if (note == "A#") return 466.164/4;
    else if (note == "B") return 493.883/4;
    else if (note == "C") return 523.251/4;
    else if (note == "C#") return 554.365/4;
    else if (note == "D") return 587.330/4;
    else if (note == "D#") return 622.254/4;
    else if (note == "E") return 659.255/4;
    else if (note == "F") return 698.456/4;
    else if (note == "F#") return 739.989/4;
    else if (note == "G") return 783.991/4;
    else if (note == "G#") return 830.609/4;
    else return 0.0;
}

void Armonizer::resetArmonizer(){
    armonizer->setLengthOfList(3);
    armonizer->setMaxOrder(1);
    armonizer->exampleArmonizer();
}

