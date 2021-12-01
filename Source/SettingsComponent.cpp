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
bool displayClock;
bool showAccurateSamplePoints;
bool displayTopHalf;
bool invertTopHalf;

SettingsComponent::SettingsComponent()
{
    setSize(280, 720);
    
    closeButton.setToggleState(true, NotificationType::dontSendNotification);
//    closeButton.onClick = [this] () {std::cout<<"Hello\n";};
    closeButton.addListener(this);
    addAndMakeVisible(closeButton);
    closeButton.setButtonText("X");
      
    
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
    displayClockButton.addListener(this);
    
    addAndMakeVisible(displayClockLabel);
    displayClockLabel.setText("Display Clock", dontSendNotification);
    displayClockLabel.attachToComponent(&displayClockButton, false);
    
    
    addAndMakeVisible(displayAccuratePointsButton);
    displayAccuratePointsButton.addListener(this);
    
    addAndMakeVisible(displayAccuratePointsLabel);
    displayAccuratePointsLabel.setText("Display Accurate Points", dontSendNotification);
    displayAccuratePointsLabel.attachToComponent(&displayAccuratePointsButton, false);
    
    
    addAndMakeVisible(displayTopHalfButton);
    displayTopHalfButton.addListener(this);
    
    addAndMakeVisible(displayTopHalfLabel);
    displayTopHalfLabel.setText("Display Top Half", dontSendNotification);
    displayTopHalfLabel.attachToComponent(&displayTopHalfButton, false);
    
    
    addAndMakeVisible(invertTopHalfButton);
    invertTopHalfButton.addListener(this);
    
    addAndMakeVisible(invertTopHalfLabel);
    invertTopHalfLabel.setText("Invert Top Half", dontSendNotification);
    invertTopHalfLabel.attachToComponent(&invertTopHalfButton, false);
    
    
    addAndMakeVisible(sampleResolutionSelector);
    sampleResolutionSelector.addItem ("1", 1);
    sampleResolutionSelector.addItem ("2", 2);
    sampleResolutionSelector.addItem ("3", 3);
    sampleResolutionSelector.onChange = [this] { comboBoxChanged(); };
    sampleResolutionSelector.setSelectedId (1);
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
    closeButton.setBounds(5, 5, 20, 20);
    lineHeightSlider.setBounds(padding, 50, getWidth() - (padding * 2), 20);
    lineWidthSlider.setBounds(padding, 100, getWidth() - (padding * 2), 20);
    noOfPointsSlider.setBounds(padding, 150, getWidth() - (padding * 2), 20);
    displayClockButton.setBounds(padding, 220, getWidth() - (padding * 2), 20);
    displayAccuratePointsButton.setBounds(padding, 270, getWidth() - (padding * 2), 20);
    displayTopHalfButton.setBounds(padding, 320, getWidth() - (padding * 2), 20);
    invertTopHalfButton.setBounds(padding, 370, getWidth() - (padding * 2), 20);
    sampleResolutionSelector.setBounds(padding, 420, getWidth() - (padding * 2), 20);
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

void SettingsComponent::buttonClicked(Button* button)
{
    if (button == &displayClockButton) {
        displayClock = !displayClock;
    } else if (button == &closeButton) {
        SettingsComponent::setVisible(false);
    } else if (button == &displayAccuratePointsButton) {
        showAccurateSamplePoints = !showAccurateSamplePoints;
    } else if (button == &displayTopHalfButton) {
        displayTopHalf = !displayTopHalf;
    } else if (button == &invertTopHalfButton) {
        invertTopHalf = !invertTopHalf;
    }
}

void SettingsComponent::comboBoxChanged() {
    
}
