/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Chorus.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor() : fs(48000), m_chorus(fs)
{
    
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    fs = sampleRate;
    m_chorus = Chorus(static_cast<int>(sampleRate));
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getNumInputChannels();
    auto totalNumOutputChannels = getNumOutputChannels();
    auto numSamples = buffer.getNumSamples();
    float* const leftChannel = buffer.getWritePointer(0);
    float* const rightChannel = buffer.getWritePointer(1);
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
           buffer.clear (i, 0, buffer.getNumSamples());
    
    // Normalize input
        float inputPeakAmplitude = 0.0f;
        for (int i = 0; i < numSamples; ++i) {
            inputPeakAmplitude = std::max(inputPeakAmplitude, std::abs(leftChannel[i]));
            inputPeakAmplitude = std::max(inputPeakAmplitude, std::abs(rightChannel[i]));
        }

        if (inputPeakAmplitude > 0.0f) {
            const float desiredInputPeak = 1.0f; // Desired peak amplitude for input normalization
            const float inputNormalizationFactor = desiredInputPeak / inputPeakAmplitude;

            for (int i = 0; i < numSamples; ++i) {
                leftChannel[i] *= inputNormalizationFactor;
                rightChannel[i] *= inputNormalizationFactor;
            }
        }

        // Process audio through chorus effect
        m_chorus.process(leftChannel, leftChannel, numSamples);
        m_chorus.process(rightChannel, rightChannel, numSamples);
    
    float peakAmplitude = 0.0f;
       for (int i = 0; i < numSamples; ++i) {
           peakAmplitude = std::max(peakAmplitude, std::abs(leftChannel[i]));
           peakAmplitude = std::max(peakAmplitude, std::abs(rightChannel[i]));
       }

    if (peakAmplitude > 0.0f) {
        const float desiredPeak = 1.0f; // Desired peak amplitude (e.g., 0 dBFS)
        const float normalizationFactor = desiredPeak / peakAmplitude;
        
        for (int i = 0; i < numSamples; ++i) {
            leftChannel[i] *= normalizationFactor;
            rightChannel[i] *= normalizationFactor;
        }
    }
               
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
//    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
//        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//
//        // ..do something to the data...
//    }
}

//==============================================================================
    bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}