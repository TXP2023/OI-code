#pragma once
#include <stdint.h>
template<typename Type, size_t _MAX_SIZE>
class Vector {
public:

    Vector() {
        size_ = 0;
        return;
    }

    template<typename T>
    inline Type& operator [] (T _Pos) {
        return arr_[_Pos];
    }

    inline void push_back(Type _Value) {
        arr_[size_++] = _Value;
        return;
    }

    inline size_t size() {
        return size_;
    }

    inline Type* begin() {
        return arr_;
    }

    inline Type* end() {
        return &arr_[size_];
    }

private:
    Type arr_[_MAX_SIZE];
    size_t size_;
};