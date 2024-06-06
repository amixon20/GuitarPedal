/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <memory>


//==============================================================================
/**
*/
class ChorusPedalAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ChorusPedalAudioProcessorEditor (ChorusPedalAudioProcessor& p);
    ~ChorusPedalAudioProcessorEditor() override;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChorusPedalAudioProcessor& audioProcessor;
    
    juce::Slider depthSlider;
    juce::Slider rateSlider;
    juce::Slider delayTimeSlider;
    juce::Slider feedbackSlider;
    juce::Slider intensitySlider;
    juce::Slider mixSlider;
    
    juce::ToggleButton bypassButton;
    
    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusPedalAudioProcessorEditor)
};
