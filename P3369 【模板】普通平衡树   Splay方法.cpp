//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <queue>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(1e5+5)

typedef long long int ll;
typedef unsigned long long int ull;

template<typename _T>
inline _T fpow(_T a, _T n, _T mod) {
    _T base = a, ret = 1;
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
//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

struct node {
    ll val, cnt, size;
    ll fa, son[2];

    node() {
        val = 0;
        cnt = 0;
        size = 0;
        fa = 0;
        son[0] = son[1] = 0;//2
        return;
    }
};

node tree[MAXN];
ll n, root, tot = 0;

//update
void upd(ll u) {
    tree[u].size = tree[tree[u].son[0]].size + tree[tree[u].son[1]].size + tree[u].cnt;
    return;
}

//旋转x
void rotate(ll u) {
    ll fa = tree[u].fa;
    ll gfa = tree[fa].fa;
    ll temp = (tree[fa].son[1] == u); //u位于父节点的那个儿子的位置
    //将节点x接在节点x的祖父节点的对应位置
    tree[gfa].son[tree[gfa].son[1] == fa] = u;
    tree[u].fa = gfa;
    //将u的子节点接在父节点上
    tree[fa].son[temp] = tree[u].son[temp ^ 1];
    tree[tree[u].son[temp ^ 1]].fa = fa;
    tree[u].son[temp ^ 1] = fa;
    tree[fa].fa = u;
    //在旋转后， 原来的父节点位于下方， 所以要先更新父节点
    upd(fa);
    upd(u);
    return;
}

//将u旋转为v的儿子， 当v=0时，将u设为root
void splay(ll u, ll v) {
    while (tree[u].fa != v) {
        ll fa = tree[u].fa, gfa = tree[fa].fa;
        if (gfa != v) {
            //if ((tree[gfa].son[0] == fa) ^ (tree[fa].son[0] == u)) {
            //    rotate(u);
            //}
            //else {
            //    rotate(fa);
            //}
            ((tree[gfa].son[0] == fa) ^ (tree[fa].son[0] == u)) ? rotate(u) : rotate(fa);
        }
        rotate(u);
    }
    if (!v) {
        //如果我们的目标时将x更新为根节点的话
        //更新根节点
        root = u;
    }
}



//将第一个大于等于x的值提到根节点
void pull(ll x) {
    if (!root) {
        //整个树就是空的，直接退出
        return;
    }
    //寻找值为u的节点
    ll u = root;
    while (x != tree[u].val && tree[u].son[x > tree[u].val]) {
        u = tree[u].son[x > tree[u].val];
    }
    splay(u, 0);
    return;
}

//查找x的前驱的位置
ll get_pre(ll x) {
    pull(x);
    if (tree[root].val < x) {
        return root;
    }
    ll u = tree[root].son[0];
    if (!u) {
        return 0; //不存在前驱
    }
    while (tree[u].son[1]) {
        u = tree[u].son[1];
    }
    return u;
}

//查找x的后继的位置
ll get_next(ll x) {
    pull(x);
    if (tree[root].val > x) {
        return root;
    }
    ll u = tree[root].son[1];
    if (!u) {
        return 0; //不存在前驱
    }
    while (tree[u].son[0]) {
        u = tree[u].son[0];
    }
    return u;
}

//insert
void ins(ll x) {
    ll u = root, fa = 0;
    //查找合适的位置使得可以插入x
    while (u && tree[u].val != x) {
        fa = u;
        u = tree[u].son[x > tree[u].val];
    }
    if (u) {
        //已经存在一个节点的权值为x
        ++tree[u].cnt;
        //upd(u);?
    }
    else {
        //不存在一个节点的值为x，要插入
        u = ++tot;
        if (fa) {
            //如果新节点不是根，那么更新父节点的指针
            tree[fa].son[x > tree[fa].val] = u;
        }
        //更新新节点的信息
        tree[u].son[1] = 0;
        tree[u].son[0] = 0;
        tree[u].val = x;
        tree[u].cnt = 1;
        tree[u].size = 1;
        tree[u].fa = fa;
    }
    splay(u, 0);
    return;
}

//remove
void rm(ll x) {
    ll pre = get_pre(x), next = get_next(x);
    splay(pre, 0);
    splay(next, pre);
    //删除节点一定位于前驱和后继之间
    ll u = tree[next].son[0];
    if (tree[u].cnt > 1) {
        --tree[u].cnt;
        splay(u, 0);
        //upd(u);
    }
    else {
        tree[next].son[0] = 0;
    }
}

//依据元素去查找kth
ll get_kth(ll x) {
    //直接将x提到根节点， 左子树+1就是
    pull(x);
    //return tree[tree[root].son[0]].size + 1; //before
    return tree[tree[root].son[0]].size + 1 + (tree[root].val < x ? tree[root].cnt : 0); //after
}

//依据kth去查找元素 返回位置
ll find_kth(ll kth) {
    if (tree[root].size < kth) {
        //区间内部就没有排名为kth的元素
        return -1;
    }
    ll u = root;
    while (true) {
        if (kth <= tree[tree[u].son[0]].size) {
            u = tree[u].son[0];
        }
        else {
            if (kth <= tree[u].cnt + tree[tree[u].son[0]].size) {
                //排名位于左节点和右键点之间，就是这个元素
                return u;
            }
            else {
                kth -= tree[u].cnt + tree[tree[u].son[0]].size;
                u = tree[u].son[1];
            }
        }
    }
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n);

    ins(MAX_INF);
    ins(-MAX_INF);
    while (n--) {
        ll opt, val;
        fread(&opt), fread(&val);
        switch (opt) {
        case 1:
            //插入
            ins(val);
            break;
        case 2:
            //删除
            rm(val);
            break;
        case 3:
            //查询x的排名
            printf("%lld\n", get_kth(val) - 1); //存在一个-INF作为哨兵
            break;
        case 4:
            //查询排名为kth的数
            printf("%lld\n", tree[find_kth(val + 1)].val);
            break;
        case 5:
            //查询x的前驱
            printf("%lld\n", tree[get_pre(val)].val);
            break;
        case 6:
            //查询x的后继
            printf("%lld\n", tree[get_next(val)].val);
            break;
        }
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
    }  // 48 是 '0'
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