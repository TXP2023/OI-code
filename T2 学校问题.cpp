#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include <queue>
#include <algorithm>
#include <string>
#include <stack>

typedef long long int ll;

#define MAXN    (ll)(2e5+5)
#define MAX_VAL 5005

using std::cin;
using std::cout;
using std::max;

struct Student {
    ll h, w;
};

struct node {
    ll ls, rs;
    ll cnt;
};

Student stu[MAXN];
ll n, k, ans = 0;;
ll arr[5000][5005], sum[5000][5000];



int main() {
    //freopen("input.txt", "r", stdin);

    cin >> n >> k;

    ll maxw = 0;
    for (ll i = 1; i <= n; ++i) {
        cin >> stu[i].h >> stu[i].w;
        ++arr[stu[i].h][stu[i].w];
        maxw = std::max(stu[i].w, maxw);
    }

    for (size_t i = 1; i <= 5000; i++) {
        for (size_t j = 1; j <= 5000; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
        }
    }

    for (size_t h = 1; h <= 5000 - k; h++) {
        for (size_t w = 1; w <= 5000 - k; w++) {
            ans = std::max(ans, sum[h + k][w + k] - sum[h - 1][w + k] - sum[h + k][w - 1] + sum[h - 1][w - 1]);
        }
    }

    printf("%lld\n", ans);

    return 0;
}
