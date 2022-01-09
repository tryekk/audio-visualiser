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

TEST(AnalyserComponent, counterTestForLoop) {
    AnalyserComponent analyserComponent;
    
//    for (int i = 0; i < analyserComponent.getCounter()) {
//        
//    }
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
    EXPECT_EQ(1, analyserComponent.getColourCounter());
    
}

TEST(AnalyserComponent, testColourUpdatesAndTransitions) {
    AnalyserComponent analyserComponent;
    
    analyserComponent.paint();  // 0
    analyserComponent.paint();  // 1
    analyserComponent.paint();  // 2

    EXPECT_EQ(0.2f, analyserComponent.getCurrentColour0());  // Target colour is 0.5f
    EXPECT_EQ(0.4f, analyserComponent.getCurrentColour1());  // Target colour is 1.0f
    EXPECT_EQ(0.4f, analyserComponent.getCurrentColour2());  // Target colour is 1.0f
    
}
