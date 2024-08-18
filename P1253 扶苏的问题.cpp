#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>

#define _PUSH_DOWN_ true

typedef int64_t ll;
typedef uint64_t unill;

//����ǰ������
//�������
template< typename T >
inline T readf();

#define size 100005

ll vis[size], tree[size << 2];
std::pair< ll, ll> tag[size << 2];
std::pair< bool, bool > tagbool[size << 2];

inline void buildTree(ll p, ll lp, ll rp)
{
    if (lp == rp) {
        tree[p] = vis[lp - 1];
        return;
    }
    ll mid = (lp + rp) >> 1;
    buildTree(p * 2, lp, mid);
    buildTree(p * 2 + 1, mid + 1, rp);
    tree[p] = std::max(tree[p * 2], tree[p * 2 + 1]);
    return;
}

inline void addTag(ll p, ll change) //������ͳһ����Ϊͬһ����
{
    tag[p].first += change;
    tree[p] += change;
    tagbool[p].first = true;
}

inline void reviseTag(ll p, ll change)
{
    tag[p].second = change;
    tree[p] = change;
    tagbool[p].second = true;
}

#if _PUSH_DOWN_
    
inline void push_down(ll p)
{
    if (tagbool[p].first) {
        addTag(p * 2, tag[p].first);
        addTag(p * 2 + 1, tag[p].first);        
        tag[p].first = 0;
        tagbool [p] .first = false;
    }
    if (tagbool[p].second) {
        reviseTag(p * 2, tag[p].second);
        reviseTag(p * 2 + 1, tag[p].second);
        tag[p].second = 0;
        tagbool[p].second = false;
    }
}

#else
inline void push_down_first(ll p)
{
    if (tagbool[p].first) {
        addTag(p * 2, tag[p].first);
        addTag(p * 2 + 1, tag[p].first);
        tagbool[p].first = false;
    }
    return;
}

inline void push_down_second(ll p)
{
    if (tagbool[p].second) {
        reviseTag(p * 2, tag[p].second);
        reviseTag(p * 2 + 1, tag[p].second);
        tagbool[p].second = false;
    }
    return;
}

#endif

inline void updata_revise(ll left/*������*/, ll right/*������*/,
    ll p/*��ǰ�������߶��������±�*/, ll lp/*��ǰ�������߶�������˵�*/, ll rp/*��ǰ�������߶������Ҷ˵�*/,
    ll change/*�޸ĵ�ֵ*/)
{
    if (left <= lp && right >= rp) { //Ŀ���޸�����  ��ȫ���ǵ�ǰ����
        reviseTag(p, change); //����tag �������ݹ�
        return;
    }
    //���������ȫ����

#if _PUSH_DOWN_
    push_down(p);
#else
    push_down_second(p);  //���ӽڵ�ת��tag���
    push_down_first(p); //
#endif
    ll mid = (lp + rp) >> 1;
    if (left <= mid) {
        updata_revise(left, right, p * 2, lp, mid, change);
    }
    if (mid < right) {
        updata_revise(left, right, p * 2 + 1, mid + 1, rp, change);
    }
    tree[p] = std::max(tree[p * 2], tree[p * 2 + 1]);
    return;
}

inline void updata_add(ll left/*������*/, ll right/*������*/,
    ll p/*��ǰ�������߶��������±�*/, ll lp/*��ǰ�������߶�������˵�*/, ll rp/*��ǰ�������߶������Ҷ˵�*/,
    ll change/*�޸ĵ�ֵ*/)
{
    if (left <= lp && right >= rp) { //Ŀ���޸�����  ��ȫ���ǵ�ǰ����
        addTag(p, change); //����tag �������ݹ�
        return;
    }
    //���������ȫ����
#if _PUSH_DOWN_
    push_down(p);
#else
    push_down_second(p);  //���ӽڵ�ת��tag���
    push_down_first(p); //
#endif
    ll mid = (lp + rp) >> 1;
    if (left <= mid) {
        updata_add(left, right, p * 2, lp, mid, change);
    }
    if (mid < right) {
        updata_add(left, right, p * 2 + 1, mid + 1, rp, change);
    }
    tree[p] = std::max(tree[p * 2], tree[p * 2 + 1]);
    return;
}

inline ll query(ll left/*Ŀ���ѯ��˵�*/, ll right/*Ŀ���ѯ�Ҷ˵�*/, ll p/*Ŀǰ���ڱ���ѯ���������±�*/, ll lp, ll rp)
{
    if (left <= lp && right >= rp) { //�����ǰ���鿴���߶�������պ�ȫ��λ��Ŀ���ѯ�������� ���ص�ǰ������ֵ
        return tree[p];
    }
#if _PUSH_DOWN_
    push_down(p);
#else
    push_down_second(p);  //���ӽڵ�ת��tag���
    push_down_first(p); //
#endif
    ll ret = LLONG_MIN;
    ll mid = (rp + lp) >> 1;
    if (left <= mid) { //����ָ���������ȫ����Ŀ��������
        ret = query(left, right, p * 2, lp, mid);
    }
    if (mid < right) {
        ret = std::max(query(left, right, p * 2 + 1, mid + 1, rp), ret);
    }
    return ret;
}

int main()
{
    freopen(".in", "r", stdin);

    const ll n = readf< ll >(), q = readf< ll >();

    for (size_t i = 0; i < n; i++) {
        vis[i] = readf< ll >();
        //scanf("%lld", &vis[i]);
    }

    buildTree(1, 1, n);

    std::fill(tagbool, tagbool + (n << 2) + 1, std::pair< bool, bool >{false, false});

    for (int i = 0; i < q; i++) {
        ll left, right, x;
        switch (readf< ll >()) {
        case 1:
            //�޸�Ϊx
            left = readf< ll >(), right = readf< ll >(), x = readf< ll >();
            updata_revise(left, right, 1, 1, n, x);
            break;
        case 2:
            //����x
            left = readf< ll >(), right = readf< ll >(), x = readf< ll >();
            updata_add(left, right, 1, 1, n, x);
            break;
        case 3:
            left = readf< ll >(), right = readf< ll >();
            printf("%lld\n", query(left, right, 1, 1, n));
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
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}