/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 7 Jun 2024 2:36:59pm
    Author:  Alex Mixon

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

//==============================================================================
CustomLookAndFeel::CustomLookAndFeel()
{
    goldColour = juce::Colour(255, 215, 0);

}

CustomLookAndFeel::~CustomLookAndFeel(){}

//void CustomLookAndFeel::paint (juce::Graphics& g)
//{
//    /* This demo code just fills the component's background and
//       draws some placeholder text to get you started.
//
//       You should replace everything in this method with your own
//       drawing code..
//    */
//
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
//
//    g.setColour (juce::Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//
//    g.setColour (juce::Colours::white);
//    g.setFont (14.0f);
//    g.drawText ("CustomLookAndFeel", getLocalBounds(),
//                juce::Justification::centred, true);   // draw some placeholder text
//}
void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                                         float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    // Call base class to draw the slider
    juce::LookAndFeel_V4::drawRotarySlider(g, x, y, width, height, sliderPos, rotaryStartAngle, rotaryEndAngle, slider);

    // Draw a gold ring around the slider
    g.setColour(goldColour);
    g.setOpacity(0.5f); // Adjust opacity as needed
    g.drawEllipse(x, y, width, height, 2.0f);
}

//void CustomLookAndFeel::resized()
//{
//    // This method is where you should set the bounds of any child
//    // components that your component contains..
//
//}
