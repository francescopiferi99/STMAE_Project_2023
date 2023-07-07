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

    addAndMakeVisible(numberOfNotes);
    numberOfNotes.addListener(this);
    numberOfNotes.setRange(1, 6, 1);

    addAndMakeVisible(markovOrder);
    markovOrder.addListener(this);
    markovOrder.setRange(1, 6, 1);

    addAndMakeVisible(velocity);
    velocity.addListener(this);
    velocity.setRange(1, 60, 1);

    numberOfNotesLabel.setText("Number of Notes", juce::dontSendNotification);
    markovOrderLabel.setText("Markov Order", juce::dontSendNotification);
    velocityLabel.setText("Velocity", juce::dontSendNotification);

    numberOfNotesLabel.setJustificationType(juce::Justification::centred);
    markovOrderLabel.setJustificationType(juce::Justification::centred);
    velocityLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(numberOfNotesLabel);
    addAndMakeVisible(markovOrderLabel);
    addAndMakeVisible(velocityLabel);

    addAndMakeVisible(sendButton);
    sendButton.addListener(this);
    sendButton.setButtonText("Update Values");
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
    // g.drawFittedText ("Vesion 0", getLocalBounds(), juce::Justification::centred, 1);
}

void ExamPifAudioProcessorEditor::resized()
{
    // Calculate the height for each slider and label
    int sliderHeight = getHeight() / 4;
    int labelWidth = getWidth() / 4;
    int buttonWidth = 100;
    int buttonHeight = 30;
    int buttonMargin = 10;

    // Set the bounds for the first slider (numberOfNotes)
    numberOfNotes.setBounds(labelWidth, 0, getWidth() - labelWidth, sliderHeight);

    // Set the bounds for the second slider (markovOrder)
    markovOrder.setBounds(labelWidth, sliderHeight, getWidth() - labelWidth, sliderHeight);

    // Set the bounds for the third slider (velocity)
    velocity.setBounds(labelWidth, 2 * sliderHeight, getWidth() - labelWidth, sliderHeight);

    // Set the bounds for the first label (numberOfNotesLabel)
    numberOfNotesLabel.setBounds(0, 0, labelWidth, sliderHeight);

    // Set the bounds for the second label (markovOrderLabel)
    markovOrderLabel.setBounds(0, sliderHeight, labelWidth, sliderHeight);

    // Set the bounds for the third label (velocityLabel)
    velocityLabel.setBounds(0, 2 * sliderHeight, labelWidth, sliderHeight);

    sendButton.setBounds(getWidth() - buttonWidth - buttonMargin, getHeight() - buttonHeight - buttonMargin, buttonWidth, buttonHeight);
}

void ExamPifAudioProcessorEditor::sliderValueChanged(Slider *slider) {

}

void ExamPifAudioProcessorEditor::buttonClicked(juce::Button *button) {
    if(button == &sendButton){
        // std::cout << armonizer->getOrder();
    }
}