/*
  ==============================================================================

    AnalyserComponent.cpp
    Created: 23 Oct 2021 10:46:40am
    Author:  Tom Carter

  ==============================================================================
*/

#include <iostream>

#include "AnalyserComponent.h"

#include "SettingsComponent.h"


AnalyserComponent::AnalyserComponent(): forwardFFT (fftOrder),
window (fftSize, juce::dsp::WindowingFunction<float>::hann)
{
    setOpaque (true);
    setAudioChannels (2, 0);  // we want a couple of input channels but no outputs
    startTimerHz (60);
    setSize (800, 600);
}

AnalyserComponent::~AnalyserComponent()
{
    shutdownAudio();
}

void AnalyserComponent::prepareToPlay(int, double) {}

void AnalyserComponent::releaseResources() {}

void AnalyserComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (bufferToFill.buffer->getNumChannels() > 0)
    {
        auto* channelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);

        for (auto i = 0; i < bufferToFill.numSamples; ++i)
            pushNextSampleIntoFifo (channelData[i]);
    }
}

void AnalyserComponent::paint(juce::Graphics& g)
{    
    g.fillAll(backgroundColour);

    g.setOpacity (1.0f);
    drawFrame (g);
    
    counter = counter + 1;
    colourIncrement = colourIncrement + 1;
    n = n * 2;
    if (n >= interpolationFrames) {
        n = 1;
    }
    
    if (displayClock) {
        g.setColour(juce::Colours::white);
        String currentTimeHours = (String) juce::Time::getCurrentTime().getHours();
        String currentTimeMins = (String) juce::Time::getCurrentTime().getMinutes();
        if (currentTimeMins.length() == 1) {
            currentTimeMins = "0" + currentTimeMins;
        }
        String currentTime = currentTimeHours + ":" + currentTimeMins;
//        auto currentTimeString = currentTime.toString (false, true);
        int size = (int) getHeight() * 0.05;
        float fontSize = juce::jlimit (36, 72, size);
        g.setFont (juce::Font ("Calibri", fontSize, juce::Font::bold));
        g.drawText (currentTime, 120, 100, 500, 200, juce::Justification::topLeft, true);
    }
}

void AnalyserComponent::timerCallback()
{
    if (nextFFTBlockReady)
    {
        drawNextFrameOfSpectrum();
        nextFFTBlockReady = false;
        repaint();
    }
}

void AnalyserComponent::pushNextSampleIntoFifo (float sample) noexcept
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

