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
    addAndMakeVisible(scene1Button);
    scene1Button.addListener(this);
    auto scene1Icon = ImageCache::getFromMemory(BinaryData::settings_png, BinaryData::settings_pngSize);
    scene1Button.setImages(false, true, true, scene1Icon, 1.0f, juce::Colours::grey, scene1Icon, 1.0f, juce::Colours::white, scene1Icon, 1.0f, juce::Colours::white);
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
                juce::Justification::centredTop, true);   // draw some placeholder text
}

void HomePageComponent::resized()
{
    int padding = 30;
    
    scene1Button.setBounds(padding, padding, getWidth() - (padding * 2), 280);
}

void HomePageComponent::buttonClicked(Button *button)
{
    if (button == &scene1Button) {
        std::cout << "Scene 1\n";
    }
}
