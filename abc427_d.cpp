#include <bits/stdc++.h>

typedef long long int ll;

using std::cin;
using std::cout;

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

#define MAXN (ll)(2e5+5)
#define MAXK (ll)(25)

struct Graph {
    struct Edge {
        ll v, next;
    };

    Edge e[MAXN];
    ll head[MAXN], tot;

    void add_edge(ll u, ll v) {
        ++tot;
        e[tot] = { v, head[u] };
        head[u] = tot;
        return;
    }

    void clear() {
        tot = 0;
        memset(head, 0, sizeof head);
        memset(e, 0, sizeof e);
        return;
    }
};



Graph g, suf;
char ch[MAXN];
bool flag[MAXN][2]; //记录这个节点是否可以到达某个节点字符为A or B
ll dp[MAXN][MAXK]; //1 是 Alice  2是Bob
ll n, m, k, t;

void init() {
    g.clear();
    suf.clear();
    memset(ch, 0, sizeof ch);
    memset(flag, 0, sizeof flag);
    memset(dp, 0, sizeof dp);
    return;
}

void solve() {
    init();


    //cin >> n >> m >> k;
    fread(&n), fread(&m), fread(&k);

    k <<= 1;

    for (ll i = 1; i <= n; ++i) {
        cin >> ch[i];
    }

    for (ll i = 0; i < m; ++i) {
        ll u, v, w;
        //cin >> u >> v;
        fread(&u), fread(&v);
        g.add_edge(u, v);
        suf.add_edge(v, u);
        flag[u][ch[v] - 'A'] = true;
    }

    //初始化dp状态
    std::queue<std::pair<ll, ll>> que;
    for (ll i = 1; i <= n; ++i) {
        //初始化每个dp[][1]
        if (k & 1) {
            //dp[][1]  是Alice走
            if (flag[i][0]) {
                dp[i][1] = 1;
            }
            else {
                dp[i][1] = 2;
            }
        }
        else {
            if (flag[i][1]) {
                dp[i][1] = 2;
            }
            else {
                dp[i][1] = 1;
            }
        }
        que.push({ i, 1 });
    }

    while (!que.empty()) {
        ll u = que.front().first, j = que.front().second;
        que.pop();
        for (ll i = suf.head[u]; i; i = suf.e[i].next) {
            ll v = suf.e[i].v;
            if (!dp[v][j + 1]) {
                //此前没有任何状态
                //直接将当前状态塞进去
                dp[v][j + 1] = dp[u][j];
                if (j + 1 < k) {
                    que.push({ v, j + 1 });
                }
                continue;
            }
            else {
                //此前存在状态ss
                //分类讨论
                if (k - j & 1) {
                    //是Alice在走
                    if (dp[v][j + 1] == 1) {
                        //目前Alice以及存在必胜策论
                        //那么没必要爱走其他策略
                        continue;
                    }
                    else {
                        //那么此时 dp[v][j+1] = 2
                        if (dp[u][j] != dp[v][j + 1]) {
                            dp[v][j + 1] = dp[u][j];
                            que.push({ v, j + 1 });
                            //被更新了， 更新dp入队
                        }
                    }
                }
                else {
                    //是Bob在走
                    if (dp[v][j + 1] == 2) {
                        //目前Bob以及存在必胜策论
                        //那么没必要爱走其他策略
                        continue;
                    }
                    else {
                        //那么此时 dp[v][j+1] = 1
                        if (dp[u][j] != dp[v][j + 1]) {
                            dp[v][j + 1] = dp[u][j];
                            que.push({ v, j + 1 });
                            //被更新了， 更新dp入队
                        }
                    }
                }
            }
        }
    }

    printf("%s\n", dp[1][k] == 1 ? "Alice" : "Bob");

}

int main() {
    freopen("input.txt", "r", stdin);
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);

    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}