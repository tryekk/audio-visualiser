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

Colour gainColour = juce::Colours::lightgreen;
Colour backgroundColour = juce::Colours::black;
Colour lowPitchColour = juce::Colours::blue;
Colour highPitchColour = juce::Colours::red;
float heightModifier;
float widthModifier;
int noOfPoints;
bool displayClock;
bool showAccurateSamplePoints;
bool displayTopHalf = true;
bool invertTopHalf = true;
bool displayBottomHalf = true;

SettingsComponent::SettingsComponent()
{
    setSize(360, 720);
    
    closeButton.setToggleState(true, NotificationType::dontSendNotification);
//    closeButton.onClick = [this] () {std::cout<<"Hello\n";};
    closeButton.addListener(this);
    addAndMakeVisible(closeButton);
    closeButton.setButtonText("X");
    
    
    addAndMakeVisible(colourSelectorGain);
    colourSelectorGain.setCurrentColour(gainColour);
    colourSelectorGain.addChangeListener(this);
    
    addAndMakeVisible(colourSelectorBackground);
    colourSelectorBackground.setCurrentColour(backgroundColour);
    colourSelectorBackground.addChangeListener(this);
    
    addAndMakeVisible(colourSelectorPitchLow);
    colourSelectorPitchLow.setCurrentColour(lowPitchColour);
    colourSelectorPitchLow.addChangeListener(this);
    
    addAndMakeVisible(colourSelectorPitchHigh);
    colourSelectorPitchHigh.setCurrentColour(highPitchColour);
    colourSelectorPitchHigh.addChangeListener(this);
    
    
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
    displayTopHalfButton.setToggleState(true, dontSendNotification);
    displayTopHalfButton.addListener(this);
    
    addAndMakeVisible(displayTopHalfLabel);
    displayTopHalfLabel.setText("Display Top Half", dontSendNotification);
    displayTopHalfLabel.attachToComponent(&displayTopHalfButton, false);
    
    
    addAndMakeVisible(invertTopHalfButton);
    invertTopHalfButton.setToggleState(true, dontSendNotification);
    invertTopHalfButton.addListener(this);
    
    addAndMakeVisible(invertTopHalfLabel);
    invertTopHalfLabel.setText("Invert Top Half", dontSendNotification);
    invertTopHalfLabel.attachToComponent(&invertTopHalfButton, false);
    
    
    addAndMakeVisible(displayBottomHalfButton);
    displayBottomHalfButton.setToggleState(true, dontSendNotification);
    displayBottomHalfButton.addListener(this);
    
    addAndMakeVisible(displayBottomHalfLabel);
    displayBottomHalfLabel.setText("Display Bottom Half", dontSendNotification);
    displayBottomHalfLabel.attachToComponent(&displayBottomHalfButton, false);
    
    
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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SettingsComponent::resized()
{
    int padding = 30;
    closeButton.setBounds(5, 5, 20, 20);
    
    colourSelectorGain.setBounds(padding, 48, (getWidth() - (padding * 2)) / 2, 200);
    colourSelectorBackground.setBounds(padding + ((getWidth() - (padding * 2)) / 2) + 2, 48, (getWidth() - (padding * 2)) / 2, 200);
    colourSelectorPitchLow.setBounds(padding, 250, ((getWidth() - (padding * 2)) / 2) - 2, 200);
    colourSelectorPitchHigh.setBounds(padding + ((getWidth() - (padding * 2)) / 2) + 2, 250, (getWidth() - (padding * 2)) / 2, 200);
    
    lineHeightSlider.setBounds(padding, 500, getWidth() - (padding * 2), 20);
    lineWidthSlider.setBounds(padding, 550, getWidth() - (padding * 2), 20);
    noOfPointsSlider.setBounds(padding, 600, getWidth() - (padding * 2), 20);
    
    displayClockButton.setBounds(padding, 700, getWidth() - (padding * 2), 20);
    displayAccuratePointsButton.setBounds(padding, 750, getWidth() - (padding * 2), 20);
    displayTopHalfButton.setBounds(padding, 800, getWidth() - (padding * 2), 20);
    invertTopHalfButton.setBounds(padding, 850, getWidth() - (padding * 2), 20);
    displayBottomHalfButton.setBounds(padding, 900, getWidth() - (padding * 2), 20);
    sampleResolutionSelector.setBounds(padding, 950, getWidth() - (padding * 2), 20);
}

void SettingsComponent::changeListenerCallback(ChangeBroadcaster* source)
{
    if (source == &colourSelectorGain) {
        gainColour = colourSelectorGain.getCurrentColour();
    } else if (source == &colourSelectorBackground) {
        backgroundColour = colourSelectorBackground.getCurrentColour();
    } else if (source == &colourSelectorPitchLow) {
        lowPitchColour = colourSelectorPitchLow.getCurrentColour();
    } else if (source == &colourSelectorPitchHigh) {
        highPitchColour = colourSelectorPitchHigh.getCurrentColour();
    }
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
    } else if (button == &displayBottomHalfButton) {
        displayBottomHalf = !displayBottomHalf;
    }
}

void SettingsComponent::comboBoxChanged() {
    
}
