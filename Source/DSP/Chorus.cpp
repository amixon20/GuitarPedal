#include <JuceHeader.h>
#include "Chorus.h"
#include <algorithm>

Chorus::Chorus(int maxDelay, double sampleRate)
: delayLine(maxDelay, sampleRate), lfo(sampleRate, 0, 0)
{
    
}

Chorus::~Chorus() {}



void Chorus::process(juce::AudioBuffer<float>& buffer,
                     float depth, float rate, float delayTime, float feedback,
                     float intensity, float mix)
{
   
}
