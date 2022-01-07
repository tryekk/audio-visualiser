//
//  AnalyserComponentTests.cpp
//  Audio Visualiser - App
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
    EXPECT_EQ(0, analyserComponent.getCounter());
    
}
