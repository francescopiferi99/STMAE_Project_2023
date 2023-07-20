/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthHandler.h"
#include "Armonizer.h"
//==============================================================================
/**
*/
class ExamPifAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ExamPifAudioProcessor();
    ~ExamPifAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    double getDPhase(double freq, double sampleRate);

public:
    void setDPhase(double freq);
    int count;

private:
    double phase;
    double dphase;
    double frequency;
    double amp;
    int currentNote;
    int noteCurrentlyPlaying;

    Armonizer* armonizer = Armonizer::getArmonizer(); // Singleton
    SynthHandler* synthHandler = SynthHandler::getSynthHandler();
    std::vector<state_single> sequence; // = armonizer->createSequence();

    state_single convert_midi_note_to_string(int midi_note);

        //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExamPifAudioProcessor)
};
