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

//�����������
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = nullptr);
#endif

//�����������
template<typename Type>
inline void writef(Type x);


struct Splay_data {
    ll child[2]; //
    ll father; //���׽ڵ�
    ll value; //�ڵ�Ȩֵ
    ll size; //������С
    ll cnt;//�˽ڵ�����ʾ��Ȩֵ�ĳ��ִ���

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
ll root, node_num;//���ڵ���  �ڵ����

//�ڸı�ڵ�λ�ú󣬽��ڵ� _P �� size ���¡�
void update_size(ll _Index) {
    tree[_Index].size = tree[tree[_Index].child[0]].size + tree[tree[_Index].child[1]].size + tree[_Index].cnt;
    return;
}

//�жϽڵ� x �Ǹ��׽ڵ������ӻ����Ҷ��ӡ� ��false ��true
bool get_child(ll _Index) {
    return _Index == tree[tree[_Index].father].child[1];
}

//���ٽڵ�_Index
void clear(ll _Index) {
    tree[_Index] = Splay_data();
    return;
}

//����_Index���丸�ڵ���ת
void rotate(ll _Index) {
    //��ת��Ҫ��֤:
    //  ���� Splay ������������䣨�����ƻ���������������ʣ���
    //  ��Ӱ��Ľڵ�ά������Ϣ��Ȼ��ȷ��Ч��
    //  root ����ָ����ת��ĸ��ڵ㡣
    // 
    // ���岽��
    // 1.�� y �������ָ�� x ���Ҷ��ӣ��� x ���Ҷ��ӣ���� x ���Ҷ��ӵĻ����ĸ���ָ�� y
    // 2.�� x ���Ҷ���ָ�� y���� y �ĸ���ָ�� x
    // 3.���ԭ���� y ���и��� z����ô�� z ��ĳ�����ӣ�ԭ�� y ���ڵĶ���λ�ã�ָ�� x���� x �ĸ���ָ�� z��
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
    //�� y �������ָ�� x ���Ҷ���
    tree[u].child[chk] = tree[_Index].child[chk ^ 1];
    //x ���Ҷ��ӣ���� x ���Ҷ��ӵĻ����ĸ���ָ�� y
    if (tree[_Index].child[chk ^ 1]) {
        tree[tree[_Index].child[chk ^ 1]].father = u;
    }
    tree[_Index].child[chk ^ 1] = u;
    tree[u].father = _Index;
    //���ԭ���� y ���и��� z����ô�� z ��ĳ�����ӣ�ԭ�� y ���ڵĶ���λ�ã�ָ�� x���� x �ĸ���ָ�� z��
    tree[_Index].father = v;
    if (v) {
        //tree[v].child[get_child(u)] = _Index;
        tree[v].child[u == tree[v].child[1]] = _Index;
    }
    update_size(u);
    update_size(_Index);
    return;
}

//Splay ����
void Splay(ll _Index) {
    //Splay �����涨��ÿ����һ���ڵ� x ��Ҫǿ�ƽ�����ת�����ڵ㡣
    //
    for (ll i = tree[_Index].father; i = tree[_Index].father, i; rotate(_Index)) {
        if (tree[i].father) {
            rotate(get_child(_Index) == get_child(i) ? i : _Index);
        }
    }
    root = _Index;
    return;
}

//����ֵ _Value
inline void insert(ll _Value) {
    /*
    ���������һ���Ƚϸ��ӵĹ��̣����岽�����£���������ֵΪ k����
    ��������ˣ���ֱ�Ӳ�������˳���
    �����ǰ�ڵ��Ȩֵ���� k �����ӵ�ǰ�ڵ�Ĵ�С�����½ڵ�͸��׵���Ϣ������ǰ�ڵ���� Splay ������
    /�����ն�������������������ң��ҵ��սڵ�Ͳ��뼴�ɣ��벻Ҫ���� Splay ��������
    */

    //����ʵ������
    //��������ˣ���ֱ�Ӳ�������˳���
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
        _Index = tree[_Index].child[tree[_Index].value < _Value/*�����ǰ�ڵ�ֵС�ڲ���ڵ�ֵ ���ʽֵΪ1 ��Ӧ�����ӽڵ� ��֮*/];
        //û�е��ֵΪ_Value����ô��Ҫ����ڵ�
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

//��ѯ _Value ������
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

//��ѯ���� rank ����
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

//��ѯ���ڵ��ǰ�����±�
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


//ɾ������
inline void remove(ll _Value) {
    //���Ƚ� x ��ת������λ�á�
    get_Rank_By_Value(_Value);
    if (tree[root].cnt > 1) {
        tree[root].cnt--;
        update_size(root);
        return;
    }

    //xû���ӽڵ�
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
            //�� M �в���һ���� x
        case 1:
            insert(x);
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif            
            break;
            //�� M ��ɾ��һ���� x�����ж����ͬ������Ӧֻɾ��һ����
        case 2:
            remove(x);
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif
            break;
            //��ѯ M ���ж��ٸ����� x С�����ҽ��õ��Ĵ𰸼�һ��
        case 3:
            printf("%lld\n", get_Rank_By_Value(x));
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif
            break;
            //��ѯ����� M ��С�������к�����λ�ڵ� x λ������
        case 4:
            printf("%lld\n", get_Value_By_Rank(x));
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif
            break;
            //��ѯ M �� x ��ǰ��
        case 5:
            printf("%lld\n", pre(x));
#if DEBUG
            printf("%lld now is  root value is: %lld\n", i, tree[root].value);
            show(root);
#endif
            break;
            //��ѯ M �� x �ĺ��
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
    while (top) putchar(sta[--top] + '0');  // 48 �� '0'
    return;
}



/**
 *              ,----------------,              ,---------,
 *         ,-----------------------,          ,"        ,"|
 *       ,"                      ,"|        ,"        ,"  |
 *      +-----------------------+  |      ,"        ,"    |
 *      |  .-----------------.  |  |     +---------+      |
 *      |  |                 |  |  |     | -==----'|      |
 *      |  |  ϣ���˴�����bug|  |  |     |         |      |
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