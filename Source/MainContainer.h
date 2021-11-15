/*
  ==============================================================================

    HomePageContainer.h
    Created: 3 Nov 2021 3:35:58pm
    Author:  Tom Carter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "HomePageComponent.h"
#include "AnalyserComponent.h"
#include "SettingsComponent.h"

//==============================================================================
/*
*/
class MainContainer  : public juce::Component
{
public:
    MainContainer();
    
    ~MainContainer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContainer)
    HomePageComponent homePageComponent;
    AnalyserComponent audioVisualiserComponent;
    SettingsComponent settingsComponent;
};
