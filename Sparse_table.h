#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>
template<typename T, typename _RanIt>
class Sparse_table {
public:
    Sparse_table(size_t _size, _RanIt _First, _RanIt _Last, T(*_func)(const T, const T));

    T query(size_t _Left, size_t _Right);
private:
    T(*func_)(const T, const T);
    size_t size_;
    std::vector< std::vector< T > > dp_;
};

template<typename T, typename _RanIt>
Sparse_table<T, _RanIt>::Sparse_table(size_t _size, _RanIt _First, _RanIt _Last, T(*_func)(const T, const T)) {
    func_ = _func;
    size_ = _size;
    ll* LOG = new ll[size_ + 1];
    LOG[0] = -1;
    for (size_t i = 1; i <= size_; i++) {
        LOG[i] = LOG[i >> 1] + 1;
    }
    ll p = (int)(log(double(size_)) / log(2.0));
    dp_.resize(n + 2, std::vector< ll >(p + 1, 0));
    _RanIt it = _First;
    for (size_t i = 1; i <= size_; i++, it++) {
        dp_[i][0] = *it;
    }
    for (size_t i = 1; i <= p; i++) {
        for (size_t j = 1; j + (1 << i) <= n + 1; j++) {
            dp_[j][i] = (*func_)(dp_[j][i - 1], dp_[j + (1 << (i - 1))][i - 1]);
        }
    }
    delete[] LOG;
    return;

}

template<typename T, typename _RanIt>
T Sparse_table<T, _RanIt>::query(size_t _Left, size_t _Right) {
    int k = (int)(log(double(_Right - _Left + 1)) / log(2.0));
    return (*func_)(dp_[_Left][k], dp_[_Right - (1 << k) + 1][k]);  //
}