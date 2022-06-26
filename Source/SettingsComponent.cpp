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

Colour gainColour = juce::Colour::fromRGBA(0, 255, 0, 255);
Colour backgroundColour = juce::Colours::black;
Colour lowPitchColour = juce::Colours::blue;
Colour highPitchColour = juce::Colour::fromRGBA(255, 0, 180, 255);
float heightModifier;
float widthModifier;
int interpolationFrames = 4;
int interpolationFramesColour = 6;
bool displayClock;
bool displayFps;
bool showAccurateSamplePoints;
bool drawLines = true;
bool centreVerticalOrigin = false;
float verticalOriginModifier = 2.0f;
bool centreHorizontalOrigin = false;
float horizontalOriginModifier = 2.0f;
bool mirrorVertical;
bool displayTopHalf = true;
bool invertTopHalf = true;
bool displayBottomHalf = true;

SettingsComponent::SettingsComponent()
{
//    setSize(360, 720);
    
    addAndMakeVisible(colourLabel);
    colourLabel.setText("Choose Colours", dontSendNotification);
    colourLabel.setJustificationType(juce::Justification::centredTop);
    
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
    
    
    
    addAndMakeVisible(appearanceLabel);
    appearanceLabel.setText("Appearance & Behaviour", dontSendNotification);
    appearanceLabel.setJustificationType(juce::Justification::centredTop);
    
    
    addAndMakeVisible(lineHeightSlider);
    lineHeightSlider.setRange(0.0f, 2.0f, 0.001f);
    lineHeightSlider.setValue(1.0f);
    lineHeightSlider.addListener(this);
    
    addAndMakeVisible(lineHeightLabel);
    lineHeightLabel.setText("Line Height", dontSendNotification);
    lineHeightLabel.attachToComponent(&lineHeightSlider, false);
    
    
    addAndMakeVisible(lineWidthSlider);
    lineWidthSlider.setRange(0.0f, 10.0f, 0.001f);
    lineWidthSlider.setValue(1.0f);
    lineWidthSlider.addListener(this);
    
    addAndMakeVisible(lineWidthLabel);
    lineWidthLabel.setText("Line Width", dontSendNotification);
    lineWidthLabel.attachToComponent(&lineWidthSlider, false);
    
    
    addAndMakeVisible(interpolationFramesSlider);
    interpolationFramesSlider.setRange(1, 60, 1);
    interpolationFramesSlider.setValue(4);
    interpolationFramesSlider.addListener(this);
    
    addAndMakeVisible(interpolationFramesLabel);
    interpolationFramesLabel.setText("Smoothing Frames", dontSendNotification);
    interpolationFramesLabel.attachToComponent(&interpolationFramesSlider, false);
    
    
    addAndMakeVisible(interpolationFramesColourSlider);
    interpolationFramesColourSlider.setRange(1, 60, 1);
    interpolationFramesColourSlider.setValue(6);
    interpolationFramesColourSlider.addListener(this);
    
    addAndMakeVisible(interpolationFramesColourLabel);
    interpolationFramesColourLabel.setText("Colour Smoothing Frames", dontSendNotification);
    interpolationFramesColourLabel.attachToComponent(&interpolationFramesColourSlider, false);
    
    
    
    addAndMakeVisible(axisAlignLabel);
    axisAlignLabel.setText("Axis Alignment", dontSendNotification);
    axisAlignLabel.setJustificationType(juce::Justification::centredTop);
    
    
    addAndMakeVisible(centreVerticalOriginButton);
    centreVerticalOriginButton.setToggleState(false, dontSendNotification);
    centreVerticalOriginButton.addListener(this);
    
    addAndMakeVisible(centreVerticalOriginLabel);
    centreVerticalOriginLabel.setText("Centre vertical origin", dontSendNotification);
    centreVerticalOriginLabel.attachToComponent(&centreVerticalOriginButton, false);
    
    
    addAndMakeVisible(verticalOriginSlider);
    verticalOriginSlider.setRange(1.0f, 6.0f, 0.01f);
    verticalOriginSlider.setValue(2.0f);
    verticalOriginSlider.addListener(this);
    
    addAndMakeVisible(verticalOriginLabel);
    verticalOriginLabel.setText("Vertical Origin", dontSendNotification);
    verticalOriginLabel.attachToComponent(&verticalOriginSlider, false);
    
    
    addAndMakeVisible(centreHorizontalOriginButton);
    centreHorizontalOriginButton.setToggleState(false, dontSendNotification);
    centreHorizontalOriginButton.addListener(this);
    
    addAndMakeVisible(centreHorizontalOriginLabel);
    centreHorizontalOriginLabel.setText("Centre horizontal origin", dontSendNotification);
    centreHorizontalOriginLabel.attachToComponent(&centreHorizontalOriginButton, false);
    
    
    addAndMakeVisible(horizontalOriginSlider);
    horizontalOriginSlider.setRange(0.01f, 6.0f, 0.01f);
    horizontalOriginSlider.setValue(2.0f);
    horizontalOriginSlider.addListener(this);
    
    addAndMakeVisible(horizontalOriginLabel);
    horizontalOriginLabel.setText("Horizontal Origin", dontSendNotification);
    horizontalOriginLabel.attachToComponent(&horizontalOriginSlider, false);
    
    
    addAndMakeVisible(mirrorVerticalButton);
    mirrorVerticalButton.addListener(this);
    
    addAndMakeVisible(mirrorVerticalButton);
    mirrorVerticalLabel.setText("Mirror Vertical Axis", dontSendNotification);
    mirrorVerticalLabel.attachToComponent(&mirrorVerticalButton, false);
    
    
    
    addAndMakeVisible(displayLabel);
    displayLabel.setText("Display options", dontSendNotification);
    displayLabel.setJustificationType(juce::Justification::centredTop);
    
    
    addAndMakeVisible(displayClockButton);
    displayClockButton.addListener(this);
    
    addAndMakeVisible(displayClockLabel);
    displayClockLabel.setText("Display Clock", dontSendNotification);
    displayClockLabel.attachToComponent(&displayClockButton, false);
    
    
    addAndMakeVisible(displayFpsButton);
    displayFpsButton.addListener(this);
    
    addAndMakeVisible(displayClockLabel);
    displayFpsLabel.setText("Display FPS", dontSendNotification);
    displayFpsLabel.attachToComponent(&displayFpsButton, false);
    
    
    addAndMakeVisible(displayAccuratePointsButton);
    displayAccuratePointsButton.addListener(this);
    
    addAndMakeVisible(displayAccuratePointsLabel);
    displayAccuratePointsLabel.setText("Display Accurate Points", dontSendNotification);
    displayAccuratePointsLabel.attachToComponent(&displayAccuratePointsButton, false);
    
    
    addAndMakeVisible(drawLinesButton);
    drawLinesButton.setToggleState(true, dontSendNotification);
    drawLinesButton.addListener(this);
    
    addAndMakeVisible(drawLinesLabel);
    drawLinesLabel.setText("Draw Lines", dontSendNotification);
    drawLinesLabel.attachToComponent(&drawLinesButton, false);
    
    
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
    
    
//    addAndMakeVisible(interpolationTypeSelector);
//    interpolationTypeSelector.addItem ("1", 1);
//    interpolationTypeSelector.addItem ("2", 2);
//    interpolationTypeSelector.addItem ("3", 3);
//    interpolationTypeSelector.onChange = [this] { comboBoxChanged(); };
//    interpolationTypeSelector.setSelectedId (1);
}

