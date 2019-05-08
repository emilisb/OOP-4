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
        _data = new T[_capacity];

        std::copy(other.begin(), other.end(), _data);
    }

    // C++11
    vector(vector&& other) {
        // TODO
    }

    vector(std::initializer_list<T> init) {
        _size = init.size();
        _capacity = calculateGrowth(_size);
        _data = new T[_capacity];

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
        _size = other.size();
        _capacity = other.capacity();
        printf("other size: %d\n", other.size());
        _data = new T[_capacity];
        
        std::copy(other.begin(), other.end(), _data);
        return *this;
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

    iterator begin() noexcept {
        return _data;
    }

    const_iterator begin() const noexcept {
        return _data;
    }

    const_iterator cbegin() const noexcept {
        return begin();
    }

    iterator end() noexcept {
        return _data + _size;
    }

    const_iterator end() const noexcept {
        return _data + _size;
    }

    const_iterator cend() const noexcept {
        return end();
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(_data + _size);
    }

    const_reverse_iterator rbegin() const noexcept {
        return rbegin();
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(_data);
    }

    const_reverse_iterator rend() const noexcept {
        return rend();
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

    void shrink_to_fit() {
        for (auto i = _size; i < _capacity; i++) {
            _data[i].~T();
        }
        _capacity = _size;
    }

    void clear() {
        for (size_type i = 0; i < _size; i++) {
            _data[i].~T();
        }

        _size = 0;
    }

    iterator insert(const_iterator pos, const T& value) {
        // TODO
    }

    iterator insert(const_iterator pos, T&& value) {
        // TODO
    }

    iterator insert(const_iterator pos, size_type count, const T& value) {
        // TODO
    }

    template<class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        // TODO
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        // TODO
    }

    template< class... Args >
    iterator emplace(const_iterator pos, Args&&... args) {
        // TODO
    }

    iterator erase(const_iterator pos) {
        // TODO
    }

    iterator erase(const_iterator first, const_iterator last) {
        // TODO
    }

    void push_back(const T& item) {
        if (_size == _capacity) {
            reallocate(_capacity + 1);
        }

        _data[_size] = item;
        ++_size;
    }

    //void push_back(T&& value) {
        // TODO
    //}

    template< class... Args >
    void emplace_back(Args&&... args) {
        // TODO
    }

    void pop_back() {
        back().~T();
        --_size;
    }

    void resize(size_type count) {
        // TODO
    }

    void resize(size_type count, const_reference value) {
        // TODO
    }

    void swap(vector& other) {
        // TODO
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
