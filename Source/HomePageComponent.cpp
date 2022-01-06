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
    auto scene1Icon = ImageCache::getFromMemory(BinaryData::visualiserspores_png, BinaryData::visualiserspores_pngSize);
    scene1Button.setImages(false, true, true, scene1Icon, 1.0f, juce::Colour::fromFloatRGBA(0, 0, 0, 0), scene1Icon, 1.0f, juce::Colour::fromFloatRGBA(50, 50, 50, 0.15f), scene1Icon, 1.0f, juce::Colour::fromFloatRGBA(150, 150, 150, 0.35f));
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
