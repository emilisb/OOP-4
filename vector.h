//
//  vector.h
//  Vector
//
//  Created by Emilis Baliukonis on 05/05/2019.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#ifndef vector_h
#define vector_h

#include <stdexcept>
#include <iterator>
#include <limits>

template<class T>
class vector {
public:
    typedef size_t size_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    
    vector() : _size(0), _capacity(4) { _data = new T[_capacity]; }
    
    vector(size_type count, const T& value = T()) : _size(count), _capacity(count*2) {
        _data = new T[_capacity];
        std::fill_n(_data, count, value);
    }
    
    /*
     template<class InputIt>
     vector(InputIt first, InputIt last) {
     // TODO
     }
     */
    
    vector(const vector& other) {
        _size = other.size();
        _capacity = other._capacity();
        _data = new T[_size];
        
        std::copy(std::begin(other.data()), std::end(other.data()), std::begin(_data));
    }
    
    // C++11
    vector(vector&& other) {
        // TODO
    }
    
    vector(std::initializer_list<T> init) {
        _size = init.size();
        _capacity = _size * 2;
        _data = new T[_size];
        
        std::copy(init.begin(), init.end(), _data);
    }
    
    ~vector() {
        delete[] _data;
    }
    
    vector& operator=(const vector& other) {
        _size = other.size();
        _capacity = other._capacity();
        _data = new T[_size];
        
        std::copy(std::begin(other.data()), std::end(other.data()), std::begin(_data));
    }
    
    void assign(size_t count, const T& value) {
        // TODO
    }
    
    template<class InputIt>
    void assign(InputIt first, InputIt last) {
        // TODO
    }
    
    void push_back(const T& item) {
        // TODO reallocate
        _data[_size] = item;
        ++_size;
    }
    
    reference at(size_type pos) {
        if (pos < _size) {
            return _data[pos];
        }
        
        throw std::out_of_range("position is out of range");
    }
    
    const_reference at(size_type pos) const {
        if (pos < _size) {
            return _data[pos];
        }
        
        throw std::out_of_range("position is out of range");
    }
    
    reference operator[](size_type pos) {
        return _data[pos];
    }
    
    const_reference operator[](size_type pos) const {
        return _data[pos];
    }
    
    reference front() {
        return _data[0];
    }
    
    const_reference front() const {
        return _data[0];
    }
    
    reference back() {
        return _data[_size - 1];
    }
    
    const_reference back() const {
        return _data[_size - 1];
    }
    
    T* data() noexcept {
        return _data;
    }
    
    const T* data() const noexcept {
        return _data;
    }
    
    iterator begin() {
        return _data;
    }
    
    const_iterator begin() const {
        return _data;
    }
    
    iterator end() {
        return _data + _size;
    }
    
    const_iterator end() const {
        return _data + _size;
    }
    
    reverse_iterator rbegin() {
        // TODO
    }
    
    const_reverse_iterator rbegin() const {
        // TODO
    }
    
    reverse_iterator rend() {
        // TODO
    }
    
    const_reverse_iterator rend() const {
        // TODO
    }
    
    bool empty() const {
        return _size == 0;
    }
    
    size_type size() const {
        return _size;
    }
    
    size_type max_size() const {
        // TODO validate
        return std::numeric_limits<size_type>::max();
    }
    
    void reserve(size_type new_cap) {
        if (new_cap > max_size()) {
            throw new std::length_error("capacity cannot be larger than max size");
        }
        _capacity = new_cap;
        // TODO reallocate
    }
    
    // C++11
    void shrink_to_fit() {
        _capacity = _size;
        // reallocate
    }
    
    void clear() {
        for (int i = 0; i < _size; i++) {
            delete _data[i];
        }
        
        _size = 0;
    }
private:
    size_type _size;
    size_type _capacity;
    T* _data;
};

#endif /* vector_h */
