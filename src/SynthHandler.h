//
// Created by Francesco Piferi on 29/06/23.
//

#ifndef PIFERI_EXAM_01_SYNTHHANDLER_H
#define PIFERI_EXAM_01_SYNTHHANDLER_H

#endif //PIFERI_EXAM_01_SYNTHHANDLER_H

#pragma once

#include <JuceHeader.h>
#include "SineOscillator.h"
#include "CustomOscillator.h"

class SynthHandler{
    static SynthHandler* synthHandler;
    double sampleRate;
    bool isOn;

    float masterLevel = 0.0f;
    CustomOscillator* oscillators[128];
    SynthHandler();

public:
    static SynthHandler* getSynthHandler();
    void createOscillator(int index, double freq);
    void setSampleRate(double sampleRate_);
    void setMasterLevel(double masterLevel_);

    void reset(int index);
    void resetAll();
    void setIsOn(bool isOn_);

    void getNextAudioBlock(juce::AudioBuffer<float>& bufferToFill);
};