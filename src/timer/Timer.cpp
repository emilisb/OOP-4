//
//  Timer.cpp
//  Uzduotis 2
//
//  Created by Emilis Baliukonis on 04/03/2019.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#include "Timer.h"

void Timer::start() {
    startTime = high_resolution_clock::now();
}

int Timer::duration() {
    auto stopTime = high_resolution_clock::now();
    return duration_cast<milliseconds>(stopTime - startTime).count();
}