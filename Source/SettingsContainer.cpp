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
    
    settingsComponent.setBounds(0, 0, settingsViewport.getMaximumVisibleWidth(), 1000);
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
    settingsComponent.setBounds(0, 0, settingsViewport.getMaximumVisibleWidth(), 1000);
}
