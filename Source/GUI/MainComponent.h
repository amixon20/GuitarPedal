/*
  ==============================================================================

    MainComponent.h
    Created: 7 Jun 2024 1:30:06pm
    Author:  Alex Mixon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "CustomSlider.h"
//==============================================================================
/*
*/
class MainComponent : public juce::Component
{
public:
    MainComponent(ChorusPedalAudioProcessor& processor);
    ~MainComponent();

    void resized() override;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    
    void paint (juce::Graphics& g) override;

private:
    ChorusPedalAudioProcessor& audioProcessor;
    CustomSlider depthSlider, rateSlider, intensitySlider,
            delayTimeSlider, feedbackSlider, mixSlider;
    juce::ToggleButton bypassButton;
    std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent);
};

