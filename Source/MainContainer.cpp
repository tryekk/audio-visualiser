/*
  ==============================================================================

    HomePageContainer.cpp
    Created: 3 Nov 2021 3:35:58pm
    Author:  Tom Carter

  ==============================================================================
*/

#include <iostream>
#include <JuceHeader.h>

#include "MainContainer.h"

//==============================================================================
MainContainer::MainContainer()
{
    setSize (1280, 720);
    addAndMakeVisible(audioVisualiserComponent);
    
//    addAndMakeVisible(homePageComponent);
    addAndMakeVisible(settingsComponent);
}

MainContainer::~MainContainer()
{
}

void MainContainer::paint (juce::Graphics& g)
{
}

void MainContainer::resized()
{
    homePageComponent.setBounds(0, 0, 280, getHeight());
    audioVisualiserComponent.setBounds(getLocalBounds());
    settingsComponent.setBounds(getWidth() - 280, 0, 280, getHeight());
}
