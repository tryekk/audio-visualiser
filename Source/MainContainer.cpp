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
    
    setWantsKeyboardFocus(true);
    addKeyListener(this);
    
    addAndMakeVisible(audioVisualiserComponent);
    
    addChildComponent(openSettingsButton);
    openSettingsButton.addListener(this);
    auto settingsIcon = ImageCache::getFromMemory(BinaryData::settings_png, BinaryData::settings_pngSize);
    openSettingsButton.setImages(false, true, true, settingsIcon, 1.0f, juce::Colours::grey, settingsIcon, 1.0f, juce::Colours::white, settingsIcon, 1.0f, juce::Colours::white);
    
    addChildComponent(openHomeButton);
    openHomeButton.addListener(this);
    auto homeIcon = ImageCache::getFromMemory(BinaryData::home_png, BinaryData::home_pngSize);
    openHomeButton.setImages(false, true, true, homeIcon, 0.6f, juce::Colours::grey, homeIcon, 1.0f, juce::Colours::white, homeIcon, 1.0f, juce::Colours::white);
    
    addChildComponent(homePageComponent);
    addChildComponent(settingsContainer);

    openHomeButton.setVisible(true);
    openSettingsButton.setVisible(true);
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
    openHomeButton.setBounds(10, 10, 35, 35);
    
    audioVisualiserComponent.setBounds(getLocalBounds());
    settingsContainer.setBounds(getWidth() - 360, 0, 360, getHeight());
}

void MainContainer::buttonClicked(Button* button)
{
    if (button == &openSettingsButton) {
        settingsContainer.setVisible(true);
    } else if (button == &openHomeButton) {
        homePageComponent.setVisible(true);
    }
}

bool MainContainer::keyPressed(const KeyPress &k, Component *c) {
    if(k.getTextCharacter() == 'x') {
        isUIVisible = !isUIVisible;
        if (isUIVisible) {
            openHomeButton.setVisible(true);
            openSettingsButton.setVisible(true);
        } else {
            openHomeButton.setVisible(false);
            openSettingsButton.setVisible(false);
        }
        return true;
    } else {
        return false;
    }
}
