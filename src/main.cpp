//
//  main.cpp
//  Vector
//
//  Created by Emilis Baliukonis on 05/05/2019.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#include <iostream>
#include <vector>
#include "vector.h"

class TestObject {
public:
    TestObject() {
        std::cout << "object constructor" << std::endl;
        ptr = &_value;
    }
    
    TestObject(const TestObject& other) {
        std::cout << "object copy constructor" << std::endl;
        ptr = &_value;
    }
    
    TestObject(int value) : _value(value) {
        std::cout << "object constructor with value" << std::endl;
    }
    
    ~TestObject() {
        std::cout << "object deconstructor" << std::endl;
    }
    
    int *ptr;
private:
    int _value = 10;
};

int main(int argc, const char * argv[]) {
    vector<TestObject> numbers;
    
    TestObject object;
    for (int i = 0; i < 10; i++) {
        numbers.push_back(object);
        std::cout << "capacity " << numbers.capacity() << " size " << numbers.size() << std::endl;
        std::cout << "pointer addr " << numbers.at(i).ptr << " value " << *numbers.at(i).ptr << std::endl;
    }

    std::cout << numbers.size() << std::endl;
    return 0;
}
