#pragma once

#include <JuceHeader.h>

#include "SettingsComponent.h"

//==============================================================================

class AnalyserComponent   : public juce::AudioAppComponent,
                            private juce::Timer
{
public:    
    AnalyserComponent();  // Windowing function

    ~AnalyserComponent() override;

    //==============================================================================
    void prepareToPlay (int, double) override;
    void releaseResources() override;

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

    //==============================================================================
    void paint (juce::Graphics& g) override;

    void timerCallback() override;

    void pushNextSampleIntoFifo (float sample) noexcept;  // One sample per call

    void drawNextFrameOfSpectrum();
    
    void drawFrame (juce::Graphics& g);
    
    void drawLayer (juce::Graphics& g, int i, float RGBColour[3], float transparency, float heightModifier, float scaleFactor);
    
private:
    enum
    {
        fftOrder  = 10,             // No of sample sections on screen
        fftSize   = 1 << fftOrder,  // use the left bit shift operator which produces 2048 as binary number 100000000000
        scopeSize = 140             // number of points in the visual representation of the spectrum as a scope
    };
    
    juce::dsp::FFT forwardFFT;                      // FFT object
    juce::dsp::WindowingFunction<float> window;     // Windowing function to prevent spectral leakage
 
    float fifo [fftSize];                           // Sampling rate
    float fftData [2 * fftSize];                    // Result of FFT calculations
    int fifoIndex = 0;                              // Samples in FIFO
    bool nextFFTBlockReady = false;                 // Is next block ready to be rendered
    float scopeData [scopeSize];                    // Contains the points to be displayed on screen
    float oldPositionData [scopeSize];
    float currentPositionData [scopeSize];
    
    int counter = 0;
    int smoothingFramesColour = 6;
    int colourIncrement = 0;
    juce::Colour currentAccurateColourList [scopeSize];
    juce::Colour oldColourList [scopeSize];
    
    int interpolationType = 0;  // 0 = linear, 1 = exponential
    bool centreOrigin = false;
    int n = 1;
    int modifier = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalyserComponent)
};
