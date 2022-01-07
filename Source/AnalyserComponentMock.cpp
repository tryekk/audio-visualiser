/*
  ==============================================================================

    AnalyserComponentMock.cpp
    Created: 7 Jan 2022 7:16:11pm
    Author:  Tom Carter

  ==============================================================================
*/

#include <iostream>
#include <chrono>

#include "AnalyserComponentMock.h"


AnalyserComponent::AnalyserComponent()
{
}

AnalyserComponent::~AnalyserComponent()
{
}

void AnalyserComponent::paint()
{
    counter = counter + 1;
//    colourIncrement = colourIncrement + 1;
//
//    n = n * 2;
//    if (n >= interpolationFrames) {
//        n = 1;
//    }
    
    drawNextFrameOfSpectrum();
}


// This function was taken from an example project on https://docs.juce.com/master/tutorial_spectrum_analyser.html
void AnalyserComponent::drawNextFrameOfSpectrum()
{
    if (counter >= interpolationFrames) {
        // Reset
        counter = 0;
    }
}
