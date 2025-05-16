#pragma once
#include <stdint.h>
#include <algorithm>

inline int64_t fast_pow(int64_t a, int64_t n, int64_t mod) {
    int64_t base = a, ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * base;
            ret %= mod;
        }
        base = base * base;
        base %= mod;
        n >>= 1;
    }
    return ret % mod;
}

//µ›πÈ–¥∑®
inline uint64_t gcd(uint64_t _Val_1, uint64_t _Val_2) {
    return _Val_2 == 0 ? _Val_1 : gcd(_Val_2, _Val_1 % _Val_2);
}

//—≠ª∑–¥∑®
inline uint64_t gcd(uint64_t _Val_1, uint64_t _Val_2) {
    while (_Val_2) {
        //uint64_t tmp = _Val_1;
        //_Val_1 = _Val_2;
        //_Val_2 = tmp % _Val_2;
        std::swap(_Val_1, _Val_2);
        _Val_2 %= _Val_1;
    }
    return _Val_1;
}


inline uint64_t lcm(uint64_t _Val_1, uint64_t _Val_2) {
    return _Val_1 / gcd(_Val_1, _Val_2) * _Val_2;
}

