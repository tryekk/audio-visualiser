/*
  ==============================================================================

    HomePageContainer.h
    Created: 3 Dec 2021 3:46:57pm
    Author:  Tom Carter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "HomePageComponent.h"

//==============================================================================
/*
*/
class HomePageContainer  :  public juce::Component,
                            public Button::Listener
{
public:
    HomePageContainer();
    ~HomePageContainer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked(Button* button) override;

private:
    int homePageComponentMinHeight = 1050;
    
    Viewport homePageViewport;
    
    HomePageComponent homePageComponent;
    
    TextButton closeButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HomePageContainer)
};
