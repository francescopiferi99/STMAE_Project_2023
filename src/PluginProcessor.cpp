/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MarkovManager.h"
#include "MarkovChain.h"

//==============================================================================
ExamPifAudioProcessor::ExamPifAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    phase = 0;
    dphase = 0;
    frequency = 440;
    amp = 0;
    count = 0;
}

ExamPifAudioProcessor::~ExamPifAudioProcessor()
{
}

//==============================================================================
const juce::String ExamPifAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ExamPifAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ExamPifAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ExamPifAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ExamPifAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ExamPifAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ExamPifAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ExamPifAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ExamPifAudioProcessor::getProgramName (int index)
{
    return {};
}

void ExamPifAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ExamPifAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    dphase = ExamPifAudioProcessor::getDPhase(frequency, sampleRate);
}

void ExamPifAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ExamPifAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ExamPifAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    bool isOn = false;
    juce::MidiBuffer processedMidi;
    armonizer->setSampleRate(getSampleRate());


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumOutputChannels; ++channel){
        if (channel == 0){
            auto* channelDataL = buffer.getWritePointer (channel);
            auto* channelDataR = buffer.getWritePointer (channel+1);
            int numSamples = buffer.getNumSamples();

            for (int sInd = 0; sInd < numSamples; ++sInd){
                channelDataL[sInd] = (float) (std::sin(phase) * amp);
                channelDataR[sInd] = (float) (std::sin(phase) * amp);
                phase += dphase;
                if (amp > 0 && !isOn)
                    amp *= 0.9999;  // Reduce the amplitude gradually for fade-out effect
            }
        }
    }

    for (const auto metadata : midiMessages){
        auto message = metadata.getMessage();
        const auto time = metadata.samplePosition;
        DBG("processBlock:: Got message " << message.getNoteNumber());
        if (message.isNoteOn()){
            isOn = true;
            amp = 1;
            frequency = juce::MidiMessage::getMidiNoteInHertz(message.getNoteNumber());
            dphase = this->getDPhase(frequency, getSampleRate());
            break;
        }
        if (message.isNoteOff()){
            // No need to change anything for the note-off event
        }
        processedMidi.addEvent(message, time);
    }

    for(const auto metadata : midiMessages){
        auto message = metadata.getMessage();
        const auto time = metadata.samplePosition;
        DBG("processBlock:: Got message " << message.getNoteNumber());
        if(message.isNoteOn()){
            int midiNote = message.getNoteNumber();
            double fundFreq = message.getMidiNoteInHertz(midiNote);
            armonizer->createOscillator(midiNote, fundFreq);
        }
        else if(message.isNoteOff()){
            int midiNote = message.getNoteNumber();
        }
        processedMidi.addEvent(message, time);
    }
    midiMessages.swapWith(processedMidi);
    armonizer->getNextAudioBlock(buffer);
}

//==============================================================================
bool ExamPifAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ExamPifAudioProcessor::createEditor()
{
    return new ExamPifAudioProcessorEditor (*this);
}

//==============================================================================
void ExamPifAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ExamPifAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ExamPifAudioProcessor();
}

double ExamPifAudioProcessor::getDPhase(double freq, double sampleRate){
    double two_pi = 3.1415927 * 2;
    return (two_pi / sampleRate) * freq;
}

void ExamPifAudioProcessor::setDPhase(double freq){
    frequency = freq;
    dphase = getDPhase(frequency, getSampleRate());
}
