#pragma once

//==============================================================================
class AnalyserComponent   : public juce::AudioAppComponent,
                            private juce::Timer
{
public:
    AnalyserComponent(): forwardFFT (fftOrder),
    window (fftSize, juce::dsp::WindowingFunction<float>::hann)  // Windowing function
    {
        setOpaque (true);
        setAudioChannels (2, 0);  // we want a couple of input channels but no outputs
        startTimerHz (60);
        setSize (1280, 720);
    }

    ~AnalyserComponent() override
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int, double) override {}
    void releaseResources() override          {}

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        if (bufferToFill.buffer->getNumChannels() > 0)
        {
            auto* channelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);
 
            for (auto i = 0; i < bufferToFill.numSamples; ++i)
                pushNextSampleIntoFifo (channelData[i]);
        }
    }

    //==============================================================================
    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::black);

        g.setOpacity (1.0f);
//        g.setColour (juce::Colours::white);
        drawFrame (g);
        counter = counter + 1;
        colourIncrement = colourIncrement + 1;
        if (colourIncrement >= smoothingFramesColour) {
            colourIncrement = 0;
        }
    }

    void timerCallback() override {
        if (nextFFTBlockReady)
        {
            drawNextFrameOfSpectrum();
            nextFFTBlockReady = false;
            repaint();
        }
    }

    void pushNextSampleIntoFifo (float sample) noexcept  // One sample per call
    {
        // if the fifo contains enough data, set a flag to say
        // that the next frame should now be rendered.. (cpoied to FFT)
        if (fifoIndex == fftSize)               // number of samples
        {
            if (! nextFFTBlockReady)            // [12]
            {
                juce::zeromem (fftData, sizeof (fftData));
                memcpy (fftData, fifo, sizeof (fifo));
                nextFFTBlockReady = true;
            }
 
            fifoIndex = 0;  // Reset fifo
        }
 
        fifo[fifoIndex++] = sample;             // [12]
    }

    void drawNextFrameOfSpectrum() {
        window.multiplyWithWindowingTable (fftData, fftSize);       // Apply the windowing function to the data
        forwardFFT.performFrequencyOnlyForwardTransform (fftData);  // then render our FFT data
 
        auto mindB = -100.0f;
        auto maxdB =    0.0f;
 
        if (counter >= smoothingFrames) {
//            oldPositionData = scopeData;
            for (int i = 0; i < scopeSize; i++) {
                oldPositionData[i] = scopeData[i];
            }
            // Now in the for loop for every point in the scope width, calculate the level proportionally to the desired minimum and maximum decibels. To do this, we first need to skew the x-axis to use a logarithmic scale to better represent our frequencies. We can then feed this scaling factor to retrieve the correct array index and use the amplitude value to map it to a range between 0.0 .. 1.0.
            for (int i = 0; i < scopeSize; ++i)                         // Calculate level for each point in scope
            {
                auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - (float) i / (float) scopeSize) * 0.2f);
                
                auto fftDataIndex = juce::jlimit (0, fftSize / 2, (int) (skewedProportionX * (float) fftSize * 0.5f));
                
                auto level = juce::jmap (juce::jlimit (mindB, maxdB, juce::Decibels::gainToDecibels (fftData[fftDataIndex])
                                                                   - juce::Decibels::gainToDecibels ((float) fftSize)),
                                         mindB, maxdB, 0.0f, 1.0f);
     
                scopeData[i] = level;                                   // Set point with apropriate amplitude
            }
            
            // Reset
            counter = 0;
        }
    }
    void drawFrame (juce::Graphics& g) {
//        oldPosition = oldPosition + ((scopeData[5] - oldPosition) / smoothingFrames);
//        if (increment == smoothingFrames) {
//            increment = 0;
//        }
        
//        std::cout << (oldPosition + (((scopeData[5] - oldPosition) / smoothingFrames) * counter)) * 100 << "\n";
//        std::cout << counter << "\n";
        
        for (int i = 1; i < scopeSize; ++i)
        {
            auto width  = getLocalBounds().getWidth();
            auto height = getLocalBounds().getHeight();
            float fractionalWidth = width / scopeSize;
            float scaleFactor = 0.99f;
            
            float LowGainColourR = 0.0f;
            float LowGainColourG = 0.0f;
            float LowGainColourB = 0.0f;
            float HighGainColourR = 0.0f;
            float HighGainColourG = 235.0f;
            float HighGainColourB = 0.0f;
            
            float LowPitchColourR = 0.0f;
            float LowPitchColourG = 0.0f;
            float LowPitchColourB = 0.0f;
            float HighPitchColourR = 235.0f;
            float HighPitchColourG = 0.0f;
            float HighPitchColourB = 200.0f;
            
            if (showAccurateSamplePoints) {
                g.setColour(juce::Colours::gold);
                g.drawEllipse(i * (fractionalWidth) - (fractionalWidth / 2) * scaleFactor, height - (oldPositionData[i] * height) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, 5);

                g.setColour(juce::Colours::blue);
                g.drawEllipse(i * (fractionalWidth) - (fractionalWidth / 2) * scaleFactor, height - (scopeData[i] * height) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, 5);
            }
            
            // Update points
            if ((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / smoothingFrames) * counter)) != 0) {
    
                g.setColour (juce::Colour((
                                            (HighPitchColourR / scopeSize) * i) + ((HighGainColourR - LowGainColourR) * scopeData[i]),
                                            HighPitchColourG + ((HighGainColourG - LowGainColourG) * scopeData[i]),
                                            HighPitchColourB + ((HighGainColourB - LowGainColourB) * scopeData[i])));
                
                g.drawEllipse(i * fractionalWidth - (fractionalWidth / 2) * scaleFactor, (height - ((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / smoothingFrames) * counter)) * height)) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);
                
                g.drawLine(i * (fractionalWidth), height, i * (fractionalWidth), height - ((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / smoothingFrames) * counter)) * height), fractionalWidth * scaleFactor);
            }
            
//            g.setColour (juce::Colour(255.0f, (255.0f / scopeSize) * i, (255.0f / scopeSize) * i));
//
//            g.drawLine ({ (float) juce::jmap (i - 1, 0, scopeSize - 1, 0, width),
//                                  juce::jmap (scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
//                          (float) juce::jmap (i,     0, scopeSize - 1, 0, width),
//                                  juce::jmap (scopeData[i],     0.0f, 1.0f, (float) height, 0.0f) });
        }
    }

private:
    enum
    {
        fftOrder  = 10,             // No of sample sections on screen
        fftSize   = 1 << fftOrder,  // use the left bit shift operator which produces 2048 as binary number 100000000000
        scopeSize = 100             // number of points in the visual representation of the spectrum as a scope
    };
    
    
    juce::dsp::FFT forwardFFT;                      // FFT object
    juce::dsp::WindowingFunction<float> window;     // Windowing function to prevent spectral leakage
 
    float fifo [fftSize];                           // Sampling rate
    float fftData [2 * fftSize];                    // Result of FFT calculations
    int fifoIndex = 0;                              // Samples in FIFO
    bool nextFFTBlockReady = false;                 // Is next block ready to be rendered
    float scopeData [scopeSize];                    // Contains the points to be displayed on screen
    float oldPositionData [scopeSize];
    
    int counter = 0;
    int smoothingFrames = 8;
    int smoothingFramesColour = 500;
    int colourIncrement = 0;
    
    bool showAccurateSamplePoints = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalyserComponent)
};
