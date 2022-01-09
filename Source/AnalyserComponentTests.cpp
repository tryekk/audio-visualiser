//
//  AnalyserComponentTests.cpp
//  Audio Visualiser Tests - App
//
//  Created by Tom Carter on 07/01/2022.
//  Copyright © 2022 Tom Carter. All rights reserved.
//

#include <gtest/gtest.h>
#include "AnalyserComponentMock.h"

TEST(AnalyserComponent, counterTest) {
    AnalyserComponent analyserComponent;
    
    analyserComponent.paint();
    EXPECT_EQ(1, analyserComponent.getCounter());
    
    analyserComponent.paint();
    EXPECT_EQ(2, analyserComponent.getCounter());

    analyserComponent.paint();
    EXPECT_EQ(3, analyserComponent.getCounter());

    analyserComponent.paint();
    EXPECT_EQ(4, analyserComponent.getCounter());
    
    analyserComponent.paint();
    EXPECT_EQ(1, analyserComponent.getCounter());
}

TEST(AnalyserComponent, colourCounterTest) {
    AnalyserComponent analyserComponent;
    
    analyserComponent.paint();
    EXPECT_EQ(1, analyserComponent.getColourCounter());
    
    analyserComponent.paint();
    EXPECT_EQ(2, analyserComponent.getColourCounter());

    analyserComponent.paint();
    EXPECT_EQ(3, analyserComponent.getColourCounter());
    
    analyserComponent.paint();
    EXPECT_EQ(4, analyserComponent.getColourCounter());
    
    analyserComponent.paint();
    EXPECT_EQ(5, analyserComponent.getColourCounter());
    
    analyserComponent.paint();
    EXPECT_EQ(6, analyserComponent.getColourCounter());

    analyserComponent.paint();
    EXPECT_EQ(1, analyserComponent.getColourCounter());
    
}

TEST(AnalyserComponent, testColourUpdatesAndTransitions) {
    AnalyserComponent analyserComponent;
    
    analyserComponent.paint();
    EXPECT_EQ(0.5f, analyserComponent.getCurrentColour0());
    
}
