/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ExamPifAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener, public juce::Button::Listener
{
public:
    ExamPifAudioProcessorEditor (ExamPifAudioProcessor&);
    ~ExamPifAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;
    void buttonClicked(Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ExamPifAudioProcessor& audioProcessor;

    juce::Slider numberOfNotes;
    juce::Slider markovOrder;
    juce::Slider velocity;

    juce::Label numberOfNotesLabel;
    juce::Label markovOrderLabel;
    juce::Label velocityLabel;

    juce::TextButton sendButton;

    Armonizer* armonizer = Armonizer::getArmonizer();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExamPifAudioProcessorEditor)
};
