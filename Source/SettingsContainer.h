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
class SettingsContainer  :  public juce::Component,
                            public Button::Listener
{
public:
    SettingsContainer();
    ~SettingsContainer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked(Button* button) override;

private:
    int settingsComponentMinHeight = 1000;
    
    Viewport settingsViewport;
    
    SettingsComponent settingsComponent;
    
    TextButton closeButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsContainer)
};
