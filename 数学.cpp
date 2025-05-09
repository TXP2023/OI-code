#pragma once
#include <stdint.h>

inline uint64_t pow(uint64_t base, uint64_t index, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (index > 0) /*指数大于0进行指数折半，底数变其平方的操作*/ {
        if (index % 2 == 1) /*指数为奇数*/ {
            index -= 1;         //指数减一
            index /= 2;         //指数折半
            result *= base;     //分离出当前项并累乘后保存
            result %= mod;
            base *= base;       //底数变其平方
            base %= mod;
        }
        else /*指数为偶数*/ {
            index /= 2;         //指数折半
            base *= base;       //底数变其平方
        }
    }
    return result;
}