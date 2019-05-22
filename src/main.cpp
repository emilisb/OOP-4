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
    vector<int> vec({ 1, 2, 3, 4 });
    vector<int> other({ 1, 2, 3, 4 });
    
    if (vec == other) {
        return 1;
    }
    
    return 0;
    
    struct T {
        int a;
        double b;
        std::string c;
        
        T(int a, double b, std::string &&c) : a(a) , b(b), c(std::move(c)) {}
    };
    
    vector<T> objects;
    objects.emplace(objects.begin(), 42, 3.14, "foo");
    std::cout << objects.at(0).a << std::endl;
    /*
    std::allocator<std::string> allocator;
    std::string *array;
    
    array = allocator.allocate(0);
    allocator.deallocate(array, 0);
    
    array = allocator.allocate(3);
    allocator.construct(&array[0], "hello");
    allocator.construct(&array[1], "world");
    allocator.construct(&array[2], "test");
    
    std::cout << allocator.max_size() << std::endl;
    
    for (int i = 0; i < 3; i++) {
        std::cout << array[i] << " ";
    }
    
    std::cout << std::endl;
    
    std::cout << *(array) << " ";
    std::cout << *(array + 1) << " ";
    std::cout << *(array + 2) << " ";
    
    return 0;
    
    std::string *newArray;
    newArray = allocator.allocate(5);
    std::move(array, array + 3, newArray);
    
    return 0;
     */
    /*
    vector<std::string> students;
    int n = 200000;
    for (int i = 0; i < n; i++) {
        students.push_back("helllo");
        std::cout << students.at(i) << std::endl;
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << students.at(i) << std::endl;
    }
    
    return 0;
    */
    for (size_t i = 10000; i <= 100000000; i *= 10) {
        //benchmarkInsert(i);
        //benchmarkResize(i);
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
