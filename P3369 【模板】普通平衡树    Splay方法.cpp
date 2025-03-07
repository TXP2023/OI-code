//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <time.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (long long)(1e6 + 5)
#define DEBUG         false

typedef long long int ll;
typedef unsigned long long int unill;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = nullptr);
#endif

//快速输出函数
template<typename Type>
inline void writef(Type x);


struct Splay_data {
    ll child[2]; //
    ll father; //父亲节点
    ll value; //节点权值
    ll size; //子树大小
    ll cnt;//此节点所表示的权值的出现次数

    Splay_data() {
        child[0] = 0, child[1] = 0;
        father = 0;
        value = 0;
        size = 0;
        cnt = 0;
        return;
    }
};


Splay_data tree[MAXN];
ll root, node_num;//根节点编号  节点个数

//在改变节点位置后，将节点 _P 的 size 更新。
void update_size(ll _Index) {
    tree[_Index].size = tree[tree[_Index].child[0]].size + tree[tree[_Index].child[1]].size + tree[_Index].cnt;
    return;
}

//判断节点 x 是父亲节点的左儿子还是右儿子。 左false 右true
bool get_child(ll _Index) {
    return _Index == tree[tree[_Index].father].child[1];
}

//销毁节点_Index
void clear(ll _Index) {
    tree[_Index] = Splay_data();
    return;
}

//将点_Index和其父节点旋转
void rotate(ll _Index) {
    //旋转需要保证:
    //  整棵 Splay 的中序遍历不变（不能破坏二叉查找树的性质）。
    //  受影响的节点维护的信息依然正确有效。
    //  root 必须指向旋转后的根节点。
    // 
    // 具体步骤
    // 1.将 y 的左儿子指向 x 的右儿子，且 x 的右儿子（如果 x 有右儿子的话）的父亲指向 y
    // 2.将 x 的右儿子指向 y，且 y 的父亲指向 x
    // 3.如果原来的 y 还有父亲 z，那么把 z 的某个儿子（原来 y 所在的儿子位置）指向 x，且 x 的父亲指向 z。
    //int y = fa[x], z = fa[y], chk = get(x);
    //ch[y][chk] = ch[x][chk ^ 1];
    //if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
    //ch[x][chk ^ 1] = y;
    //fa[y] = x;
    //fa[x] = z;
    //if (z) ch[z][y == ch[z][1]] = x;
    //maintain(y);
    //maintain(x);
    ll u = tree[_Index].father, v = tree[u].father, chk = get_child(_Index);
    //将 y 的左儿子指向 x 的右儿子
    tree[u].child[chk] = tree[_Index].child[chk ^ 1];
    //x 的右儿子（如果 x 有右儿子的话）的父亲指向 y
    if (tree[_Index].child[chk ^ 1]) {
        tree[tree[_Index].child[chk ^ 1]].father = u;
    }
    tree[_Index].child[chk ^ 1] = u;
    tree[u].father = _Index;
    //如果原来的 y 还有父亲 z，那么把 z 的某个儿子（原来 y 所在的儿子位置）指向 x，且 x 的父亲指向 z。
    tree[_Index].father = v;
    if (v) {
        //tree[v].child[get_child(u)] = _Index;
        tree[v].child[u == tree[v].child[1]] = _Index;
    }
    update_size(u);
    update_size(_Index);
    return;
}

//Splay 操作
void Splay(ll _Index) {
    //Splay 操作规定：每访问一个节点 x 后都要强制将其旋转到根节点。
    //
    for (ll i = tree[_Index].father; i = tree[_Index].father, i; rotate(_Index)) {
        if (tree[i].father) {
            rotate(get_child(_Index) == get_child(i) ? i : _Index);
        }
    }
    root = _Index;
    return;
}

//插入值 _Value
inline void insert(ll _Value) {
    /*
    插入操作是一个比较复杂的过程，具体步骤如下（假设插入的值为 k）：
    如果树空了，则直接插入根并退出。
    如果当前节点的权值等于 k 则增加当前节点的大小并更新节点和父亲的信息，将当前节点进行 Splay 操作。
    /否则按照二叉查找树的性质向下找，找到空节点就插入即可（请不要忘记 Splay 操作）。
    */

    //代码实现如下
    //如果树空了，则直接插入根并退出。
    if (!root) {
        tree[++node_num].value = _Value;
        tree[node_num].cnt++;
        root = node_num;
        update_size(root);
        return;
    }
    ll _Index = root, father = 0;
    while (1) {
        if (tree[_Index].value == _Value) {
            tree[_Index].cnt++;
            update_size(_Index);
            update_size(father);
            Splay(_Index);
            break;
        }
        father = _Index;
        _Index = tree[_Index].child[tree[_Index].value < _Value/*如果当前节点值小于插入节点值 表达式值为1 对应的右子节点 反之*/];
        //没有点的值为_Value，那么就要插入节点
        if (!_Index) {
            tree[++node_num].value = _Value;
            tree[node_num].cnt++;
            tree[node_num].father = father;//-
            tree[father].child[_Value > tree[father].value] = node_num;
            update_size(node_num);
            update_size(father);
            Splay(node_num);
            break;
        }
    }
    return;
}

