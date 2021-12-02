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
    addAndMakeVisible(settingsViewport);
    settingsViewport.setViewedComponent(&settingsComponent, true);
    
    // Set inital size
    if (getHeight() > settingsComponentMinHeight) {
        settingsComponent.setBounds(0, 0, settingsViewport.getMaximumVisibleWidth(), getHeight());
    } else {
        settingsComponent.setBounds(0, 0, settingsViewport.getMaximumVisibleWidth(), settingsComponentMinHeight);
    }
    
    closeButton.setToggleState(true, NotificationType::dontSendNotification);
//    closeButton.onClick = [this] () {std::cout<<"Hello\n";};
    closeButton.addListener(this);
    addAndMakeVisible(closeButton);
    closeButton.setButtonText("X");
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
    
    closeButton.setBounds(5, 5, 20, 20);
}

void SettingsContainer::buttonClicked(Button* button)
{
    if (button == &closeButton) {
        SettingsContainer::setVisible(false);
    }
}
