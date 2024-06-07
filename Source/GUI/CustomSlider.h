/*
  ==============================================================================

    CustomSlider.h
    Created: 7 Jun 2024 1:33:03pm
    Author:  Alex Mixon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomSlider : public juce::Component
{
public:
    CustomSlider(const juce::String& labelText, const juce::String& parameterID, juce::AudioProcessorValueTreeState& apvts);
    ~CustomSlider();

    void resized() override;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

private:
    juce::Slider slider;
    juce::Label label;
    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    juce::String parameter;
    juce::LookAndFeel_V4 customLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSlider)
};

