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
class Button : public juce::ImageButton
{
public:
    Button(SharedImages* i) : buttonEnabled(i->getPadButtonOn()), buttonDisabled(i->getPadButtonOff())
    {
        updateButtonImages();
        
    }
    
    void updateButtonImages()
     {
         // Check the condition (e.g., button pressed)
         if (isButtonPressed) // Replace isButtonPressed with your condition
         {
             setImages(true, false, true,
                       buttonEnabled, 1.f, juce::Colours::transparentWhite, // Image when button is enabled
                       buttonEnabled, 0.5f, juce::Colours::transparentWhite, // Image when button is pressed
                       buttonEnabled, 1.f, juce::Colours::transparentWhite); // Image when button is disabled
         }
         else
         {
             setImages(true, false, true,
                       buttonDisabled, 1.f, juce::Colours::transparentWhite, // Image when button is enabled
                       buttonDisabled, 0.5f, juce::Colours::transparentWhite, // Image when button is pressed
                       buttonDisabled, 1.f, juce::Colours::transparentWhite); // Image when button is disabled
         }
     }
    
    void buttonClicked(juce::Button* button)
      {
          // Update the button state and images when clicked
          isButtonPressed = !isButtonPressed;
          updateButtonImages();
      }
    
private:
    
    bool isButtonPressed;
    juce::Image& buttonEnabled, buttonDisabled;
    
};
