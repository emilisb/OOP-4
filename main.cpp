//
//  main.cpp
//  Vector
//
//  Created by Emilis Baliukonis on 05/05/2019.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#include <iostream>
#include "vector.h"

int main(int argc, const char * argv[]) {
    vector<int> numbers(5, 10);
    numbers.push_back(5);

    std::cout << numbers.at(0) << std::endl;
    return 0;
}
