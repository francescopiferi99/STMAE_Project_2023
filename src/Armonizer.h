//
// Created by Francesco Piferi on 02/07/23.
//

#ifndef PIFERI_EXAM_01_ARMONIZER_H
#define PIFERI_EXAM_01_ARMONIZER_H

#endif //PIFERI_EXAM_01_ARMONIZER_H

#include "SynthHandler.h"
#include "MarkovManager.h"
#include <vector>

class Armonizer{
    static Armonizer* armonizer;
    std::vector<SineOscillator> oscillators;
    Armonizer();
    int sliderValue;
    MarkovManager mm;
    void updateOscillators();
    bool isOn;
    float masterLevel = 0.0f;
    double sampleRate;


public:
    float getNextSample();
    void setSampleRate(double sampleRate_);
    void setOrderValue(int newValue);
    int getOrder();
    static Armonizer* getArmonizer();
    void createOscillator(int index, double freq);
    void getNextAudioBlock(juce::AudioBuffer<float>& bufferToFill);
    void setIsOn(bool isOn_);
    void setMasterLevel(double masterLevel_);

};