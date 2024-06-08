/*
  ==============================================================================

    StereoLFO.h
    Created: 8 Jun 2024 12:44:56pm
    Author:  Alex Mixon

  ==============================================================================
*/

#pragma once

class StereoLFO
{
public:
    StereoLFO(double sampleRate, double frequency, double depth);
    void setFrequency(double frequency);
    void setDepth(double depth);
    void reset();
    float getNextSampleLeft();
    float getNextSampleRight();

private:
    double sampleRate;
    double frequency;
    double depth;
    double phaseLeft;
    double phaseRight;
};