//查询 _Value 的排名
inline ll get_Rank_By_Value(ll _Value) {
    ll _Index = root, ret = 0;
    while (1) {
        if (_Value < tree[_Index].value) {
            _Index = tree[_Index].child[0];
        }
        else {
            ret += tree[tree[_Index].child[0]].size;
            if (!_Index) {
                return ret + 1;
            }
            if (tree[_Index].value == _Value) {
                Splay(_Index);
                return ret + 1;
            }
            ret += tree[_Index].cnt;
            _Index = tree[_Index].child[1];
        }
    }
}

//查询排名 rank 的数
inline ll get_Value_By_Rank(ll _Rank) {
    ll _Index = root;
    while (1) {
        if (tree[_Index].child[0] && tree[tree[_Index].child[0]].size >= _Rank) {
            _Index = tree[_Index].child[0];
        }
        else {
            _Rank -= tree[tree[_Index].child[0]].size + tree[_Index].cnt;
            if (_Rank <= 0) {
                Splay(_Index);
                return tree[_Index].value;
            }
            _Index = tree[_Index].child[1];
        }
    }
}

//查询根节点的前驱的下标
inline ll _pre_of_root() {
    ll _Index = tree[root].child[0];
    if (!_Index) {
        return _Index;
    }

    while (tree[_Index].child[1]) {
        _Index = tree[_Index].child[1];
    }

    Splay(_Index);
    return _Index;
}

inline ll _next_of_root() {
    ll _Index = tree[root].child[1];
    if (!_Index) {
        return _Index;
    }

    while (tree[_Index].child[0]) {
        _Index = tree[_Index].child[0];
    }

    Splay(_Index);
    return _Index;
}


//删除操作
inline void remove(ll _Value) {
    //首先将 x 旋转到根的位置。
    get_Rank_By_Value(_Value);
    if (tree[root].cnt > 1) {
        tree[root].cnt--;
        update_size(root);
        return;
    }

    //x没有子节点
    if (!tree[root].child[0] && !tree[root].child[1]) {
        clear(root);
        root = 0;
        return;
    }

    //
    if (!tree[root].child[0]) {
        ll Index = root;
        root = tree[root].child[1];
        tree[root].father = 0;
        clear(Index);
        return;
    }
    if (!tree[root].child[1]) {
        ll Index = root;
        root = tree[root].child[0];
        tree[root].father = 0;
        clear(Index);
        return;
    }
    ll cur = root, pre = _pre_of_root();
    tree[tree[cur].child[1]].father = pre;
    tree[pre].child[1] = tree[cur].child[1];
    clear(cur);
    update_size(root);
    return;
}


inline ll pre(ll _Value) {
    insert(_Value);

    ll ret = tree[_pre_of_root()].value;
    remove(_Value);
    return ret;
}

void show(ll _Index) {
    if (!_Index) {
        return;
    }

    if (tree[_Index].child[0]) {
        printf("%lld  ", tree[_Index].value);
        printf("%lld\n", tree[tree[_Index].child[0]].value);
    }

    if (tree[_Index].child[1]) {
        printf("%lld  ", tree[_Index].value);
        printf("%lld \n", tree[tree[_Index].child[1]].value);
    }
    if (tree[_Index].child[0]) {
        show(tree[_Index].child[0]);
    }
    if (tree[_Index].child[1]) {
        show(tree[_Index].child[1]);
    }
    return;
}

inline ll next(ll _Value) {
    insert(_Value);

    ll ret = tree[_next_of_root()].value;
    remove(_Value);
    return ret;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    ll n = readf<ll>();
    for (ll i = 1; i <= n; ++i) {
        ll operate = readf<ll>(), x = readf<ll>();
        switch (operate) {
            //向 M 中插入一个数 x
        case 1:
            insert(x);
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif            
            break;
            //从 M 中删除一个数 x（若有多个相同的数，应只删除一个）
        case 2:
            remove(x);
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif
            break;
            //查询 M 中有多少个数比 x 小，并且将得到的答案加一。
        case 3:
            printf("%lld\n", get_Rank_By_Value(x));
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif
            break;
            //查询如果将 M 从小到大排列后，排名位于第 x 位的数。
        case 4:
            printf("%lld\n", get_Value_By_Rank(x));
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif
            break;
            //查询 M 中 x 的前驱
        case 5:
            printf("%lld\n", pre(x));
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif
            break;
            //查询 M 中 x 的后继
        case 6:
            printf("%lld\n", next(x));
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif
            break;
        }
    }


#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

#if READ
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
#else
template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != NULL) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
}
#endif

template<typename Type>
inline void writef(Type x) {
    int sta[MAX_NUM_SIZE];
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) putchar(sta[--top] + '0');  // 48 是 '0'
    return;
}



/**
 *              ,----------------,              ,---------,
 *         ,-----------------------,          ,"        ,"|
 *       ,"                      ,"|        ,"        ,"  |
 *      +-----------------------+  |      ,"        ,"    |
 *      |  .-----------------.  |  |     +---------+      |
 *      |  |                 |  |  |     | -==----'|      |
 *      |  |  希望此代码无bug|  |  |     |         |      |
 *      |  |                 |  |  |     |`---=    |      |
 *      |  |  C:\>_          |  |  |     |==== ooo |      ;
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