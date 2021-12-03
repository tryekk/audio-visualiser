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
  
}

HomePageComponent::~HomePageComponent()
{
}

void HomePageComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGBA(60, 60, 60, 230));

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Choose a scene", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void HomePageComponent::resized()
{

}
