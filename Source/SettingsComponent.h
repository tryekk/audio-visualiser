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

extern Colour gainColour;
extern Colour backgroundColour;
extern Colour lowPitchColour;
extern Colour highPitchColour;
extern float heightModifier;
extern float widthModifier;
extern int noOfPoints;
extern int fftOrder;
extern bool displayClock;
extern bool showAccurateSamplePoints;
extern bool displayTopHalf;
extern bool invertTopHalf;
extern bool displayBottomHalf;

class SettingsComponent  :  public juce::Component,
                            public Slider::Listener,
                            public Button::Listener,
                            public juce::ChangeListener
{
public:
    SettingsComponent();
    ~SettingsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallback(ChangeBroadcaster* source) override;
    
    void sliderValueChanged(Slider* slider) override;
    
    void buttonClicked(Button* button) override;
    
    void comboBoxChanged();

private:
    TextButton closeButton;
    
    ColourSelector colourSelectorGain;
    ColourSelector colourSelectorBackground;
    ColourSelector colourSelectorPitchLow;
    ColourSelector colourSelectorPitchHigh;
        
    Slider lineHeightSlider;
    Label lineHeightLabel;
    
    Slider lineWidthSlider;
    Label lineWidthLabel;

    Slider noOfPointsSlider;
    Label noOfPointsLabel;
    
    ToggleButton displayClockButton;
    Label displayClockLabel;
    
    ToggleButton displayAccuratePointsButton;
    Label displayAccuratePointsLabel;
    
    ToggleButton displayTopHalfButton;
    Label displayTopHalfLabel;
    
    ToggleButton invertTopHalfButton;
    Label invertTopHalfLabel;
    
    ToggleButton displayBottomHalfButton;
    Label displayBottomHalfLabel;
    
    ComboBox sampleResolutionSelector;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsComponent)
};
