//
//  Timer.hpp
//  Uzduotis 2
//
//  Created by Emilis Baliukonis on 04/03/2019.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>

using namespace std::chrono;

class Timer {
public:
    void start();
    int duration();
private:
    high_resolution_clock::time_point startTime;
};

#endif /* Timer_hpp */