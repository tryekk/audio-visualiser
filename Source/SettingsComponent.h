/*
  ==============================================================================

    SettingsComponent.h
    Created: 4 Nov 2021 1:37:42pm
    Author:  Tom Carter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "AnalyserComponent.h"

//==============================================================================
/*
*/

extern float heightModifier;
extern float widthModifier;
extern int noOfPoints;

class SettingsComponent  :  public juce::Component,
                            public Slider::Listener
{
public:
    SettingsComponent();
    ~SettingsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider* slider) override;

private:
    Slider lineHeightSlider;
    Label lineHeightLabel;
    
    Slider lineWidthSlider;
    Label lineWidthLabel;

    Slider noOfPointsSlider;
    Label noOfPointsLabel;
    
    ToggleButton displayClockButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsComponent)
};
