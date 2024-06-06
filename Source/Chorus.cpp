#include <JuceHeader.h>
#include "Chorus.h"
Chorus::Chorus() {}
Chorus::~Chorus() {}


//void Chorus::processChannel(float* channelData, int numSamples, float fs, float depth, float rate, int delaySamples, float feedback)
//{
//    // Create modulation signal
//    juce::AudioBuffer<float> modulation(1, numSamples);
//    for (int sample = 0; sample < numSamples; ++sample)
//    {
//        const float t = static_cast<float>(sample) / fs;
//        modulation.setSample(0, sample, depth * std::sin(2.0f * juce::MathConstants<float>::pi * rate * t));
//    }
//
//    // Apply chorus effect
//    for (int sample = 0; sample < numSamples; ++sample)
//    {
//        // Calculate delayed index
//        const int delayIndex = static_cast<int>(sample - delaySamples * (1 + modulation.getSample(0, sample)));
//
//        // Apply feedback
//        if (delayIndex >= 0 && delayIndex < numSamples)
//        {
//            channelData[sample] += feedback * channelData[delayIndex];
//        }
//    }
//}
void Chorus::process(const juce::AudioBuffer<float>& x, juce::AudioBuffer<float>& y,
                     float fs, float depth, float rate, float delayTime, float feedback,
                     float intensity, float mix)
    {
        const int numChannels = x.getNumChannels();
        const int numSamples = x.getNumSamples();

        // Convert delay time to samples
        const int delaySamples = round(delayTime * fs);

        // Apply chorus effect independently to each channel
        for (int channel = 0; channel < numChannels; ++channel)
        {
            const float* xChannelData = x.getReadPointer(channel);
            float* yChannelData = y.getWritePointer(channel);

            // Create modulation signal for each channel
            juce::AudioBuffer<float> modulation(1, numSamples);
            for (int sample = 0; sample < numSamples; ++sample)
            {
                const float t = static_cast<float>(sample) / fs;
                modulation.setSample(0, sample, depth * std::sin(2.0f * M_PI * rate * t));
            }

            // Apply chorus effect
            for (int sample = 0; sample < numSamples; ++sample)
            {
                // Calculate delayed index
                const int delayIndex = round(sample - delaySamples * (1 + modulation.getSample(0, sample)));

                // Apply feedback
                if (delayIndex >= 0 && delayIndex < numSamples)
                {
                    // Apply chorus effect with intensity and mix
                    float processedSample = xChannelData[sample] + feedback * xChannelData[delayIndex];
                    processedSample = mix * processedSample + (1.0f - mix) * xChannelData[sample];
                    yChannelData[sample] = intensity * processedSample + (1.0f - intensity) * xChannelData[sample];
                }
                else
                {
                    yChannelData[sample] = xChannelData[sample];
                }
            }
        }
    }
