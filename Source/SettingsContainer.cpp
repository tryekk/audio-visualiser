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
    addAndMakeVisible(settingsComponent);
}

SettingsContainer::~SettingsContainer()
{
}

void SettingsContainer::paint (juce::Graphics& g)
{
}

void SettingsContainer::resized()
{
    settingsComponent.setBounds(0, 0, getWidth(), getHeight());
}
