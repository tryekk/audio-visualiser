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
    //    float LowGainColourR = 1.0f;
    //    float LowGainColourG = 1.0f;
    //    float LowGainColourB = 1.0f;
    //
    //    float HighGainColourR = gainColour[0];
    //    float HighGainColourG = gainColour[1];
    //    float HighGainColourB = gainColour[2];
    //
    //    float LowPitchColourR = lowPitchColour[0];
    //    float LowPitchColourG = lowPitchColour[1];
    //    float LowPitchColourB = lowPitchColour[2];
    //
    //    float HighPitchColourR = highPitchColour[0];
    //    float HighPitchColourG = highPitchColour[1];
    //    float HighPitchColourB = highPitchColour[2];
    
    for (int i = 0; i < scopeSize; i++)
    {
        
        // Simulates the update colour procedure in the real application
        float red = oldColourList[i][0] + (((currentAccurateColourList[i][0] - oldColourList[i][0]) / interpolationFramesColour) * colourIncrement);
        float green = oldColourList[i][1] + (((currentAccurateColourList[i][1] -  oldColourList[i][1]) / interpolationFramesColour) * colourIncrement);
        float blue = oldColourList[i][2] + (((currentAccurateColourList[i][2] - oldColourList[i][2]) / interpolationFramesColour) * colourIncrement);
    
        updatedColour[0] = red;  // Will always be the last point in this test case
        updatedColour[1] = green;
        updatedColour[2] = blue;
        
        // Update old colour
        if (colourIncrement >= interpolationFramesColour)
        {
            oldColourList[i][0] = currentAccurateColourList[i][0];
            oldColourList[i][1] = currentAccurateColourList[i][1];
            oldColourList[i][2] = currentAccurateColourList[i][2];
            
        }
    }
 
    if (colourIncrement >= interpolationFramesColour) {
        // Then reset
        colourIncrement = 0;
    }

}
