#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdarg.h>
#include <iostream>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//����ǰ������
//�������
template< typename T >
inline T readf();

struct start {
    ll x, y;
    ll light; //����
    ll inh, outh;
    bool operator <(const start other)const {
        return x < other.x;
    }
};


std::vector< start > starts;
std::vector< ll > dis_starts; //��ɢ�����ǵ�y����
ll n, w, h, t;

class segment_tree {
private:
    std::vector< ll > _tree;
    std::vector< ll > _tag;
    inline void add_tag(ll x, ll p, ll lp, ll rp) {
        _tag[p] += x;
        _tree[p] += x;
        return;
    }

    inline void push_down(ll p, ll lp, ll rp) {
        if (_tag[p] != 0) {
            ll mid = (lp + rp) >> 1;
            add_tag(_tag[p], p * 2, lp, mid);
            add_tag(_tag[p], p * 2 + 1, mid + 1, rp);
            _tag[p] = 0;
        }
        return;
    }
public:
    

    //���캯��
    segment_tree(ll size) {
        _tree.resize(size, 0);
        _tag.resize(size + 1, 0);
    }

    inline void up_data(ll left/*Ŀ����˵�*/, ll right/*Ŀ���Ҷ˵�*/, ll x/*���ӵ�ֵ*/,
        ll p/*�����±�*/, ll lp, ll rp/*��ǰ�����±�����Ӧ�����Ҷ˵�*/) {
        if (left <= lp && right >= rp) /*�����ǰ�����Ѿ�������Ŀ������*/ {
            //tree[p] += (rp - lp + 1) * x;
            add_tag(x, p, lp, rp);
            return;
        }
        //�������������
        push_down(p, lp, rp);
        ll mid = (lp + rp) >> 1;
        if (left <= mid) {
            up_data(left, right, x, p * 2, lp, mid);
        }
        if (right > mid) {
            up_data(left, right, x, p * 2 + 1, mid + 1, rp);
        }
        _tree[p] = std::max(_tree[p * 2], _tree[p * 2 + 1]);
        return;
    }

    inline ll at(ll p) {
        return _tree[p];
    }
};

int main() {
    freopen("input.txt", "r", stdin);

    t = readf< ll >();

    while (t--) {
        n = readf< ll >(), w = readf< ll >(), h = readf< ll >();
        w--, h--; //"��"ס������
        ll head = 0;
        for (size_t i = 0; i < n; i++) {
            starts.push_back({ 
                readf< ll >(), //x
                readf< ll >(), //y
                readf< ll >(), //���� light
                });
            dis_starts.push_back(starts.back().y);
        }
        dis_starts.push_back(LLONG_MAX);

        //��ɢ��ȥ��
        std::sort(dis_starts.begin(), dis_starts.end());
        dis_starts.erase(std::unique(dis_starts.begin(), dis_starts.end()), dis_starts.end());
        
        //�߶�����ʼ��
        std::sort(starts.begin(), starts.end());
        segment_tree tree((1 + dis_starts.size() << 2) + 1);
        ll ans = 0;
        for (size_t i = 0; i < n; i++) {
            starts[i].inh = std::upper_bound(dis_starts.begin(), dis_starts.end(), starts[i].y) - dis_starts.begin() + 1;
            starts[i].outh = std::upper_bound(dis_starts.begin(), dis_starts.end(), starts[i].y + h) - dis_starts.begin() + 1;
            tree.up_data(starts[i].inh, starts[i].outh, starts[i].light, 1, 1, dis_starts.size());
            while (starts[i].x - w > starts[head].x) {
                tree.up_data(starts[head].inh, starts[head].outh, -starts[head].light, 1, 1, dis_starts.size()); 
                head++;
            }
            ans = std::max(ans, tree.at(1));
        }
        printf("%lld\n", ans);
    
        starts.clear();
        dis_starts.clear();
    }

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