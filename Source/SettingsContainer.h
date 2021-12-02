/*
  ==============================================================================

    SettingsContainer.h
    Created: 2 Dec 2021 10:08:37am
    Author:  Tom Carter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "SettingsComponent.h"

//==============================================================================
/*
*/
class SettingsContainer  : public juce::Component
{
public:
    SettingsContainer();
    ~SettingsContainer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Viewport settingsViewport;
    
    SettingsComponent settingsComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsContainer)
};
