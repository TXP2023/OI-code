#pragma once
#include <stdint.h>
#include <algorithm>

using ll = long long int;

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

template <typename T>
T gcd(T a, T b) {
	if (b == 0) {
		return a;
	} 
	return gcd(b, a % b);
}

template <typename T>
T lcm(T a, T b) {
	return a * b / gcd(b, a % b);
}

//计算组合数，在实际应用中可以拿一个c数组记录一下答案
ll get_combinations(ll _n, ll _m) {
    if (!_m) {
        //子集大小为m=0时, 子集只能是空的1种情况
        return 1;
        //return c[_n][_m] = 1;
    }
    if (_m == 1) {
        //子集大小为m=1时，n个元素中每个各有1中可能
        return _n;
        //return c[_n][_m] = n;
    }
    //利用 帕斯卡/杨辉三角公式 计算
    if (_n - _m < _m) {
        _m = _n - _m;
    }
    return get_combinations(_n - 1, _m) + get_combinations(_n - 1, _m - 1);
    //return c[_n][_m] = get_combinations(_n - 1, _m) + get_combinations(_n - 1, _m - 1);
}