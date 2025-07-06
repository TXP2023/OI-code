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
#define MAXN          (size_t)(1e6+1)

typedef long long int ll;

//¿ì¶Áº¯ÊýÉùÃ÷
template< typename Type >
inline Type readf(Type* p = nullptr);

int barrel[MAXN][64];
int n, q, max_val = 0;

#define fast_read true

int main() {
#if fast_read
    readf(&n);
#else
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n;
#endif // fast_read

    for (int i = 1; i <= n; i++) {
#if fast_read
        int val = readf<int>();
#else
        int val;
        std::cin >> val;
#endif // fast_read
        for (int j = 1; j <= 63; ++j) {
            barrel[i][j] = barrel[i - 1][j] ^ (j == val);
        }
    }

#if fast_read
    readf(&q);
#else
    std::cin >> q;
#endif // fast_read

    while(q--) {
#if fast_read
        int l = readf<int>(), r = readf<int>();
#else
        int l, r;
        std::cin >> l >> r;
#endif // fast_read
        bool flag = false;
        for (int j = 1; j <= 63; ++j) {
            if (barrel[r][j] ^ barrel[l - 1][j]) {
                flag = true; //f[i][1] ~ f[i][63]    f[1][i] ~ f[63][i]
                break;
            }
        }
        puts(flag ? "YES" : "NO");
    }

    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != nullptr) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
}
