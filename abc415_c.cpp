//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <iostream>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          20

typedef long long int ll;
typedef unsigned long long int ull;

//�����������
template< typename Type >
inline Type fread(Type* p = nullptr);

//�����������
template<typename Type>
inline void fwrite(Type x);

char str[MAXN];
ll t, n;

inline void slove() {
	fread(&n);
    cin >> (s + 1);

    dp[0] = true; // ��ƿ�ӿ��԰�ȫ���
    for (int i = 1; i < (1 << n); i++) {
        dp[i] = false; // ���赱ǰ״̬���ܰ�ȫ���
        if (s[i] == '1') // Σ��״̬��ֱ������
            continue;
        for (int j = 0; j < n; j++) // ö��ÿһ�ֻ�ѧ����
            if (i >> j & 1) // ���i��2^j��һλ��Ϊ1����ʾi�д��ڵ�j������
                dp[i] |= dp[i ^ (1 << j)]; // ��������j������֮ǰ��״̬���԰�ȫ�õ�����ǰ״̬iҲ����
    }

    if (dp[(1 << n) - 1] == true) // ����������ʾ����ڵ�״̬�Ƿ��ܹ���ȫ�õ�
        cout << "Yes\n";
    else
        cout << "No\n";
    return;
}


int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

	fread(&t);

    while (t--) {
        slove();
    }



#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type fread(Type* p) {
#if _FREAD
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != nullptr) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
#else
    if (p == nullptr) {
        Type temp;
        p = &temp;
    }
    scanf("%lld", p);
    return *p;


#endif // _FREAD
}


template<typename Type>
inline void fwrite(Type x) {
    int sta[MAX_NUM_SIZE];
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) {
        putchar(sta[--top] + '0');
    }  // 48 �� '0'
    return;
}



/**
 *              ,----------------,              ,---------,
 *         ,-----------------------,          ,"        ,"|
 *       ,"                      ,"|        ,"        ,"  |
 *      +-----------------------+  |      ,"        ,"    |
 *      |  .-----------------.  |  |     +---------+      |
 *      |  |                 |  |  |     | -==----'|      |
 *      |  |                 |  |  |     |         |      |
 *      |  |  C:\>rp++       |  |  |     |`---=    |      |
 *      |  |                 |  |  |     |==== ooo |      ;
 *      |  |                 |  |  |     |(((( [33]|    ,"
 *      |  `-----------------'  | /      |((((     |  ,"
 *      +-----------------------+/       |         |,"
 *         /_)______________(_/          +---------+
 *    _______________________________
 *   /  oooooooooooooooo  .o.  oooo /,   /-----------
 *  / ==ooooooooooooooo==.o.  ooo= //   /\--{)B     ,"
 * /_==__==========__==_ooo__ooo=_/'   /___________,"
 *
 */