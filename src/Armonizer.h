//
// Created by Francesco Piferi on 02/07/23.
//

#ifndef PIFERI_EXAM_01_ARMONIZER_H
#define PIFERI_EXAM_01_ARMONIZER_H

#endif //PIFERI_EXAM_01_ARMONIZER_H

#include "MarkovManager.h"
#include "SineOscillator.h"
#include <JuceHeader.h>
#include <vector>


class Armonizer{
    static Armonizer* armonizer;
    std::vector<SineOscillator> oscillators;
    Armonizer();
    int length; // Number of notes in an Armonizer
    int order; // Markon order
    int velocity; // Duration of the notes
    MarkovManager mm; // Markov Chain
    void updateOscillators();
    bool isOn; // Bool to control the playback session
    float masterLevel = 1.0f; // Master volume
    double sampleRate = 44100; // Sample rate, by default 44100
    void exampleArmonizer();
    state_single fromNoteNumberToName(int noteNumber);
    double fromNameToFirstFrequecy(state_single);
    int currentOscillatorIndex = 0; // Index for the playback session
    double oscillatorDuration = 0.2; // Duration of each note
    double timeElapsed = 0.0; // Times between the beginning of the the notes and the current time
    state_sequence sequence; // Sequence of notes
    std::vector<state_sequence> database; // Last 10 sequences created
    std::vector<int> fromNameToNumber(state_sequence sequence);

public:
    bool creation = false; // Bool to control the creation session
    std::vector<state_sequence> getDatabase();
    float getNextSample();
    void setSampleRate(double sampleRate_);
    void setLengthOfList(int newValue);
    int getMaxOrder();
    int getLength();
    int getVelocity();
    static Armonizer* getArmonizer();
    void createOscillators(int index, double freq);
    void createOscillators(double freq);

    void getNextAudioBlock(juce::AudioBuffer<float>& bufferToFill);
    void setIsOn(bool isOn_);
    void setMasterLevel(double masterLevel_);
    void reset();
    void changeModel(const std::string& filename);
    std::vector<state_single> createSequence(state_single first);
    SineOscillator getOscillator(int index);
    void setMaxOrder(int newMaxOrder);
    void initialize();
    void newSequence();
    void saveSequence();
    void addSequence(int noteNumber);
    void setOscillatorDuration(double durationInSeconds);
    void resetArmonizer();
    void printSequence();
    state_sequence getSequence();
    void writeToExternalFile(const std::string& filename, int index);
    void writeMidiFile(const std::string& filename, const std::vector<int>& notes);
};