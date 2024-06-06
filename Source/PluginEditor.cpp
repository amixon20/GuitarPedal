/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <JuceHeader.h>
//==============================================================================
ChorusPedalAudioProcessorEditor::ChorusPedalAudioProcessorEditor (ChorusPedalAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);
    
    depthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    depthSlider.setBounds(10, 50, 75, 75);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible(depthSlider);
    
    rateSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rateSlider.setBounds(10, 150, 75, 75);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible(rateSlider);
    
    intensitySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    intensitySlider.setBounds(175, 150, 75, 75);
    intensitySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible(intensitySlider);
    
    delayTimeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    delayTimeSlider.setBounds(350, 150, 75, 75);
    delayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible(delayTimeSlider);
    
    feedbackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    feedbackSlider.setBounds(510, 50, 75, 75);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible(feedbackSlider);
    
    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setBounds(510, 150, 75, 75);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible(mixSlider);
    
    bypassButton.setBounds(290, 100, 50, 20);
    addAndMakeVisible(bypassButton);
    
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB1", depthSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB2", rateSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB3", intensitySlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB4", delayTimeSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB5", feedbackSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB6", mixSlider));
    
    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts, "BUTTON1", bypassButton));
}

ChorusPedalAudioProcessorEditor::~ChorusPedalAudioProcessorEditor()
{
}

//==============================================================================
void ChorusPedalAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (40.0f);
    g.drawFittedText ("Mixon Chorus", getLocalBounds().removeFromTop(75), juce::Justification::centred, 1);
}

void ChorusPedalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
