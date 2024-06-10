/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChorusPedalAudioProcessor::ChorusPedalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
apvts(*this, nullptr, "params", createParams())
//maxDelay(getSampleRate() * .03), chorus(maxDelay, getSampleRate())
{
    lfoPhase = 0;
    
    ringBufferLeft = nullptr;
    ringBufferRight = nullptr;
    
    ringBufferWriteHead = 0;
    ringBufferLength = 0;
    
    feedbackLeft = 0;
    feedbackRight = 0;
}

ChorusPedalAudioProcessor::~ChorusPedalAudioProcessor()
{
    if(ringBufferLeft != nullptr) {
        delete [] ringBufferLeft;
        ringBufferLeft = nullptr;
    }
    if(ringBufferRight != nullptr) {
        delete [] ringBufferRight;
        ringBufferRight = nullptr;
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout ChorusPedalAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB1", 1}, "Depth", 0.f, 1.f, 0.5));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB2", 2}, "Rate", 0.1f, 10.f, 1.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB3", 3}, "Intensity", 0.f, 1.f, 0.5));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB4", 4}, "Delay Time", 5.f, 50.f, 10.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB5", 5}, "Feedback", 0.f, 98.f, 0.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB6", 6}, "Mix", 0.f, 100.f, 50.f));
    
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{"BUTTON1", 7}, "Bypass", false));
    
    return {params.begin(), params.end()};
    
}
//==============================================================================
const juce::String ChorusPedalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChorusPedalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChorusPedalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChorusPedalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ChorusPedalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChorusPedalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChorusPedalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChorusPedalAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ChorusPedalAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChorusPedalAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ChorusPedalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    depth.reset(sampleRate, 0.0005);
    rate.reset(sampleRate, 0.0005);
    delayTime.reset(sampleRate, 0.0005);
    feedback.reset(sampleRate, 0.0005);
    mix.reset(sampleRate, 0.0005);
    
    lfoPhase = 0;
    
    ringBufferLength = sampleRate * MAX_DELAY_TIME;
    
    if(ringBufferLeft == nullptr) {
        ringBufferLeft = new float[ringBufferLength];
    }
    
    juce::zeromem(ringBufferLeft, ringBufferLength * sizeof(float));
    
    if(ringBufferRight == nullptr) {
        ringBufferRight = new float[ringBufferLength];
    }
    
    juce::zeromem(ringBufferRight, ringBufferLength * sizeof(float));
    
    ringBufferWriteHead = 0;
}

void ChorusPedalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChorusPedalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ChorusPedalAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    
    auto d = apvts.getRawParameterValue("KNOB1")->load();
    depth.setTargetValue(d);
    auto r = apvts.getRawParameterValue("KNOB2")->load();
    rate.setTargetValue(r);
    auto dt = apvts.getRawParameterValue("KNOB4")->load() / 1000;
    delayTime.setTargetValue(dt);
    auto fb = apvts.getRawParameterValue("KNOB5")->load() / 100;
    feedback.setTargetValue(fb);
    auto m = apvts.getRawParameterValue("KNOB6")->load() / 100;
    mix.setTargetValue(m);
    
    bool bypass = *apvts.getRawParameterValue("BUTTON1") > 0.5f ? true : false;
    
    if(bypass)
    {
        return;
    }
    
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);
    
    float phaseOffset = 0.0f;
    float lfoRate = rate.getNextValue();
    float phaseOffsetIncrement = lfoRate / getSampleRate();
    
    for(int i = 0; i < buffer.getNumSamples(); i++) {
        // Writing to buffer and adding feedback
        ringBufferLeft[ringBufferWriteHead] = leftChannel[i] + feedbackLeft;
        ringBufferRight[ringBufferWriteHead] = rightChannel[i] + feedbackRight;
        
        // Calculating delay for left channel with LFO
        float lfoOutLeft = sin(2 * M_PI * lfoPhase);
        lfoOutLeft *= depth.getNextValue();
        
        // Calculating delay for right channel with LFO + offset
        float lfoPhaseRight = lfoPhase + phaseOffset;
        
        phaseOffset += phaseOffsetIncrement;
        
        if(lfoPhaseRight > 1) {
            lfoPhaseRight -= 1;
        }
        
        float lfoOutRight = sin(2 * M_PI * lfoPhaseRight);
        lfoOutRight *= depth.getNextValue();
        
        float lfoOutMappedLeft = 0;
        float lfoOutMappedRight = 0;
        
        // Updating LFO phase
        lfoPhase += rate.getNextValue() / getSampleRate();
        
        
        
        lfoOutMappedLeft = juce::jmap<float>(lfoOutLeft, -1.f, 1.f, 0.005f, 0.03f);
        lfoOutMappedRight = juce::jmap<float>(lfoOutRight, -1.f, 1.f, 0.005f, 0.03f);
        
        
        float delayTimeSamplesLeft = getSampleRate() * lfoOutMappedLeft;
        float delayTimeSamplesRight = getSampleRate() * lfoOutMappedRight;
        
        if(lfoPhase > 1) {
            lfoPhase -= 1;
        }
        
        // Calculating read head for left channel delay sample
        float delayReadHeadLeft = ringBufferWriteHead - delayTimeSamplesLeft;
        
        if(delayReadHeadLeft < 0) {
            delayReadHeadLeft += ringBufferLength;
        }
        
        int readHeadLeft_x = (int) delayReadHeadLeft;
        int readHeadLeft_x1 = readHeadLeft_x + 1;
        float readHeadFloatLeft = delayReadHeadLeft - readHeadLeft_x;
        
        if(readHeadLeft_x1 >= ringBufferLength) {
            readHeadLeft_x1 -= ringBufferLength;
        }
        
        // Calculating read head for right channel delay sample
        float delayReadHeadRight = ringBufferWriteHead - delayTimeSamplesRight;
        
        if(delayReadHeadRight < 0) {
            delayReadHeadRight += ringBufferLength;
        }
        
        int readHeadRight_x = (int) delayReadHeadRight;
        int readHeadRight_x1 = readHeadRight_x + 1;
        float readHeadFloatRight = delayReadHeadRight - readHeadRight_x;
        
        if(readHeadRight_x1 >= ringBufferLength) {
            readHeadRight_x1 -= ringBufferLength;
        }
        
        // Interpolating delay samples from current read head positions for both channels
        float delay_sample_left = lin_interp(ringBufferLeft[readHeadLeft_x], ringBufferLeft[readHeadLeft_x1], readHeadFloatLeft);
        float delay_sample_right = lin_interp(ringBufferRight[readHeadRight_x], ringBufferRight[readHeadRight_x1], readHeadFloatRight);
        
        // Calculating feedback samples
        feedbackLeft = delay_sample_left * feedback.getNextValue();
        feedbackRight = delay_sample_right * feedback.getNextValue();
        
        // Updating buffer write head
        ringBufferWriteHead++;
        
        if(ringBufferWriteHead >= ringBufferLength) {
            ringBufferWriteHead = 0;
        }
        
        // Mixing sample between dry and wet signal
        float dryAmount = 1 - mix.getNextValue();
        float wetAmount = mix.getNextValue();
        
        buffer.setSample(0, i, buffer.getSample(0, i) * dryAmount + delay_sample_left * wetAmount);
        buffer.setSample(1, i, buffer.getSample(1, i) * dryAmount + delay_sample_right * wetAmount);
    }
}
float ChorusPedalAudioProcessor::lin_interp(float sample_x, float sample_x1, float inPhase)
{
    return (1 - inPhase) * sample_x + inPhase * sample_x1;
}

//==============================================================================
bool ChorusPedalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ChorusPedalAudioProcessor::createEditor()
{
    return new ChorusPedalAudioProcessorEditor (*this);
}

//==============================================================================
void ChorusPedalAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ChorusPedalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChorusPedalAudioProcessor();
}
