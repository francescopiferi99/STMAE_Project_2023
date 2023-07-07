//
// Created by Francesco Piferi on 29/06/23.
//

#ifndef PIFERI_EXAM_01_SINEOSCILLATOR_H
#define PIFERI_EXAM_01_SINEOSCILLATOR_H

#endif //PIFERI_EXAM_01_SINEOSCILLATOR_H

#pragma once

class SineOscillator
{
public:
    SineOscillator(float gain_);
    SineOscillator();
    void setFrequency (float frequency, float sampleRate);
    float getNextSample() noexcept;
    void updateAngle() noexcept;
    float getGain();
    void setGain(float gain_);

private:
    float currentAngle = 0.0f, angleDelta = 0.0f;
    float gain = 0.0f;
};