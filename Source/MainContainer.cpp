/*
  ==============================================================================

    HomePageContainer.cpp
    Created: 3 Nov 2021 3:35:58pm
    Author:  Tom Carter

  ==============================================================================
*/

#include <iostream>
#include <JuceHeader.h>

#include "MainContainer.h"

//==============================================================================
MainContainer::MainContainer()
{
    setSize (1280, 720);
    addAndMakeVisible(audioVisualiserComponent);
    
    addAndMakeVisible(openSettingsButton);
    openSettingsButton.addListener(this);
    auto settingsIcon = ImageCache::getFromMemory(BinaryData::settings_png, BinaryData::settings_pngSize);
    openSettingsButton.setImages(false, true, true, settingsIcon, 0.6f, juce::Colours::white, settingsIcon, 1.0f, juce::Colours::white, settingsIcon, 1.0f, juce::Colours::white);
    
    
//    addAndMakeVisible(homePageComponent);
    addChildComponent(settingsComponent);
}

MainContainer::~MainContainer()
{
}

void MainContainer::paint (juce::Graphics& g)
{
}

void MainContainer::resized()
{
    homePageComponent.setBounds(0, 0, 280, getHeight());
    openSettingsButton.setBounds(getWidth() - 45, 10, 35, 35);
    audioVisualiserComponent.setBounds(getLocalBounds());
    settingsComponent.setBounds(getWidth() - 280, 0, 280, getHeight());
}

void MainContainer::buttonClicked(Button* button)
{
    if (button == &openSettingsButton) {
        settingsComponent.setVisible(true);
    }
}
