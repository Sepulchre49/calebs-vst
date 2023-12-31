/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FirstOrderFeedbackFilter.h"
#include "Biquad.h"

//==============================================================================
/**
*/
class CalebsvstAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    CalebsvstAudioProcessor();
    ~CalebsvstAudioProcessor() override;

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

    friend class CalebsvstAudioProcessorEditor;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CalebsvstAudioProcessor);

    double gain;
    double muted = 1.0;
    bool toggleLPF = false;
    bool toggleBiquad = false;

    FirstOrderFeedforwardFilter filters[2] = { FirstOrderFeedforwardFilter(0.1,0.1), FirstOrderFeedforwardFilter(0.1,0.1) };
    Biquad biquads[2] = { Biquad(1.0, 0.73, 1.0, -0.78, 0.88), Biquad(1.0, 0.73, 1.0, -0.78, 0.88) };
};
