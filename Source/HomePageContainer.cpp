/*
  ==============================================================================

    HomePageContainer.cpp
    Created: 3 Dec 2021 3:46:57pm
    Author:  Tom Carter

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HomePageContainer.h"

//==============================================================================
HomePageContainer::HomePageContainer()
{
    addAndMakeVisible(homePageViewport);
    homePageViewport.setViewedComponent(&homePageComponent, true);
    
    // Set inital size
    if (getHeight() > homePageComponentMinHeight) {
        homePageComponent.setBounds(0, 0, homePageViewport.getMaximumVisibleWidth(), getHeight());
    } else {
        homePageComponent.setBounds(0, 0, homePageViewport.getMaximumVisibleWidth(), homePageComponentMinHeight);
    }
    
    closeButton.setToggleState(true, NotificationType::dontSendNotification);
    closeButton.addListener(this);
    addAndMakeVisible(closeButton);
    closeButton.setButtonText("X");
}

HomePageContainer::~HomePageContainer()
{
}

void HomePageContainer::paint (juce::Graphics& g)
{
}

void HomePageContainer::resized()
{
    homePageViewport.setBounds(getLocalBounds());
    if (getHeight() > homePageComponentMinHeight) {
        homePageComponent.setBounds(0, 0, homePageViewport.getMaximumVisibleWidth(), getHeight());
    } else {
        homePageComponent.setBounds(0, 0, homePageViewport.getMaximumVisibleWidth(), homePageComponentMinHeight);
    }
    
    closeButton.setBounds(5, 5, 20, 20);
}

void HomePageContainer::buttonClicked(Button* button)
{
    if (button == &closeButton) {
        HomePageContainer::setVisible(false);
    }
}
