/*
  ==============================================================================

    SharedImages.h
    Created: 8 Jun 2024 10:52:23am
    Author:  Alex Mixon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SharedImages  : public juce::Component
{
public:
    SharedImages() {loadImages();};
    
    void loadImages();
        
    juce::Image& getBackgroundImage() { return m_BackgroundImage; };
        
    juce::Image& getBigKnobImage()    { return m_BigKnob; };
        
    juce::Image& getPadButtonOn()     { return m_PadButtonOn; };

    juce::Image& getPadButtonOff()    { return m_PadButtonOff; };
private:
    
    juce::Image m_BackgroundImage;
        
    juce::Image m_BigKnob;
        
    juce::Image m_PadButtonOn;
        
    juce::Image m_PadButtonOff;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SharedImages)
};
