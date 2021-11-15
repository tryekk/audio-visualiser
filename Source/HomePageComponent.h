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
class HomePageComponent  : public juce::Component
{
public:
    HomePageComponent();
    ~HomePageComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HomePageComponent)
};
