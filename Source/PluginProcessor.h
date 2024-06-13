/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SharedImages.h"
#define MAX_DELAY_TIME 2
//==============================================================================
/**
*/
class ChorusPedalAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ChorusPedalAudioProcessor();
    ~ChorusPedalAudioProcessor() override;

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
    
    juce::AudioProcessorValueTreeState apvts;
    
    SharedImages* getSharedImagesPtr() { return m_pSharedImagesPtr; };
    
    float lin_interp(float sample_x, float sample_x1, float inPhase);
    
    float cubic_interp(float y0, float y1, float y2, float y3, float frac);
    
    void setBypass(bool bypass) { bypassed = bypass;};
    
private:
    
    juce::SharedResourcePointer<SharedImages>     m_pSharedImagesPtr;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    
    bool bypassed;
    
    juce::LinearSmoothedValue<float> depth;
    juce::LinearSmoothedValue<float> rate;
    juce::LinearSmoothedValue<float> feedback;
    juce::LinearSmoothedValue<float> delayTime;
    juce::LinearSmoothedValue<float> mix;
    
    float lfoPhase;
    
    float feedbackLeft;
    float feedbackRight;
        
    int ringBufferWriteHead;
    int ringBufferLength;
        
    float* ringBufferLeft;
    float* ringBufferRight;
    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusPedalAudioProcessor)
};
