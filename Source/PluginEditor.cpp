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
    
}

ChorusPedalAudioProcessorEditor::~ChorusPedalAudioProcessorEditor()
{
    
}

//==============================================================================
void ChorusPedalAudioProcessorEditor::paint (juce::Graphics& g)
{
    
}

void ChorusPedalAudioProcessorEditor::resized()
{
    mainComponent.setBounds(0, 0, getWidth(), getHeight());
}
