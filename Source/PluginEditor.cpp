/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Chorus.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), chorus(48000)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 500);
    
    depthSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlider.setRange (0.0, 1.0);
    depthSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 0);
    depthSlider.setPopupDisplayEnabled (true, false, this);
    depthSlider.setTextValueSuffix (" Depth");
    depthSlider.setValue(0.5);
    
    addAndMakeVisible(depthSlider);
    
    depthSlider.addListener(this);
    
    rateSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider.setRange (0.0, 5.0);
    rateSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 0);
    rateSlider.setPopupDisplayEnabled (true, false, this);
    rateSlider.setTextValueSuffix (" Rate");
    rateSlider.setValue(1.0);
    
    addAndMakeVisible(rateSlider);
    
    rateSlider.addListener(this);
    
    delayTimeSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTimeSlider.setRange (0.0, 5.0);
    delayTimeSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 0);
    delayTimeSlider.setPopupDisplayEnabled (true, false, this);
    delayTimeSlider.setTextValueSuffix (" Delay Time");
    delayTimeSlider.setValue(1.0);
    
    addAndMakeVisible(delayTimeSlider);
    
    delayTimeSlider.addListener(this);
    
    feedbackSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setRange (0.0, 1.0);
    feedbackSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 0);
    feedbackSlider.setPopupDisplayEnabled (true, false, this);
    feedbackSlider.setTextValueSuffix (" Feedback");
    feedbackSlider.setValue(0.0);
    
    addAndMakeVisible(feedbackSlider);
    
    feedbackSlider.addListener(this);
    
    
    
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
//     (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::black);
    g.setFont (25.0f);
    g.drawFittedText ("Chorus", getLocalBounds(), juce::Justification::centred, 1);
    
    g.setFont(15.0f);
    g.drawText ("Depth", 150, 200, 100, getHeight() - 60, juce::Justification::left, false);
    g.drawText ("Rate", 400, 200, 100, getHeight() - 60, juce::Justification::left, false);
    g.drawText ("Delay Time", 600, 200, 100, getHeight() - 60, juce::Justification::left, false);
    g.drawText ("Feedback", 850, 200, 100, getHeight() - 60, juce::Justification::left, false);
}

void NewProjectAudioProcessorEditor::resized()
{
    depthSlider.setBounds (150, 100, 100, getHeight() - 60);
    
    rateSlider.setBounds (400, 100, 100, getHeight() - 60);
    
    delayTimeSlider.setBounds (600, 100, 100, getHeight() - 60);
    
    feedbackSlider.setBounds (850, 100, 100, getHeight() - 60);
}
void NewProjectAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if(slider == &depthSlider) {
        chorus.setModulationDepth(depthSlider.getValue());
    }
    if(slider == &rateSlider) {
        chorus.setModulationRate(rateSlider.getValue());
    }
//    if(slider == &delayTimeSlider) {
//        audioProcessor.chorusDelayTime = delayTimeSlider.getValue();
//    }
    if(slider == &feedbackSlider) {
        chorus.setFeedback(feedbackSlider.getValue());
    }
}



