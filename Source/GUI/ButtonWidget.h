/*
  ==============================================================================

    ButtonWidget.h
    Created: 8 Jun 2024 10:50:40am
    Author:  Alex Mixon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../SharedImages.h"
//==============================================================================
/*
*/
class HitPads : public juce::ImageButton
{
public:
    HitPads(SharedImages* i) : buttonEnabled(i->getPadButtonOn()), buttonDisabled(i->getPadButtonOff())
    {
        setImages(true, false, true,
                  buttonDisabled, 1.f, juce::Colours::transparentWhite,
                  buttonDisabled, 0.5f, juce::Colours::transparentWhite,
                  buttonEnabled, 1.f, juce::Colours::transparentWhite);
        
    }
    
    
private:
    juce::Image& buttonEnabled, buttonDisabled;
    
};
