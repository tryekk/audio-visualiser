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
#include "SettingsContainer.h"

//==============================================================================
/*
*/
class MainContainer  :  public juce::Component,
                        public Button::Listener,
                        private juce::KeyListener
{
public:
    MainContainer();
    
    ~MainContainer() override;

    void paint (juce::Graphics&) override;
    
    void resized() override;
    
    void buttonClicked(Button* button) override;
            
    bool keyPressed(const KeyPress &k, Component *c) override;
    
private:
    HomePageComponent homePageComponent;
    AnalyserComponent audioVisualiserComponent;
    SettingsContainer settingsContainer;
    
    bool isUIVisible = true;
    
    ImageButton openSettingsButton;
    ImageButton openHomeButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContainer)
};
