/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/MainComponent.h"
#include <memory>


//==============================================================================
/**
*/
class ChorusPedalAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ChorusPedalAudioProcessorEditor (ChorusPedalAudioProcessor& p);
    ~ChorusPedalAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChorusPedalAudioProcessor& audioProcessor;
    
    MainComponent mainComponent;
    
    juce::Label depthLabel, rateLabel, intensityLabel, delayTimeLabel, feedbackLabel, mixLabel, bypassLabel;
    
    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    
    std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusPedalAudioProcessorEditor)
};
