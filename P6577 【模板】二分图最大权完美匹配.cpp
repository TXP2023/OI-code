#include <vector>
#include <queue>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>
#include <cstdio>

#define inf 1e18

typedef long long int ll;
typedef unsigned long long int  ull;
typedef long double lf;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< bool > ltag(0), rtag(0); //匹配
std::vector< ll > Lmatch(0), Rmatch(0); //匹配
std::vector< ll > Ltop(0), Rtop(0); //顶标
std::vector< ll > pre(0);
std::vector< ll > slack(0);
std::vector< std::vector< ll > > graph(0);
ll n, m, ans = 0;

inline void init(); //初始化
inline void find_Path(ll u); //增加增广路径
inline void Kuhn_Munkres(); //KM算法
inline void add_Path(ll u); //转移

inline void init() /*初始化*/ {
    Ltop.resize(n, -inf);
    std::vector< ll >(Ltop).swap(Ltop);
    Rtop.resize(n, 0);
    std::vector< ll >(Rtop).swap(Rtop);
    pre.resize(n, -1);
    std::vector< ll >(pre).swap(pre);
    Lmatch.resize(n, -1);
    std::vector< ll >(Lmatch).swap(Lmatch);
    Rmatch.resize(n, -1);
    std::vector< ll >(Rmatch).swap(Rmatch);
    ltag.resize(n, false);//
    std::vector< bool >(ltag).swap(ltag);
    rtag.resize(n, false);//
    std::vector< bool >(rtag).swap(rtag);
    slack.resize(n, 0);//
    std::vector< ll >(slack).swap(slack);
    graph.resize(n, std::vector< ll >(n, -inf));
    return;
}

inline void Kuhn_Munkres() {
    for (ll i = 0/*这里的i是枚举左部图点*/; i < n; i++) {
        find_Path(i); //给每个左部图点匹配
    }
    return;
}

inline void find_Path(ll u) {
    std::fill(ltag.begin(), ltag.end(), false);
    std::fill(rtag.begin(), rtag.end(), false);
    std::fill(slack.begin(), slack.end(), inf);
    std::queue< ll > que;//左部图点队列
    que.push(u);

    while (true) {
        while (!que.empty()) { //当前存在需要考虑的点
            ll v = que.front(); que.pop();
            ltag[v] = true; //这个左部图点已经被匹配过了
            //给这个左部图点匹配
            for (size_t i = 0/*这里的i是右部图点*/; i < n; i++) {
                /*且两个顶标和要小于当前左部图点与这个点的*/
                if (!rtag[i]/*这个右部图点没有被匹配*/ && Ltop[v] + Rtop[i] - graph[v][i] < slack[i]/*可减少最小d值*/) {
                    slack[i] = Ltop[v] + Rtop[i] - graph[v][i]; 
                    pre[i] = v;//右部图点i将要与当前被匹配的左部图点v匹配
                    if (slack[i] == 0)/*如果当前不存在差值, 即为相等边 添加增广路*/ {
                        rtag[i] = true; //这个点标记为被匹配
                        if (Rmatch[i] == -1) /*如果这个右部图节点之前没有被匹配*/ {
                            add_Path(i); //尝试增加到相等子图
                            return;
                        }
                        else { //如果之前已经被匹配过了 加入队列 那就过一会再说
                            que.push(Rmatch[i]);
                        }
                    }
                }
            }
        }
        ll MinDifference = inf/*找最小差值*/;
        for (size_t i = 0; i < n; i++) {
            if (!rtag[i]) /*如果这个右部图点不在相等子图里*/ {
                MinDifference = std::min(MinDifference, slack[i]);
            }
        }
        for (size_t i = 0; i < n; i++) {
            if (ltag[i]) {
                Ltop[i] -= MinDifference;
            }
            if (rtag[i]) {
                Rtop[i] += MinDifference;
            }
            else {
                slack[i] -= MinDifference; //??
            }
        }
        for (size_t i = 0; i < n; i++) {
            if (!rtag[i] && slack[i] == 0) /*添加到相等子图*/ {
                rtag[i] = 1;
                if (Rmatch[i] == -1) {
                    add_Path(i);
                    return;
                }
                else {
                    que.push(Rmatch[i]);
                }
            }
        }
    }
}


inline void add_Path(ll u) /*??*/ {
    ll t;
    while (u != -1) /*如果存在这个右部图点*/ {
        t = Lmatch[pre[u]]; //t为更新前的这个右部点的匹配对象的匹配
        Rmatch[u] = pre[u]; //他自己的匹配更新为对应的左部图点
        Lmatch[pre[u]] = u; //那么它的匹配对象更新为这个右部图点
        u = t; //新的右部点值
    }
    return;
}


int main() {
    freopen("input.txt", "r", stdin);

    n = readf< ull >(), m = readf< ull >();

    init();

    for (ll i = 0; i < m; i++) {
        ll u = readf< ll >(), //左部图
            v = readf< ll >(), //右部图
            w = readf< ll >(); //权值
        graph[u - 1][v - 1] = w;
        Ltop[u - 1] = std::max(Ltop[u - 1], w);
    }

    Kuhn_Munkres();
    //_sleep(2000);
    for (ll i = 0; i < n; i++) {
        ans += graph[Rmatch[i]][i];
    }
    printf("%lld\n", ans);
    for (ll i = 0; i < n; i++) {
        printf("%lld ", Rmatch[i] + 1);
    }
    //_sleep(2000);
    return 0;
}

template< typename T >
inline T readf() {
#if false
    T sum = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0') ch = getchar();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = getchar();
    return sum;
#else
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}