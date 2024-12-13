#pragma once
#include <stdint.h>

inline uint64_t pow(int32_t base, int32_t index) {
    long long int result = 1;
    while (index > 0) /*ָ������0����ָ���۰룬��������ƽ���Ĳ���*/ {
        if (index % 2 == 1) /*ָ��Ϊ����*/ {
            index -= 1;         //ָ����һ
            index /= 2;         //ָ���۰�
            result *= base;     //�������ǰ��۳˺󱣴�
            base *= base;       //��������ƽ��
        }
        else /*ָ��Ϊż��*/ {
            index /= 2;         //ָ���۰�
            base *= base;       //��������ƽ��
        }
    }
    return result;
}