/*
  ==============================================================================

    MainComponent.cpp
    Created: 7 Jun 2024 1:30:06pm
    Author:  Alex Mixon

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"
#include "CustomSlider.h"
#include "CustomLookAndFeel.h"
//==============================================================================
MainComponent::MainComponent(ChorusPedalAudioProcessor& processor)
    : audioProcessor(processor),
    depthSlider("Depth", "KNOB1", audioProcessor.apvts),
    rateSlider("Rate", "KNOB2", audioProcessor.apvts),
    intensitySlider("Intensity", "KNOB3", audioProcessor.apvts),
    delayTimeSlider("Delay Time", "KNOB4", audioProcessor.apvts),
    feedbackSlider("Feedback", "KNOB5", audioProcessor.apvts),
    mixSlider("Mix", "KNOB6", audioProcessor.apvts)
{
    depthSlider.setBounds(10, 50, 75, 75);
    rateSlider.setBounds(10, 150, 75, 75);
    intensitySlider.setBounds(175, 150, 75, 75);
    delayTimeSlider.setBounds(350, 150, 75, 75);
    feedbackSlider.setBounds(510, 50, 75, 75);
    mixSlider.setBounds(510, 150, 75, 75);
    bypassButton.setBounds(290, 100, 50, 20);
    
    addAndMakeVisible(depthSlider);
    addAndMakeVisible(rateSlider);
    addAndMakeVisible(intensitySlider);
    addAndMakeVisible(delayTimeSlider);
    addAndMakeVisible(feedbackSlider);
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(bypassButton);

    // Set up sliders with labels and attach to AudioProcessorValueTreeState
//    depthSlider.reset(new CustomSlider("Depth", "KNOB1", audioProcessor.apvts));
//    rateSlider.reset(new CustomSlider("Rate", "KNOB2", audioProcessor.apvts));
//    intensitySlider.reset(new CustomSlider("Intensity", "KNOB3", audioProcessor.apvts));
//    delayTimeSlider.reset(new CustomSlider("Delay Time", "KNOB4", audioProcessor.apvts));
//    feedbackSlider.reset(new CustomSlider("Feedback", "KNOB5", audioProcessor.apvts));
//    mixSlider.reset(new CustomSlider("Mix", "KNOB6", audioProcessor.apvts));

    bypassButton.setBounds(290, 100, 50, 20);
    addAndMakeVisible(bypassButton);
    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts, "BUTTON1", bypassButton));
}

MainComponent::~MainComponent() {}

void MainComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

        g.fillAll (juce::Colours::black);
    
        g.setColour (juce::Colours::gold);
        g.setFont (40.0f);
        g.drawFittedText ("Mixon Chorus", getLocalBounds().removeFromTop(75), juce::Justification::centred, 1);
}

void MainComponent::resized()
{
    
}
