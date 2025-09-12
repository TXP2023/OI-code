#include <iostream>
#include <stdio.h>

#define MAX_LENGTH	(size_t)(1e6+5)

using ll = long long int;

char mod[MAX_LENGTH], text[MAX_LENGTH];
ll next[MAX_LENGTH], mod_length, text_length;

inline void get_next() {
    next[1] = 0;
    for (size_t i = 2, j = 0; i <= mod_length; i++) {
        while (j && mod[i] != mod[j + 1]) {
            j = next[j]; // 无法从原先最长的next迭代，那么就从第二长的尝试迭代，以此类推
        }
        if (mod[i] == mod[j + 1]) {
            next[i] = ++j;
        }
    }
    return;
}

void kmp() {
    for (size_t i = 0, j = 0; i <= text_length; i++) {
        while (j && text[i + 1] != mod[j + 1]) {
            j = next[j];
        }
        if (text[i + 1] == mod[j + 1]) {
            ++j;
        }
        if (j == mod_length) {
            printf("%lld\n", i - j + 2);
            j = next[j];
        }
    }
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    scanf("%s%s", text + 1, mod + 1);

    mod_length = strlen(mod + 1);
    text_length = strlen(text + 1);

    get_next();
    kmp();

    for (size_t i = 1; i <= mod_length; i++) {
        printf("%lld ", next[i]);
    }

    return 0;

}