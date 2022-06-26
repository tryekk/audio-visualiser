/*
  ==============================================================================

    HomePageComponent.h
    Created: 4 Nov 2021 11:24:00am
    Author:  Tom Carter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class HomePageComponent  :  public juce::Component,
                            public Button::Listener
{
public:
    HomePageComponent();
    ~HomePageComponent() override;

    void paint (juce::Graphics&) override;
    
    void resized() override;

    void buttonClicked(Button* button) override;
    
private:
    ImageButton scene1Button;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HomePageComponent)
};
