#pragma once
#include <stdint.h>

inline uint64_t pow(uint64_t base, uint64_t index, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (index > 0) /*ָ������0����ָ���۰룬��������ƽ���Ĳ���*/ {
        if (index % 2 == 1) /*ָ��Ϊ����*/ {
            index -= 1;         //ָ����һ
            index /= 2;         //ָ���۰�
            result *= base;     //�������ǰ��۳˺󱣴�
            result %= mod;
            base *= base;       //��������ƽ��
            base %= mod;
        }
        else /*ָ��Ϊż��*/ {
            index /= 2;         //ָ���۰�
            base *= base;       //��������ƽ��
        }
    }
    return result;
}