void AnalyserComponent::drawNextFrameOfSpectrum()
{
    window.multiplyWithWindowingTable (fftData, fftSize);       // Apply the windowing function to the data
    forwardFFT.performFrequencyOnlyForwardTransform (fftData);  // then render our FFT data

    auto mindB = -100.0f;
    auto maxdB =    0.0f;

    if (counter >= interpolationFrames) {
        // Now in the for loop for every point in the scope width, calculate the level proportionally to the desired minimum and maximum decibels. To do this, we first need to skew the x-axis to use a logarithmic scale to better represent our frequencies. We can then feed this scaling factor to retrieve the correct array index and use the amplitude value to map it to a range between 0.0 .. 1.0.
        for (int i = 0; i < scopeSize; ++i)                         // Calculate level for each point in scope
        {
            oldPositionData[i] = scopeData[i];
            
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

void AnalyserComponent::drawFrame (juce::Graphics& g)
{
    for (int i = 1; i < scopeSize; ++i)
    {
        auto width  = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight();
        float fractionalWidth = width / scopeSize;
        float scaleFactor = widthModifier;  // Line thickness
        
        float LowGainColourR = 0.0f;
        float LowGainColourG = 0.0f;
        float LowGainColourB = 0.0f;
        
        float HighGainColourR = gainColour.getFloatRed();
        float HighGainColourG = gainColour.getFloatGreen();
        float HighGainColourB = gainColour.getFloatBlue();
        
//        float LowPitchColourR = 0.0f;
//        float LowPitchColourG = 0.0f;
//        float LowPitchColourB = 0.0f;
        float HighPitchColourR = highPitchColour.getFloatRed();
        float HighPitchColourG = highPitchColour.getFloatGreen();
        float HighPitchColourB = highPitchColour.getFloatBlue();
                    
        if (showAccurateSamplePoints) {
            g.setColour(juce::Colours::gold);
            g.drawEllipse(i * (fractionalWidth) - (fractionalWidth / 2) * scaleFactor, height - (oldPositionData[i] * height) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, 5);

            g.setColour(juce::Colours::blue);
            g.drawEllipse(i * (fractionalWidth) - (fractionalWidth / 2) * scaleFactor, height - (scopeData[i] * height) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, 5);
        }
        
        // Update points
        if ((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) != 0) {  // Change
            float red = oldColourList[i].getFloatRed() + (((currentAccurateColourList[i].getFloatRed() - oldColourList[i].getFloatRed()) / smoothingFramesColour) * colourIncrement);
            float green = oldColourList[i].getFloatGreen() + (((currentAccurateColourList[i].getFloatGreen() -  oldColourList[i].getFloatGreen()) / smoothingFramesColour) * colourIncrement);
            float blue = oldColourList[i].getFloatBlue() + (((currentAccurateColourList[i].getFloatBlue() - oldColourList[i].getFloatBlue()) / smoothingFramesColour) * colourIncrement);
            float RGBColour[3] = {red, green, blue};
            
//                drawLayer(g, i, RGBColour, 0.2f, 0.9f, scaleFactor * 0.4);
//                drawLayer(g, i, RGBColour, 0.4f, 0.9f, scaleFactor * 0.55);
            drawLayer(g, i, RGBColour, 0.6f, heightModifier * 0.8f, scaleFactor * 0.7);
            drawLayer(g, i, RGBColour, 0.8f, heightModifier * 0.7f, scaleFactor * 0.85);
            drawLayer(g, i, RGBColour, 1.0f, heightModifier * 0.6f, scaleFactor * 1);
                        
            // Update colour
            if (colourIncrement >= smoothingFramesColour) {
                oldColourList[i] = currentAccurateColourList[i];
                
                currentAccurateColourList[i] = juce::Colour::fromFloatRGBA(
                    ((HighPitchColourR / scopeSize) * i) + ((HighGainColourR - LowGainColourR) * scopeData[i]),
                    HighPitchColourG + ((HighGainColourG - LowGainColourG) * scopeData[i]),
                    HighPitchColourB + ((HighGainColourB - LowGainColourB) * scopeData[i]),
                    1.0f);
            }
        }
    
//            g.setColour (juce::Colour(255.0f, (255.0f / scopeSize) * i, (255.0f / scopeSize) * i));

//            g.drawLine ({ (float) juce::jmap (i - 1, 0, scopeSize - 1, 0, width),
//                                  juce::jmap (scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
//                          (float) juce::jmap (i,     0, scopeSize - 1, 0, width),
//                                  juce::jmap (scopeData[i],     0.0f, 1.0f, (float) height, 0.0f) });
    }
    
    
    if (colourIncrement >= smoothingFramesColour) {
        // Reset
        colourIncrement = 0;
    }
    
}

void AnalyserComponent::drawLayer (juce::Graphics& g, int i, float RGBColour[3], float transparency, float localHeightModifier, float scaleFactor)
{
    auto width  = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();
    float fractionalWidth = width / scopeSize;
    
    juce::Colour smoothedColour = juce::Colour::fromFloatRGBA(
                                                              RGBColour[0],
                                                              RGBColour[1],
                                                              RGBColour[2],
                                                              transparency);
    
    g.setColour(smoothedColour);
    
    if (centreOrigin) {
        
        g.drawEllipse(i * fractionalWidth - (fractionalWidth / 2) * scaleFactor, (height - ((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier))) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);

        g.drawLine(width / 2, height / 2, i * (fractionalWidth), height - ((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier)), fractionalWidth * scaleFactor);
        
    } else {
        if (interpolationType == 0) {
            // Bottom Half
            if (displayBottomHalf) {
                g.drawEllipse(i * fractionalWidth - (fractionalWidth / 2) * scaleFactor, (height - ((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier))) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);

                g.drawLine(i * (fractionalWidth), height, i * (fractionalWidth), height - ((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier)), fractionalWidth * scaleFactor);
            }
            
            // Top half
            if (displayTopHalf) {
                if (invertTopHalf) {
                    g.drawEllipse((width - (i * fractionalWidth)) - (fractionalWidth / 2) * scaleFactor, (((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier))) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);
                    
                    g.drawLine(width - (i * fractionalWidth), 0, width - (i * fractionalWidth), (oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier), fractionalWidth * scaleFactor);
                } else {
                    g.drawEllipse((i * fractionalWidth) - (fractionalWidth / 2) * scaleFactor, (((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier))) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);
                    
                    g.drawLine(i * fractionalWidth, 0, i * fractionalWidth, (oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier), fractionalWidth * scaleFactor);
                }
            }
        } else if (interpolationType == 1) {
            currentPositionData[i] = oldPositionData[i] + (((scopeData[i] - currentPositionData[i]) / interpolationFrames) * modifier);
//            currentPositionData[i] = oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / smoothingFrames) * counter);
//            oldPositionData[i] = currentPositionData[i];
            
            // Bottom Half
            if (displayBottomHalf) {
                g.drawEllipse(i * fractionalWidth - (fractionalWidth / 2) * scaleFactor, (height - (currentPositionData[i] * (height * localHeightModifier))) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);

                g.drawLine(i * (fractionalWidth), height, i * (fractionalWidth), height - (currentPositionData[i] * (height * localHeightModifier)), fractionalWidth * scaleFactor);
                
            }
           
            // Top half
            if (displayTopHalf) {
                if (invertTopHalf) {
                    g.drawEllipse((width - (i * fractionalWidth)) - (fractionalWidth / 2) * scaleFactor, ((currentPositionData[i] * (height * localHeightModifier))) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);
                    
                    g.drawLine(width - (i * fractionalWidth), 0, width - (i * fractionalWidth), currentPositionData[i] * (height * localHeightModifier), fractionalWidth * scaleFactor);
                } else {
                    g.drawEllipse((i * fractionalWidth) - (fractionalWidth / 2) * scaleFactor, ((currentPositionData[i] * (height * localHeightModifier))) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);
                    
                    g.drawLine(i * fractionalWidth, 0, i * fractionalWidth, currentPositionData[i] * (height * localHeightModifier), fractionalWidth * scaleFactor);
                }
            }
        } else if (interpolationType == 2) {
            
            modifier = modifier + ((interpolationFrames / n));
            if (modifier > interpolationFrames) {
                modifier = 0;
            }
            if (i == 7) {
//                std::cout << currentPositionData[i] << "\n";
                std::cout << modifier << "\n";
            }
            
            // Bottom Half
            g.drawEllipse(i * fractionalWidth - (fractionalWidth / 2) * scaleFactor, (height - ((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier))) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);

            g.drawLine(i * (fractionalWidth), height, i * (fractionalWidth), height - ((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * modifier)) * (height * localHeightModifier)), fractionalWidth * scaleFactor);
            
            // Top half
            if (invertTopHalf) {
                g.drawEllipse((width - (i * fractionalWidth)) - (fractionalWidth / 2) * scaleFactor, (((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier))) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);
                
                g.drawLine(width - (i * fractionalWidth), 0, width - (i * fractionalWidth), (oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier), fractionalWidth * scaleFactor);
            } else {
                g.drawEllipse((i * fractionalWidth) - (fractionalWidth / 2) * scaleFactor, (((oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier))) - (fractionalWidth / 2) * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor, fractionalWidth * scaleFactor);
                
                g.drawLine(i * fractionalWidth, 0, width - (i * fractionalWidth), (oldPositionData[i] + (((scopeData[i] - oldPositionData[i]) / interpolationFrames) * counter)) * (height * localHeightModifier), fractionalWidth * scaleFactor);
            }
        }
    }
}
