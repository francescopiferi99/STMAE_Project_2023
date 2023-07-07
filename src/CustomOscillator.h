//
// Created by Francesco Piferi on 29/06/23.
//

#ifndef PIFERI_EXAM_01_CUSTOMOSCILLATOR_H
#define PIFERI_EXAM_01_CUSTOMOSCILLATOR_H

#endif //PIFERI_EXAM_01_CUSTOMOSCILLATOR_H

#include "SineOscillator.h"
#include <vector>
#pragma once

class CustomOscillator{
    float currentAngle = 0.0f, andleDelta = 0.0f;
    float gain = 0.0f;

    std::vector<SineOscillator*> sineOscillators;

public:
    CustomOscillator();
    float getNextSample() noexcept;
    void addSineOscillator(SineOscillator* oscillator);
    void resetOscillators();

private:
    std::vector<SineOscillator> oscillators;
};