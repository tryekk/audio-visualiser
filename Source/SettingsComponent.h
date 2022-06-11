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
extern int interpolationFrames;
extern int interpolationFramesColour;
extern int fftOrder;
extern bool displayClock;
extern bool displayFps;
extern bool showAccurateSamplePoints;
extern bool drawLines;
extern bool centreVerticalOrigin;
extern float verticalOriginModifier;
extern bool centreHorizontalOrigin;
extern float horizontalOriginModifier;
extern bool displayTopHalf;
extern bool invertTopHalf;
extern bool displayBottomHalf;

class SettingsComponent  :  public juce::Component,
                            public Slider::Listener,
                            public Button::Listener,
                            public juce::ChangeListener,
                            private juce::KeyListener
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
    
    bool keyPressed(const KeyPress &k, Component *c) override;

private:
    Label colourLabel;
    
    ColourSelector colourSelectorGain;
    ColourSelector colourSelectorBackground;
    ColourSelector colourSelectorPitchLow;
    ColourSelector colourSelectorPitchHigh;
    
    Label appearanceLabel;
        
    Slider lineHeightSlider;
    Label lineHeightLabel;
    
    Slider lineWidthSlider;
    Label lineWidthLabel;

    Slider interpolationFramesSlider;
    Label interpolationFramesLabel;
    
    Slider interpolationFramesColourSlider;
    Label interpolationFramesColourLabel;
    
    Label axisAlignLabel;
    
    ToggleButton centreVerticalOriginButton;
    Label centreVerticalOriginLabel;
    
    Slider verticalOriginSlider;
    Label verticalOriginLabel;
    
    ToggleButton centreHorizontalOriginButton;
    Label centreHorizontalOriginLabel;
    
    Slider horizontalOriginSlider;
    Label horizontalOriginLabel;
    
    Label displayLabel;
    
    ToggleButton displayClockButton;
    Label displayClockLabel;
    
    ToggleButton displayFpsButton;
    Label displayFpsLabel;
    
    ToggleButton displayAccuratePointsButton;
    Label displayAccuratePointsLabel;
    
    ToggleButton drawLinesButton;
    Label drawLinesLabel;
    
    ToggleButton displayTopHalfButton;
    Label displayTopHalfLabel;
    
    ToggleButton invertTopHalfButton;
    Label invertTopHalfLabel;
    
    ToggleButton displayBottomHalfButton;
    Label displayBottomHalfLabel;
    
    ComboBox interpolationTypeSelector;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsComponent)
};
