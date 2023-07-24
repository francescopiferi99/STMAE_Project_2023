//
// Created by Francesco Piferi on 02/07/23.
//

#ifndef PIFERI_EXAM_01_ARMONIZER_H
#define PIFERI_EXAM_01_ARMONIZER_H

#endif //PIFERI_EXAM_01_ARMONIZER_H

#include "MarkovManager.h"
// #include "SynthHandler.h"
#include "SineOscillator.h"
#include <JuceHeader.h>
#include <vector>


class Armonizer{
    static Armonizer* armonizer;
    std::vector<SineOscillator> oscillators;
    Armonizer();
    int length;
    int order;
    int velocity;
    MarkovManager mm;
    void updateOscillators();
    bool isOn;
    float masterLevel = 10.0f;
    double sampleRate = 44100;
    void exampleArmonizer();
    state_single fromNoteNumberToName(int noteNumber);
    double fromNameToFirstFrequecy(state_single);
    int currentOscillatorIndex = 0;
    double oscillatorDuration = 0.2; // 0.2 seconds for each oscillator
    double timeElapsed = 0.0;


public:
    bool creation = false;
    float getNextSample();
    void setSampleRate(double sampleRate_);
    void setLengthOfList(int newValue);
    int getMaxOrder();
    int getLength();
    int getVelocity();
    static Armonizer* getArmonizer();
    void createOscillators(int index, double freq);
    void getNextAudioBlock(juce::AudioBuffer<float>& bufferToFill);
    void setIsOn(bool isOn_);
    void setMasterLevel(double masterLevel_);
    void reset();
    void changeModel(const std::string& filename);
    std::vector<state_single> createSequence(state_single first);
    SineOscillator getOscillator(int index);
    void setMaxOrder(int newMaxOrder);
    void initialize();
    void newSequence();
    void saveSequence();
    void addSequence(int noteNumber);
    void setOscillatorDuration(double durationInSeconds);
    void resetArmonizer();
    };