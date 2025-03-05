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
#define MAXN          (long long)(1e5 + 5)

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
    short int child[2]; //
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
    tree[u].child[chk] = tree[u].child[chk ^ 1];
    //x ���Ҷ��ӣ���� x ���Ҷ��ӵĻ����ĸ���ָ�� y
    if (tree[_Index].child[chk ^ 1]) {
        tree[tree[_Index].child[chk ^ 1]].father = u;
    }
    tree[_Index].child[chk ^ 1] = u;
    tree[u].father = _Index;
    //���ԭ���� y ���и��� z����ô�� z ��ĳ�����ӣ�ԭ�� y ���ڵĶ���λ�ã�ָ�� x���� x �ĸ���ָ�� z��
    tree[_Index].father = v;
    if (v){
        tree[v].child[get_child(u)] = _Index;
    }
    update_size(_Index);
    update_size(u);
    return;
}

//Splay ����
void Splay(ll _Index) {
    //Splay �����涨��ÿ����һ���ڵ� x ��Ҫǿ�ƽ�����ת�����ڵ㡣
    //
    for (ll i = tree[_Index].father; i = tree[_Index].father, i ; rotate(i)) {
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
        tree[++node_num].father = 0;
        tree[node_num].cnt++;
        tree[node_num].value = _Value;
        root = node_num;
        update_size(node_num);
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
            tree[node_num].father = father;
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
        if (tree[_Index].child[0] && tree[_Index].size > _Rank) {
            _Index = tree[_Index].child[0];
        }
        else {
            _Rank -= tree[_Index].size + tree[_Index].cnt;
            if (_Rank <= 0) {
                Splay(_Index);
                return tree[_Index].value;
            }
            _Index = tree[_Index].child[1];
        }
    }
    return;
}

inline void remove(ll _Value) {
    //���Ƚ� x ��ת������λ�á�
    get_Rank_By_Value(_Value);
    tree[root].cnt--;
    return;
}

inline ll precursor(ll _Value) {
    insert(_Value);
    ll _Index = tree[root].child[0];
    if (_Index) {
        while (tree[_Index].child[1]) {
            _Index = tree[_Index].child[1];
        }
    }
    ll ret = tree[_Index].value;
    
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    printf("%lld\n", MAXN);


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