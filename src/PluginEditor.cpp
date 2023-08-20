/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include <__filesystem/path.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ExamPifAudioProcessorEditor::ExamPifAudioProcessorEditor (ExamPifAudioProcessor& p)
        : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    // number of notes is the number of oscillators that the Armonizer will play sequentially
    addAndMakeVisible(numberOfNotes);
    numberOfNotes.addListener(this);
    numberOfNotes.setRange(1, 60, 1);
    numberOfNotes.setValue(30);

    // MarkovOrder is the order of the markov Chain
    addAndMakeVisible(markovOrder);
    markovOrder.addListener(this);
    markovOrder.setRange(1, 4, 1);
    markovOrder.setValue(2);

    // Slider to set the duration of each note
    addAndMakeVisible(duration);
    duration.addListener(this);
    duration.setRange(0.1, 1, 0.01);
    duration.setValue(0.2);

    // Labels
    numberOfNotesLabel.setText("Number of Notes", juce::dontSendNotification);
    markovOrderLabel.setText("Markov Order", juce::dontSendNotification);
    velocityLabel.setText("Velocity", juce::dontSendNotification);

    numberOfNotesLabel.setJustificationType(juce::Justification::centred);
    markovOrderLabel.setJustificationType(juce::Justification::centred);
    velocityLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(numberOfNotesLabel);
    addAndMakeVisible(markovOrderLabel);
    addAndMakeVisible(velocityLabel);

    // Button to update the values of the sliders
    addAndMakeVisible(sendButton);
    sendButton.addListener(this);
    sendButton.setButtonText("Update Values");

    // Button to start creating
    addAndMakeVisible(createButton);
    createButton.addListener(this);
    createButton.setButtonText("New Pattern");

    // Button to save the the new sequence
    addAndMakeVisible(saveButton);
    saveButton.addListener(this);
    saveButton.setButtonText("Save");

    // Button to restore the values and the markov chain
    addAndMakeVisible(reset);
    reset.addListener(this);
    reset.setButtonText("Reset");

    // Button to save the last sequence
    addAndMakeVisible(saveLastSequence);
    saveLastSequence.addListener(this);
    saveLastSequence.setButtonText("Save Sequence");

    // Combobox to save the sequences
    addAndMakeVisible(saveSequences);
    saveSequences.addItem("Save Your Melody", 1);
    saveSequences.addItem("Save Last Melody", 2);
    saveSequences.addItem("Save Penultimate Melody", 3);
    saveSequences.addItem("Save 3th Melody", 4);
    saveSequences.addItem("Save 4th Melody", 5);
    saveSequences.addItem("Save 5th Melody", 6);
    saveSequences.addItem("Save 6th Melody", 7);
    saveSequences.addItem("Save 7th Melody", 8);
    saveSequences.addItem("Save 8th Melody", 9);
    saveSequences.addItem("Save 9th Melody", 10);
    saveSequences.addItem("Save 10th Melody", 11);
    saveSequences.setSelectedId(1);
    saveSequences.onChange = [this] { comboChanged(&saveSequences); };

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

    // Set the bounds for the third slider (duration)
    duration.setBounds(labelWidth, 2 * sliderHeight, getWidth() - labelWidth, sliderHeight);

    // Set the bounds for the first label (numberOfNotesLabel)
    numberOfNotesLabel.setBounds(0, 0, labelWidth, sliderHeight);

    // Set the bounds for the second label (markovOrderLabel)
    markovOrderLabel.setBounds(0, sliderHeight, labelWidth, sliderHeight);

    // Set the bounds for the third label (velocityLabel)
    velocityLabel.setBounds(0, 2 * sliderHeight, labelWidth, sliderHeight);

    sendButton.setBounds(getWidth() - buttonWidth - buttonMargin, getHeight() - buttonHeight - buttonMargin, buttonWidth, buttonHeight);

    createButton.setBounds(buttonMargin, getHeight() - 2 * buttonHeight - 2 * buttonMargin, buttonWidth, buttonHeight);

    // Create the saveButton
    saveButton.setBounds(buttonMargin, getHeight() - buttonHeight - buttonMargin, buttonWidth, buttonHeight);

    reset.setBounds((getWidth() - buttonWidth - buttonMargin)/2, getHeight() - buttonHeight - buttonMargin, buttonWidth, buttonHeight);

    saveSequences.setBounds((getWidth() - buttonWidth - buttonMargin)/2, getHeight() - 2 * buttonHeight - 2 * buttonMargin, buttonWidth, buttonHeight);
}

void ExamPifAudioProcessorEditor::sliderValueChanged(Slider *slider) {

}

void ExamPifAudioProcessorEditor::buttonClicked(juce::Button *button) {
    if(button == &sendButton){
        armonizer->setLengthOfList(static_cast<int>(numberOfNotes.getValue()));
        armonizer->setMaxOrder(static_cast<int>(markovOrder.getValue()));
        armonizer->setOscillatorDuration(duration.getValue());
    }
    if(button == &createButton){
        armonizer->newSequence();
    }
    if(button == &saveButton){
        armonizer->saveSequence();
        armonizer->setLengthOfList(static_cast<int>(numberOfNotes.getValue()));
        armonizer->setMaxOrder(static_cast<int>(markovOrder.getValue()));
        armonizer->setOscillatorDuration(duration.getValue());
    }
    if(button == &reset){
        armonizer->resetArmonizer();
        numberOfNotes.setValue(30);
        markovOrder.setValue(2);
        duration.setValue(0.2);
        armonizer->setLengthOfList(static_cast<int>(numberOfNotes.getValue()));
        armonizer->setMaxOrder(static_cast<int>(markovOrder.getValue()));
        armonizer->setOscillatorDuration(duration.getValue());
    }
}

void ExamPifAudioProcessorEditor::comboChanged(juce::ComboBox * combo){
    std::vector<state_sequence> db = armonizer->getDatabase();
    if(combo == &saveSequences && saveSequences.getSelectedId() < armonizer->getDatabase().size() + 2 && saveSequences.getSelectedId() != 1){
        state_sequence notes = db[saveSequences.getSelectedId()-2];
        std::vector<int> numbers = convert(notes);
        std::string path = std::filesystem::path(__FILE__).parent_path().string() + "/output.mid";

        armonizer->writeMidiFile(path, numbers);
        saveSequences.setSelectedId(1);
    }
}

std::vector<int> ExamPifAudioProcessorEditor::convert(state_sequence notes) {
    std::vector<int> numbers;
    numbers.clear();
    for (int i = 0; i < notes.size(); i++) {
        if (notes[i] == "C") numbers.push_back(60);
        else if (notes[i] == "C#") numbers.push_back(61);
        else if (notes[i] == "D") numbers.push_back(62);
        else if (notes[i] == "D#") numbers.push_back(63);
        else if (notes[i] == "E") numbers.push_back(64);
        else if (notes[i] == "F") numbers.push_back(65);
        else if (notes[i] == "F#") numbers.push_back(66);
        else if (notes[i] == "G") numbers.push_back(67);
        else if (notes[i] == "G#") numbers.push_back(68);
        else if (notes[i] == "A") numbers.push_back(69);
        else if (notes[i] == "A#") numbers.push_back(70);
        else if (notes[i] == "B") numbers.push_back(71);
        else {
            // Handle the case when an unrecognized note is encountered
            // Print an error message and stop adding notes to the numbers vector.
            std::cerr << "Error: Unrecognized note: " << notes[i] << std::endl;
            break;
        }
    }
    return numbers;
}
