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
class SettingsComponent  :  public juce::Component,
                            public Slider::Listener
{
public:
    SettingsComponent();
    ~SettingsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider* slider) override
    {
        if (slider == &lineHeightSlider) {
            analyserComponent.setGlobalHeightModifier(lineHeightSlider.getValue());
        }
    }

private:
    AnalyserComponent analyserComponent;
    
    Slider lineHeightSlider;
    Label lineHeightLabel;

    Slider noOfPointsSlider;
    Label noOfPointsLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsComponent)
};
