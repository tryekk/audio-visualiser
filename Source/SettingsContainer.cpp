/*
  ==============================================================================

    SettingsContainer.cpp
    Created: 2 Dec 2021 10:08:37am
    Author:  Tom Carter

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SettingsContainer.h"

//==============================================================================
SettingsContainer::SettingsContainer()
{
//    addAndMakeVisible(settingsComponent);
    addAndMakeVisible(settingsViewport);
    settingsViewport.setViewedComponent(&settingsComponent);
    
    // Set inital size
    if (getHeight() > settingsComponentMinHeight) {
        settingsComponent.setBounds(0, 0, settingsViewport.getMaximumVisibleWidth(), getHeight());
    } else {
        settingsComponent.setBounds(0, 0, settingsViewport.getMaximumVisibleWidth(), settingsComponentMinHeight);
    }
}

SettingsContainer::~SettingsContainer()
{
}

void SettingsContainer::paint (juce::Graphics& g)
{
}

void SettingsContainer::resized()
{
    settingsViewport.setBounds(getLocalBounds());
    if (getHeight() > settingsComponentMinHeight) {
        settingsComponent.setBounds(0, 0, settingsViewport.getMaximumVisibleWidth(), getHeight());
    } else {
        settingsComponent.setBounds(0, 0, settingsViewport.getMaximumVisibleWidth(), settingsComponentMinHeight);
    }
}
