#pragma once
#include <JuceHeader.h>
class Chorus
{
public:
    Chorus();
    ~Chorus();

//    float lfoValue;
//    float lfoFreq = 0.f;
//    float lfoDepth;
//    float lfoPhase[2];
//    float lfoPhaseIncrement[2];
//    int maxDelayInSeconds = .05;
//    int maxNumVoices = 2;
    
    void process(juce::AudioBuffer<float>& buffer,
                         float fs, float depth, float rate, float delayTime, float feedback,
                         float intensity, float mix);


private:
    
    
    int maxSample;
    
    static constexpr int maxVoices = 2;
    static constexpr float maxDelayInSeconds = 0.05;
    
    int maxDelayInSamples;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineL;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineR;
    int readIndex[2][maxVoices];
    int writeIndex[3][maxVoices];

    float lfoValue;
    float lfoFreq;
    float lfoDepth;
    float feedbackGain;
    
    float lfoPhase[2];
    float lfoPhaseIncrement[2];
    
    float calculateLFOValue(int channel, float rate);
    int calculateDelayTime(int voiceIndex, float lfoValue, int channel, float delayTime);
    
};


