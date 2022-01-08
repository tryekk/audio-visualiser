/*
  ==============================================================================

    AnalyserComponentMock.cpp
    Created: 7 Jan 2022 7:16:11pm
    Author:  Tom Carter
    Part of Audio Visualiser Tests project

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
    drawFrame();  // drawFrame comes first
    
    drawNextFrameOfSpectrum();  // this is run in TimerCallback in real JUCE project

    counter = counter + 1;
    colourIncrement = colourIncrement + 1;
//
//    n = n * 2;
//    if (n >= interpolationFrames) {
//        n = 1;
//    }
}

void AnalyserComponent::drawNextFrameOfSpectrum()
{
    if (counter >= interpolationFrames) {
        // Reset
        counter = 0;
    }
}

void AnalyserComponent::drawFrame()
{
 
    if (colourIncrement >= interpolationFramesColour) {
        // Updatesc olour here
        // Then reset
        colourIncrement = 0;
    }

}
