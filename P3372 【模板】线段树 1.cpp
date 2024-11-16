//������ֵ
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//����ǰ������
//�������
template< typename T >
inline T readf();

std::vector< ll > tree;
std::vector< ll > vis; //��ʼ����
std::vector< ll > tag;
ll n, m;


//����ǰ������

//����
inline void buildTree(ll p/*��Ӧtree������±�*/, ll left/*��˵�*/, ll right/*�Ҷ˵�*/);

//��ѯ�����
inline ll query(ll left/*Ŀ���ѯ��˵�*/, ll right/*Ŀ���ѯ�Ҷ˵�*/, ll p/*Ŀǰ���ڱ���ѯ���������±�*/, ll lp, ll rp);

//����tag���
inline void addTag(ll p, ll lp, ll rp, ll d);

//ת��tagzת�Ƶ��ӽڵ�
inline void push_down(ll p, ll lp, ll rp);

//�����޸�
inline void updata(ll left/*������*/, ll right/*������*/,
    ll p/*��ǰ�������߶��������±�*/, ll lp/*��ǰ�������߶�������˵�*/, ll rp/*��ǰ�������߶������Ҷ˵�*/,
    ll change/*���ӵ�ֵ*/);

inline void buildTree(ll p/*��Ӧtree������±�*/, ll left/*��˵�*/, ll right/*�Ҷ˵�*/)
{
    if (left == right) {
        tree[p] = vis[left - 1];
        return;
    }
    ll mid = (left + right) >> 1;
    buildTree(p * 2, left, mid);
    buildTree(p * 2 + 1, mid + 1, right);
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
    return;
}

inline ll query(ll left/*Ŀ���ѯ��˵�*/, ll right/*Ŀ���ѯ�Ҷ˵�*/, ll p/*Ŀǰ���ڱ���ѯ���������±�*/, ll lp, ll rp)
{
    if (left <= lp && right >= rp) { //�����ǰ���鿴���߶�������պ�ȫ��λ��Ŀ���ѯ�������� ���ص�ǰ�����
        return tree[p];
    }
    push_down(p, lp, rp);
    ll ret = 0;
    ll mid = (rp + lp) >> 1;
    if (left <= mid) { //����ָ���������ȫ����Ŀ��������
        ret += query(left, right, p * 2, lp, mid);
    }
    if (mid < right) {
        ret += query(left, right, p * 2 + 1, mid + 1, rp);
    }
    return ret;
}

inline void addTag(ll p, ll lp, ll rp, ll d)
{
    tag[p] += d;
    tree[p] += d * (rp - lp + 1);
}

inline void push_down(ll p, ll lp, ll rp) //��tag���ת�Ƶ��ӽڵ�
{
    if (tag[p]) { //�����ǰ���ڱ�� 
        ll mid = (lp + rp) >> 1;
        addTag(p * 2, lp, mid, tag[p]);
        addTag(p * 2 + 1, mid + 1, rp, tag[p]);
        tag[p] = 0;
    }
}

inline void updata(ll left/*������*/, ll right/*������*/,
    ll p/*��ǰ�������߶��������±�*/, ll lp/*��ǰ�������߶�������˵�*/, ll rp/*��ǰ�������߶������Ҷ˵�*/,
    ll change/*���ӵ�ֵ*/)
{
    if (left <= lp && right >= rp) { //Ŀ���޸�����  ��ȫ���ǵ�ǰ����
        addTag(p, lp, rp, change); //����tag �������ݹ�
        return;
    }
    //���������ȫ����
    push_down(p, lp, rp);  //���ӽڵ�ת��tag���
    ll mid = (lp + rp) >> 1;
    if (left <= mid) {
        updata(left, right, p * 2, lp, mid, change);
    }
    if (mid < right) {
        updata(left, right, p * 2 + 1, mid + 1, rp, change);
    }
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
    return;
}


int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >();

    vis.resize(n);
    for (ll& i : vis) {
        i = readf< ll >();
    }

    tree.resize((n << 2) + 1, 0);
    tag.resize((n << 2) + 1, 0);

    buildTree(1, 1, n);

    for (size_t i = 0; i < m; i++) {
        ll q = readf< ll >(), left, right, change;
        switch (q) {
        case 1:
            left = readf< ll >(), right = readf< ll >(), change = readf< ll >();
            updata(left, right, 1, 1, n, change);
            break;
        case 2:
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