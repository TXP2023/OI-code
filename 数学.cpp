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

//�������������ʵ��Ӧ���п�����һ��c�����¼һ�´�
ll get_combinations(ll _n, ll _m) {
    if (!_m) {
        //�Ӽ���СΪm=0ʱ, �Ӽ�ֻ���ǿյ�1�����
        return 1;
        //return c[_n][_m] = 1;
    }
    if (_m == 1) {
        //�Ӽ���СΪm=1ʱ��n��Ԫ����ÿ������1�п���
        return _n;
        //return c[_n][_m] = n;
    }
    //���� ��˹��/������ǹ�ʽ ����
    if (_n - _m < _m) {
        _m = _n - _m;
    }
    return get_combinations(_n - 1, _m) + get_combinations(_n - 1, _m - 1);
    //return c[_n][_m] = get_combinations(_n - 1, _m) + get_combinations(_n - 1, _m - 1);
}