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
apvts(*this, nullptr, "params", createParams()), chorus()
{
}

ChorusPedalAudioProcessor::~ChorusPedalAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout ChorusPedalAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB1", 1}, "Depth", 0.f, 1.f, 0.5));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB2", 2}, "Rate", 0.f, 20.f, 1.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB3", 3}, "Intensity", 0.f, 1.f, 0.5));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB4", 4}, "Delay Time", 0.f, 0.03, 0.1));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB5", 5}, "Feedback", 0.f, 1.f, 0.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNOB6", 6}, "Mix", 0.f, 1.f, 0.f));
    
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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
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
    const int numSamples = buffer.getNumSamples();
    const float sampleRate = getSampleRate();
    
    float depth = *apvts.getRawParameterValue("KNOB1");
    float rate = *apvts.getRawParameterValue("KNOB2");
    float intensity = *apvts.getRawParameterValue("KNOB3");
    float delayTime = *apvts.getRawParameterValue("KNOB4");
    float feedback = *apvts.getRawParameterValue("KNOB5");
    float mix = *apvts.getRawParameterValue("KNOB6");
    
    bool bypass = *apvts.getRawParameterValue("BUTTON1") > 0.5f ? true : false;
    

    // Apply chorus effect
    if(!bypass) {
        juce::AudioBuffer<float> processedBuffer(buffer.getNumChannels(), numSamples);
            chorus.process(buffer, processedBuffer, sampleRate, depth, rate, delayTime, feedback, intensity, mix);

            // Copy the processed audio back to the original buffer
            buffer = processedBuffer;
        }
    else {
        buffer = buffer;
    }
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
