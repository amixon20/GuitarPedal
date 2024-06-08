/*
  ==============================================================================

    SharedImages.cpp
    Created: 8 Jun 2024 10:52:23am
    Author:  Alex Mixon

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SharedImages.h"
//==============================================================================


void SharedImages::loadImages() 
{
    m_BackgroundImage = juce::ImageCache::getFromMemory(BinaryData::bg_1_png, BinaryData::bg_2_pngSize);
        
    m_BigKnob         = juce::ImageCache::getFromMemory(BinaryData::Knob_big_png, BinaryData::Knob_big_pngSize);
    
    m_PadButtonOn     = juce::ImageCache::getFromMemory(BinaryData::Button_en_3_png, BinaryData::Button_en_1_pngSize);
        
    m_PadButtonOff    = juce::ImageCache::getFromMemory(BinaryData::Button_dis_3_png, BinaryData::Button_dis_1_pngSize);
}
