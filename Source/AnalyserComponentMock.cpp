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
    
    for (int i = 0; i < scopeSize; i++)
    {
        // Update colour
        oldColourList[i][0] = currentAccurateColourList[i][0];
        oldColourList[i][1] = currentAccurateColourList[i][1];
        oldColourList[i][2] = currentAccurateColourList[i][2];
        
        // Simulates the update colour procedure in the real application
        float red = oldColourList[i][0] + (((currentAccurateColourList[i][0] - oldColourList[i][0]) / interpolationFramesColour) * colourIncrement);
        float green = oldColourList[i][1] + (((currentAccurateColourList[i][1] -  oldColourList[i][1]) / interpolationFramesColour) * colourIncrement);
        float blue = oldColourList[i][2] + (((currentAccurateColourList[i][2] - oldColourList[i][2]) / interpolationFramesColour) * colourIncrement);
    
        updatedColour[0] = red;
        updatedColour[1] = green;
        updatedColour[2] = blue;
    }
 
    if (colourIncrement >= interpolationFramesColour) {
        // Then reset
        colourIncrement = 0;
    }

}
