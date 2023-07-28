/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ExamPifAudioProcessorEditorModifyArmonizerPage.h"

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
    void addItem(state_sequence sequence);
    void comboChanged(ComboBox* combo);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ExamPifAudioProcessor& audioProcessor;

    bool comboPopUpOpen = false;

    void updateComboBoxItems();

    juce::Slider numberOfNotes;
    juce::Slider markovOrder;
    juce::Slider duration;

    juce::Label numberOfNotesLabel;
    juce::Label markovOrderLabel;
    juce::Label velocityLabel;

    juce::TextButton sendButton;

    juce::TextButton createButton;
    juce::TextButton saveButton;
    juce::ComboBox saveSequences;

    juce::TextButton reset;
    juce::TextButton saveLastSequence;

    Armonizer* armonizer = Armonizer::getArmonizer();
    void newComboBoxItem();
    std::vector<int> convert(state_sequence notes);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExamPifAudioProcessorEditor)
};