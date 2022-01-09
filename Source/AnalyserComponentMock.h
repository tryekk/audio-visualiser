/*
  ==============================================================================

    AnalyserComponentMock.h
    Created: 7 Jan 2022 7:28:52pm
    Author:  Tom Carter
    Part of Audio Visualiser Tests project

  ==============================================================================
*/

#pragma once


class AnalyserComponent
{
public:    
    AnalyserComponent();  // Windowing function

    ~AnalyserComponent();


    void paint();
    
    void drawNextFrameOfSpectrum();

    void drawFrame();
    
    int getInterpolationFrames()
    {
        return interpolationFrames;
    }
    
    int getCounter()
    {
        return counter;
    };
    
    int getColourCounter()
    {
        return colourIncrement;
    };
    
    float getCurrentColourRed()
    {
        return updatedColour[0];
    };
    float getCurrentColourGreen()
    {
        return updatedColour[1];
    };
    float getCurrentColourBlue()
    {
        return updatedColour[2];
    };
    
    
private:
    // Initialise required values
    
    enum
    {
        scopeSize = 5  // Number of points
    };
    
    // Contains the points locations to be displayed on screen (in JUCE application)
    float scopeData [scopeSize] = {0.1f, 1.6f, 20.0f, 16.4f, 5.0f};
    
    // Array of size 3 emulates juce::Colour
//    float gainColour [3] = {1.0f, 0.1f, 0.1f};
//    float lowPitchColour [3] = {0.1f, 0.2f, 0.2f};
//    float highPitchColour [3] = {0.9f, 0.3f, 0.3f};
    
    float currentAccurateColourList [scopeSize] [3] = {
        {0.5f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {0.5f, 1.0f, 1.0f}  // Colour that the measured colour will end up at after reaching interpolationFrames * loops
    };
    float oldColourList [scopeSize] [3] = {0.1f, 0.1f, 0.1f};
    
    float updatedColour [3] = {0, 0, 0};

    
    int counter = 0;
    int colourIncrement = 0;
    int interpolationFrames = 4;
    int interpolationFramesColour = 5;

};
