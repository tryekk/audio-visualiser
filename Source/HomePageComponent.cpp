/*
  ==============================================================================

    HomePageComponent.cpp
    Created: 4 Nov 2021 11:24:00am
    Author:  Tom Carter

  ==============================================================================
*/

#include <iostream>
#include <JuceHeader.h>

#include "HomePageComponent.h"

//==============================================================================
HomePageComponent::HomePageComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(280, 720);
}

HomePageComponent::~HomePageComponent()
{
}

void HomePageComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("HomePageComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void HomePageComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
