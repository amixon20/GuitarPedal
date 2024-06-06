#pragma once
#include <JuceHeader.h>
class Chorus
{
public:
    Chorus();
    ~Chorus();

    void process(const juce::AudioBuffer<float>& x, juce::AudioBuffer<float>& y,
                         float fs, float depth, float rate, float delayTime, float feedback,
                         float intensity, float mix);

    void reset();

    void setSampleRate(double sampleRate);

private:
//    void processChannel(float* channelData, int numSamples, float fs, float depth, float rate, int delaySamples, float feedback);
};

