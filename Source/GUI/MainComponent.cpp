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
    m_pSharedImages (audioProcessor.getSharedImagesPtr()),
    depthSlider (m_pSharedImages),
    rateSlider (m_pSharedImages),
    intensitySlider (m_pSharedImages),
    delayTimeSlider (m_pSharedImages),
    feedbackSlider (m_pSharedImages),
    mixSlider (m_pSharedImages),
    bypassButton (m_pSharedImages)

//    depthSlider("Depth", "KNOB1", audioProcessor.apvts),
//    rateSlider("Rate", "KNOB2", audioProcessor.apvts),
//    intensitySlider("Intensity", "KNOB3", audioProcessor.apvts),
//    delayTimeSlider("Delay Time", "KNOB4", audioProcessor.apvts),
//    feedbackSlider("Feedback", "KNOB5", audioProcessor.apvts),
//    mixSlider("Mix", "KNOB6", audioProcessor.apvts)
{

    
    addAndMakeVisible(depthSlider);
    addAndMakeVisible(rateSlider);
    addAndMakeVisible(intensitySlider);
    addAndMakeVisible(delayTimeSlider);
    addAndMakeVisible(feedbackSlider);
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(bypassButton);

    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB1", depthSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB2", rateSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB3", intensitySlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB4", delayTimeSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB5", feedbackSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB6", mixSlider));

    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts, "BUTTON1", bypassButton));
    
    bypassButton.addMouseListener(this, false);

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
    int width  = getWidth();
    int height = getHeight();
        
    g.drawImage(m_pSharedImages->getBackgroundImage(), 0, 0, width, height, 0, 0, 2000, 1400);
    
    g.setColour (juce::Colours::black);
    g.setFont (30.0f);
    g.drawFittedText ("Mixon Chorus", getLocalBounds().removeFromTop(35), juce::Justification::centred, 1);
}

void MainComponent::resized()
{
    depthSlider.setBounds(75, 140, 75, 75);
    rateSlider.setBounds(210, 80, 75, 75);
    intensitySlider.setBounds(210, 200, 75, 75);
    delayTimeSlider.setBounds(315, 80, 75, 75);
    feedbackSlider.setBounds(315, 200, 75, 75);
    mixSlider.setBounds(450, 140, 75, 75);
    bypassButton.setBounds(275, 165, 50, 20);
}
