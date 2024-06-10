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
#include "../SharedImages.h"
#include "SliderWidgets.h"
#include "ButtonWidget.h"
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
    
    SharedImages*               m_pSharedImages;
    
    BigKnob depthSlider, rateSlider, intensitySlider,
            delayTimeSlider, feedbackSlider, mixSlider;
    
    Button bypassButton;
    
    juce::Label depthLabel, rateLabel, delayTimeLabel, feedbackLabel, mixLabel, bypassLabel;
    
    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    
    std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent);
};

