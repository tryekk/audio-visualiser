/*
  ==============================================================================

    AnalyserComponentMock.h
    Created: 7 Jan 2022 7:28:52pm
    Author:  Tom Carter

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
    
    int getCounter()
    {
        return counter;
    };
    
    
private:

    int counter = 0;
    int interpolationFrames = 4;
  
};
