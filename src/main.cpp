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
#include "timer/Timer.h"

#include <string>

class TestObject {
public:
    TestObject() {
        std::cout << "object constructor" << std::endl;
    }
    /*
    TestObject(const TestObject& other) {
        std::cout << "object copy constructor" << std::endl;
    }
     */
    
    TestObject(std::string value) : _value(value) {
        std::cout << "object constructor with value" << std::endl;
    }
    
    ~TestObject() {
        std::cout << "object deconstructor" << std::endl;
    }

    std::string _value;
};

void benchmarkInsert(size_t size) {
    vector<int> vec;
    std::vector<int> stdvec;
    Timer t;

    std::cout << "Benchmark: inserting " << size << " elements" << std::endl;

    t.start();

    for (int i = 0; i < size; i++) {
        vec.push_back(i);
    }

    std::cout << "My vector: << " << t.duration() << " ms" << std::endl;

    t.start();

    for (int i = 0; i < size; i++) {
        stdvec.push_back(i);
    }

    std::cout << "STD vector: << " << t.duration() << " ms" << std::endl;
}

void benchmarkResize(size_t size) {
    vector<int> vec;
    std::vector<int> stdvec;
    int totalRealloc = 0;
    Timer t;

    std::cout << "Benchmark: reallocations inserting " << size << " elements" << std::endl;

    t.start();

    for (int i = 0; i < size; i++) {
        vec.push_back(i);
        if (vec.size() == vec.capacity()) {
            totalRealloc++;
        }
    }

    std::cout << "My vector: << " << totalRealloc << std::endl;

    totalRealloc = 0;
    t.start();

    for (int i = 0; i < size; i++) {
        stdvec.push_back(i);
        if (stdvec.size() == stdvec.capacity()) {
            totalRealloc++;
        }
    }

    std::cout << "STD vector: << " << totalRealloc << std::endl;
}

int main(int argc, const char * argv[]) {
    for (size_t i = 10000; i <= 100000000; i *= 10) {
        benchmarkInsert(i);
        benchmarkResize(i);
    }

    vector<TestObject> numbers;
    
    TestObject object("hello");
    for (int i = 0; i < 10; i++) {
        numbers.push_back(object);
    }
    
    numbers.erase(numbers.begin(), numbers.begin() + 1);
    
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers.at(i)._value << std::endl;
    }

    std::cout << numbers.size() << std::endl;
    return 0;
}
