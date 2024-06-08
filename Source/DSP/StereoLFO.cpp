/*
  ==============================================================================

    StereoLFO.cpp
    Created: 8 Jun 2024 12:44:56pm
    Author:  Alex Mixon

  ==============================================================================
*/

#include "StereoLFO.h"
#include <cmath>

StereoLFO::StereoLFO(double sampleRate, double frequency, double depth)
    : sampleRate(sampleRate), frequency(frequency), depth(depth), phaseLeft(0.0), phaseRight(0.0)
{
    
}

void StereoLFO::setFrequency(double frequency)
{
    this->frequency = frequency;
}

void StereoLFO::setDepth(double depth)
{
    this->depth = depth;
}

void StereoLFO::reset()
{
    phaseLeft = 0.0;
    phaseRight = 0.0;
}

float StereoLFO::getNextSampleLeft()
{
    double deltaPhase = 2.0 * M_PI * frequency / sampleRate;
    float value = depth * std::sin(phaseLeft);
    phaseLeft += deltaPhase;
    if (phaseLeft >= 2.0 * M_PI)
        phaseLeft -= 2.0 * M_PI;
    return value;
}

float StereoLFO::getNextSampleRight()
{
    double deltaPhase = 2.0 * M_PI * frequency / sampleRate;
    float value = depth * std::sin(phaseRight);
    phaseRight += deltaPhase;
    if (phaseRight >= 2.0 * M_PI)
        phaseRight -= 2.0 * M_PI;
    return value;
}
