/*
  ==============================================================================

    CustomSlider.cpp
    Created: 7 Jun 2024 1:33:03pm
    Author:  Alex Mixon

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomSlider.h"
#include "CustomLookAndFeel.h"
//==============================================================================
CustomSlider::CustomSlider(const juce::String& labelText, const juce::String& parameterID, juce::AudioProcessorValueTreeState& apvts)
    : label(labelText, labelText), parameter(parameterID)
{
    
    slider.setLookAndFeel(&customLookAndFeel);
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(slider);
    addAndMakeVisible(label);

    // Attach the slider to the AudioProcessorValueTreeState
    sliderAttachments.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(apvts, parameterID, slider));
}

CustomSlider::~CustomSlider() {}

void CustomSlider::resized()
{
    slider.setBounds(0, 0, getWidth(), getHeight() - 20);
}
