#pragma once
#include <JuceHeader.h>
#include "DelayLine.h"
#include "StereoLFO.h"
class Chorus
{
public:
    Chorus(int maxDelay, double sampleRate);
    
    ~Chorus();
    
    void process(juce::AudioBuffer<float>& buffer,
                         float depth, float rate, float delayTime, float feedback,
                         float intensity, float mix);


private:
    
    DelayLine delayLine;
    
    StereoLFO lfo;
};


