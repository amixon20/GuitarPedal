/*
  ==============================================================================

    MainComponent.cpp
    Created: 7 Jun 2024 1:30:06pm
    Author:  Alex Mixon

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"
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
{

    
    addAndMakeVisible(depthSlider);
    addAndMakeVisible(rateSlider);
    addAndMakeVisible(delayTimeSlider);
    addAndMakeVisible(feedbackSlider);
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(bypassButton);
    
    bypassButton.addMouseListener(this, true);
    
    depthLabel.setColour(juce::Label::textColourId, juce::Colours::lightblue);
    depthLabel.setText("Depth", juce::dontSendNotification );
    depthLabel.attachToComponent(&depthSlider, false);
    addAndMakeVisible(depthLabel);
    
    rateLabel.setColour(juce::Label::textColourId, juce::Colours::lightblue);
    rateLabel.setText("Rate", juce::dontSendNotification );
    rateLabel.attachToComponent(&rateSlider, false);
    addAndMakeVisible(rateLabel);
    
    delayTimeLabel.setColour(juce::Label::textColourId, juce::Colours::lightblue);
    delayTimeLabel.setText("Delay Time", juce::dontSendNotification );
    delayTimeLabel.attachToComponent(&delayTimeSlider, false);
    addAndMakeVisible(delayTimeLabel);
    
    feedbackLabel.setColour(juce::Label::textColourId, juce::Colours::lightblue);
    feedbackLabel.setText("Feedback", juce::dontSendNotification );
    feedbackLabel.attachToComponent(&feedbackSlider, false);
    addAndMakeVisible(feedbackLabel);
    
    mixLabel.setColour(juce::Label::textColourId, juce::Colours::lightblue);
    mixLabel.setText("Mix", juce::dontSendNotification );
    mixLabel.attachToComponent(&mixSlider, false);
    addAndMakeVisible(mixLabel);

    bypassLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    bypassLabel.setText("Bypass", juce::dontSendNotification );
    bypassLabel.attachToComponent(&bypassButton, false);
    addAndMakeVisible(bypassLabel);

    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB1", depthSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB2", rateSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB3", intensitySlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB4", delayTimeSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB5", feedbackSlider));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, "KNOB6", mixSlider));

    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts, "BUTTON1", bypassButton));
    
    bypassButton.addMouseListener(this, false);

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
    
    g.setColour (juce::Colours::whitesmoke);
    g.setFont (30.0f);
    g.drawFittedText ("Chorus", getLocalBounds().removeFromTop(35), juce::Justification::centred, 1);
}

void MainComponent::resized()
{
    depthSlider.setBounds(75, 140, 75, 75);
    rateSlider.setBounds(200, 180, 75, 75);
    delayTimeSlider.setBounds(325, 180, 75, 75);
    feedbackSlider.setBounds(260, 75, 75, 75);
    mixSlider.setBounds(450, 140, 75, 75);
    bypassButton.setBounds(50, 20, 50, 50);
}
