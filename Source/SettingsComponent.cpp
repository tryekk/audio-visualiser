/*
  ==============================================================================

    SettingsComponent.cpp
    Created: 4 Nov 2021 1:37:42pm
    Author:  Tom Carter

  ==============================================================================
*/

#include <iostream>
#include <JuceHeader.h>

#include "SettingsComponent.h"

#include "AnalyserComponent.h"

//==============================================================================

float heightModifier;
float widthModifier;
int noOfPoints;

SettingsComponent::SettingsComponent()
{
    setSize(280, 720);
    
    addAndMakeVisible(lineHeightSlider);
    lineHeightSlider.setRange(0.0f, 2.0f, 0.001f);
    lineHeightSlider.setValue(1.0f);
    lineHeightSlider.addListener(this);
    
    addAndMakeVisible(lineHeightLabel);
    lineHeightLabel.setText("Line height", dontSendNotification); // Might need to change in future
    lineHeightLabel.attachToComponent(&lineHeightSlider, false);
    
    addAndMakeVisible(lineWidthSlider);
    lineWidthSlider.setRange(0.0f, 2.0f, 0.001f);
    lineWidthSlider.setValue(1.0f);
    lineWidthSlider.addListener(this);
    
    addAndMakeVisible(lineWidthLabel);
    lineWidthLabel.setText("Line width", dontSendNotification); // Might need to change in future
    lineWidthLabel.attachToComponent(&lineWidthSlider, false);
    
    addAndMakeVisible(noOfPointsSlider);
    noOfPointsSlider.setRange(16, 512, 1);
    noOfPointsSlider.setValue(128);
    
    addAndMakeVisible(noOfPointsLabel);
    noOfPointsLabel.setText("Number of points", dontSendNotification);
    noOfPointsLabel.attachToComponent(&noOfPointsSlider, false);
    
    addAndMakeVisible(displayClockButton);
}

SettingsComponent::~SettingsComponent()
{
}

void SettingsComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void SettingsComponent::resized()
{
    int padding = 30;
    lineHeightSlider.setBounds(padding, 50, getWidth() - (padding * 2), 20);
    lineWidthSlider.setBounds(padding, 100, getWidth() - (padding * 2), 20);
    noOfPointsSlider.setBounds(padding, 150, getWidth() - (padding * 2), 20);
    displayClockButton.setBounds(padding, 200, getWidth() - (padding * 2), 20);
}

void SettingsComponent::sliderValueChanged(Slider* slider)
{
    if (slider == &lineHeightSlider) {
        heightModifier = lineHeightSlider.getValue();
    } else if (slider == &lineWidthSlider) {
        widthModifier = lineWidthSlider.getValue();
    } else if (slider == &noOfPointsSlider) {
        noOfPoints = noOfPointsSlider.getValue();
    }
}
