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
    
    vector() : _size(0), _capacity(0) { _data = new T[_capacity]; }
    
    vector(size_type count, const T& value = T()) : _size(count), _capacity(calculateGrowth(count)) {
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
        _capacity = other.capacity();
        _data = new T[_size];
        
        std::copy(other.begin(), other.end(), _data);
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
		// Make sure our data is not nullptr (used in unit tests to prevent double deconstruction)
		if (_data != nullptr) {
			delete[] _data;
			_data = nullptr;
		}
    }
    
    vector& operator=(const vector& other) {
		vector(other);
    }
    
    void assign(size_t count, const T& value) {
		clear();

		if (count > _capacity) {
			reallocate(count);
		}

		for (int i = 0; i < count; i++) {
			_data[i] = value;
		}

		_size = count;
    }
    
	/*
    template<class InputIt>
    void assign(InputIt first, InputIt last) {
        // TODO
    }
	*/
    
    void push_back(const T& item) {
		if (_size == _capacity) {
			reallocate(_capacity + 1);
		}

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
		return at(pos);
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
        // TODO verify
        return std::numeric_limits<size_type>::max();
    }
    
    void reserve(size_type new_cap) {
        if (new_cap > max_size()) {
            throw new std::length_error("capacity cannot be larger than max size");
        }
        _capacity = new_cap;
    }

	size_type capacity() const {
		return _capacity;
	}
    
    // C++11
    void shrink_to_fit() {
        _capacity = _size;
        // reallocate
    }
    
    void clear() {
        for (int i = 0; i < _size; i++) {
			_data[i].~T();
        }
        
        _size = 0;
    }
private:
    size_type _size;
    size_type _capacity;
    T* _data;

	size_type calculateGrowth(size_type newSize) const {
		if (_capacity > max_size() - _capacity / 2) {
			return newSize;
		}

		const size_type geometric = _capacity * 1.5;

		if (geometric < newSize) {
			return newSize;
		}

		return geometric;
	}

	void reallocate(size_type minSize) {
		const size_type newCapacity = calculateGrowth(minSize);

		T* newData = new T[newCapacity];
		std::copy(_data, _data + _size, newData);
		delete[] _data;
		
		_data = newData;
		_capacity = newCapacity;
	}
};

#endif /* vector_h */
