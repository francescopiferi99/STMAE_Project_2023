/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ExamPifAudioProcessorEditor::ExamPifAudioProcessorEditor (ExamPifAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(frequencySlider);
    frequencySlider.addListener(this);
    frequencySlider.setRange(80, 8000);
    //frequencySlider.setValue(440);
}

ExamPifAudioProcessorEditor::~ExamPifAudioProcessorEditor()
{
}

//==============================================================================
void ExamPifAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Vesion 0", getLocalBounds(), juce::Justification::centred, 1);
}

void ExamPifAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    frequencySlider.setBounds(0,0,getWidth(), getHeight()/5);
}

void ExamPifAudioProcessorEditor::sliderValueChanged(Slider *slider) {
    if(slider == &frequencySlider){
        audioProcessor.setDPhase(slider->getValue());
    }
}
