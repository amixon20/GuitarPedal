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
    : AudioProcessorEditor (&p), audioProcessor (p), mainComponent(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);

    addAndMakeVisible(mainComponent);
    
//    depthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
//    depthSlider.setBounds(10, 50, 75, 75);
//    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
//    addAndMakeVisible(depthSlider);
    
//    depthLabel.setText("Depth", juce::dontSendNotification);
//    depthLabel.attachToComponent(&depthSlider, false);
//    addAndMakeVisible(depthLabel);
    
//    rateSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
//    rateSlider.setBounds(10, 150, 75, 75);
//    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
//    addAndMakeVisible(rateSlider);
    
//    rateLabel.setText("Rate", juce::dontSendNotification);
//    rateLabel.attachToComponent(&rateSlider, false);
//    addAndMakeVisible(rateLabel);
    
//    intensitySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
//    intensitySlider.setBounds(175, 150, 75, 75);
//    intensitySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
//    addAndMakeVisible(intensitySlider);
    
//    intensityLabel.setText("Intensity", juce::dontSendNotification);
//    intensityLabel.attachToComponent(&intensitySlider, false);
//    addAndMakeVisible(intensityLabel);
    
//    delayTimeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
//    delayTimeSlider.setBounds(350, 150, 75, 75);
//    delayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
//    addAndMakeVisible(delayTimeSlider);
    
//    delayTimeLabel.setText("Delay Time", juce::dontSendNotification);
//    delayTimeLabel.attachToComponent(&delayTimeSlider, false);
//    addAndMakeVisible(delayTimeLabel);
    
//    feedbackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
//    feedbackSlider.setBounds(510, 50, 75, 75);
//    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
//    addAndMakeVisible(feedbackSlider);
    
//    feedbackLabel.setText("Feedback", juce::dontSendNotification);
//    feedbackLabel.attachToComponent(&feedbackSlider, false);
//    addAndMakeVisible(feedbackLabel);
    
//    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
//    mixSlider.setBounds(510, 150, 75, 75);
//    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
//    addAndMakeVisible(mixSlider);
    
//    mixLabel.setText("Mix", juce::dontSendNotification);
//    mixLabel.attachToComponent(&mixSlider, false);
//    addAndMakeVisible(mixLabel);
    
//    bypassButton.setBounds(290, 100, 50, 20);
//    addAndMakeVisible(bypassButton);
    
//    bypassLabel.setText("Bypass", juce::dontSendNotification);
//    mixLabel.attachToComponent(&bypassButton, false);
//    addAndMakeVisible(bypassLabel);
    
//    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB1", depthSlider));
//    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB2", rateSlider));
//    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB3", intensitySlider));
//    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB4", delayTimeSlider));
//    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB5", feedbackSlider));
//    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB6", mixSlider));
//    
//    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts, "BUTTON1", bypassButton));
}

ChorusPedalAudioProcessorEditor::~ChorusPedalAudioProcessorEditor()
{
}

//==============================================================================
void ChorusPedalAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (juce::Colours::black);
//
//    g.setColour (juce::Colours::lightblue);
//    g.setFont (40.0f);
//    g.drawFittedText ("Mixon Chorus", getLocalBounds().removeFromTop(75), juce::Justification::centred, 1);
}

void ChorusPedalAudioProcessorEditor::resized()
{
    mainComponent.setBounds(0, 0, getWidth(), getHeight());
}
