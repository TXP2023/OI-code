#if true



#else

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>

typedef uint64_t ll;
typedef uint64_t unill;

//�������
template< typename T >
inline T readf();

//����Э��
//�涨tag��first��ԱΪ���Ӳ�����second��ԱΪ�˷�����

std::vector< ll > vis;
std::vector< ll > tree;
std::vector< std::pair< ll, ll > > tag;
std::vector< std::pair< bool, bool > > tagbool;
ll n, q, m;

//����ǰ������
inline void init(); //��ʼ��

inline void BuildTree(ll p, ll rp, ll lp); //������ʼ��

inline void AddTag_Add(ll p, ll lp, ll rp, ll x);

inline void AddTag_Multiply(ll p, ll lp, ll rp, ll x);

inline void changeAdd(ll left, ll right, ll p, ll lp, ll rp, ll x); //��left~right����������x

inline void Push_down(ll p, ll lp, ll rp);

inline ll query(ll left, ll right, ll p, ll lp, ll rp);


//������
inline void init()
{
    tree.resize((n << 2) + 1, 0);
    tag.resize((n << 2) + 1, { 0, 1 });
    tagbool.resize((n << 2) + 1, { 0, 0 });
    return;
}

inline void BuildTree(ll p, ll lp, ll rp)
{
    if (lp == rp){
        tree[p] = vis[lp - 1];
        return;
    }
    ll mid = (lp + rp) >> 1;
    BuildTree(p * 2, lp, mid);
    BuildTree(p * 2 + 1, mid + 1, rp);
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
    return;
}

inline void changeAdd(ll left, ll right, ll p, ll lp, ll rp, ll x)
{
    if (left <= lp && right >= rp){
        AddTag_Add(p, lp, rp, x);
        return;
    }
    Push_down(p, lp, rp);
    ll mid = (lp + rp) >> 1;
    if (left <= mid){
        changeAdd(left, right, p * 2, lp, mid, x);
    }
    if (right > mid){
        changeAdd(left, right, p * 2 + 1, mid + 1, rp, x);
    }
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
    return;
}

inline void AddTag_Add(ll p, ll lp, ll rp, ll x)
{
    if (p >= (n << 2) + 1) {
        return;
    }
    if (tagbool[p].second == true) { // �����ǰ���ڳ˷�����tag���
        Push_down(p, lp, rp);
        tagbool[p].second = false;
        tag[p].second = 1;
    }
    tag[p].first += x;
    tagbool[p].first = true;
    tree[p] += (rp - lp + 1) * x;
    return;
}

inline void AddTag_Multiply(ll p, ll lp, ll rp, ll x)
{
    if (p >= (n << 2) + 1) {
        return;
    }
    if (tagbool[p].first) { // �����ǰ���ڼӷ�����tag���
        Push_down(p, lp, rp);
        tagbool[p].first = false;
        tag[p].first = 0;
    }
    tag[p].second *= x;
    tagbool[p].second = true;
    tree[p] *= x;
    return;
}

inline void changeMultiply(ll left, ll right, ll p, ll lp, ll rp, ll x)
{
    if (left <= lp && right >= rp){
        AddTag_Multiply(p, lp, rp, x);
        return;
    }
    Push_down(p, lp, rp);
    ll mid = (lp + rp) >> 1;
    if (left <= mid){
        changeMultiply(left, right, p * 2, lp, mid, x);
    }
    if (right > mid){
        changeMultiply(left, right, p * 2 + 1, mid + 1, rp, x);
    }
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
    return;
}

inline void Push_down(ll p, ll lp, ll rp) //��push_down�����У� Ҫע����Ҷ�ӽڵ��Ͻ���push_down����Ҫע��Խ�����⣬����� �δ���RE
{
    ll mid = (lp + rp) >> 1;
    if (tagbool[p].first){
        AddTag_Add(p * 2, lp, mid, tag[p].first);
        AddTag_Add(p * 2 + 1, mid + 1, rp, tag[p].first);
        tagbool[p].first = false;
        tag[p].first = 0;
    }
    if (tagbool[p].second){
        AddTag_Multiply(p * 2, lp, mid, tag[p].second);
        AddTag_Multiply(p * 2 + 1, mid + 1, rp, tag[p].second);
        tagbool[p].second = false;
        tag[p].second = 1;
    }
    return;
}

inline ll query(ll left, ll right, ll p, ll lp, ll rp)
{
    if (lp == rp){
        return tree[p] % m; //?
    }
    Push_down(p, lp, rp);
    ll sum = 0;
    ll mid = (lp + rp) >> 1;
    if (mid >= left){
        sum += query(left, right, p * 2, lp, mid);
    }
    if (mid < right){
        sum += query(left, right, p * 2 + 1, mid + 1, rp);
    }
    return sum % m;
}

int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >(), q = readf< ll >(), m = readf< ll >();

    vis.resize(n);
    for (ll& i : vis){
        i = readf< ll >();
    }

    init();
    BuildTree(1, 1, n);

    for (size_t i = 0; i < q; i++){
        ll cnt = readf< int >();
        ll x = readf< ll >(), y = readf< ll >(), k;
        switch (cnt){
        case 1: //x~y����k
            k = readf< ll >();
            changeMultiply(x, y, 1, 1, n, k);
            break;

        case 2: //x~y����k
            k = readf< ll >();
            changeAdd(x, y, 1, 1, n, k);
            break;
        case 3:
            printf("%lld\n", query(x, y, 1, 1, n));
            break;
        }
    }

    return 0;
}

template< typename T >
inline T readf()
{
#if false
    T sum = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0') ch = getchar();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = getchar();
    return sum;
#else
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch))
    {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}

#endif