SettingsComponent::~SettingsComponent()
{
}

void SettingsComponent::paint (juce::Graphics& g)
{
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colour::fromRGBA(60, 60, 60, 180));
}

void SettingsComponent::resized()
{
    int padding = 30;
    
    colourLabel.setBounds(padding, 28, getWidth() - (padding * 2), 20);
    colourSelectorGain.setBounds(padding, 55, (getWidth() - (padding * 2)) / 2, 200);
    colourSelectorBackground.setBounds(padding + ((getWidth() - (padding * 2)) / 2), 55, (getWidth() - (padding * 2)) / 2, 200);
    colourSelectorPitchLow.setBounds(padding, 275, ((getWidth() - (padding * 2)) / 2), 200);
    colourSelectorPitchHigh.setBounds(padding + ((getWidth() - (padding * 2)) / 2), 275, (getWidth() - (padding * 2)) / 2, 200);
    
    appearanceLabel.setBounds(padding, 550, getWidth() - (padding * 2), 20);
    lineHeightSlider.setBounds(padding, 600, getWidth() - (padding * 2), 20);
    lineWidthSlider.setBounds(padding, 650, getWidth() - (padding * 2), 20);
    interpolationFramesSlider.setBounds(padding, 700, getWidth() - (padding * 2), 20);
    interpolationFramesColourSlider.setBounds(padding, 750, getWidth() - (padding * 2), 20);
    interpolationTypeSelector.setBounds(padding, 800, getWidth() - (padding * 2), 20);
    
    axisAlignLabel.setBounds(padding, 850, getWidth() - (padding * 2), 20);
    centreVerticalOriginButton.setBounds(padding, 900, getWidth() - (padding * 2), 20);
    verticalOriginSlider.setBounds(padding, 950, getWidth() - (padding * 2), 20);
    centreHorizontalOriginButton.setBounds(padding, 1000, getWidth() - (padding * 2), 20);
    horizontalOriginSlider.setBounds(padding, 1050, getWidth() - (padding * 2), 20);
    mirrorVerticalButton.setBounds(padding, 1100, getWidth() - (padding * 2), 20);
    
    displayLabel.setBounds(padding, 1150, getWidth() - (padding * 2), 20);
    displayClockButton.setBounds(padding, 1200, getWidth() - (padding * 2), 20);
    displayFpsButton.setBounds(padding, 1250, getWidth() - (padding * 2), 20);
    displayAccuratePointsButton.setBounds(padding, 1300, getWidth() - (padding * 2), 20);
    drawLinesButton.setBounds(padding, 1350, getWidth() - (padding * 2), 20);
    displayTopHalfButton.setBounds(padding, 1400, getWidth() - (padding * 2), 20);
    invertTopHalfButton.setBounds(padding, 1450, getWidth() - (padding * 2), 20);
    displayBottomHalfButton.setBounds(padding, 1500, getWidth() - (padding * 2), 20);
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
    } else if (slider == &interpolationFramesSlider) {
        interpolationFrames = interpolationFramesSlider.getValue();
    } else if (slider == &interpolationFramesColourSlider) {
        interpolationFramesColour = interpolationFramesColourSlider.getValue();
    } else if (slider == &verticalOriginSlider) {
        verticalOriginModifier = verticalOriginSlider.getValue();
    } else if (slider == &horizontalOriginSlider) {
        horizontalOriginModifier = horizontalOriginSlider.getValue();
    }
}

void SettingsComponent::buttonClicked(Button* button)
{
    if (button == &displayClockButton) {
        displayClock = !displayClock;
    } else if (button == &mirrorVerticalButton) {
        mirrorVertical = !mirrorVertical;
    } else if (button == &displayFpsButton) {
        displayFps = !displayFps;
    } else if (button == &displayAccuratePointsButton) {
        showAccurateSamplePoints = !showAccurateSamplePoints;
    } else if (button == &drawLinesButton) {
        drawLines = !drawLines;
    } else if (button == &centreVerticalOriginButton) {
        centreVerticalOrigin = !centreVerticalOrigin;
    } else if (button == &centreHorizontalOriginButton) {
        centreHorizontalOrigin = !centreHorizontalOrigin;
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

bool SettingsComponent::keyPressed(const KeyPress &k, Component *c) {
    if (k.getTextCharacter() == 'y') {
        std::cout << "key pressed\n";
        return true;
    } else {
        return false;
    }
}
