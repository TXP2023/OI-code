#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//����ǰ������
//�������
template< typename T >
inline T readf();

template< typename T >
inline void inputf(T* p);

std::pair< short int, short int > match[]{
    {0, 6},
    {1, 2},
    {2, 5},
    {4, 4},
    {6, 6},
    {7, 3},
    {8, 7}
};
ll n, t, ans;

inline ll fast_pow(ll base, ll index) {
    ll result = 1;   //���ڴ洢���۳��뷵�����ս��������Ҫ�洢�۳�����Ҫ��ʼ��Ϊ1
    while (index > 0)           //ָ������0˵��ָ���Ķ�����λ��û�б������������
    {
        if (index & 1)          //ָ���ĵ�ǰ���������λҲ������ĩβ��λ�Ƿ���λҲ����1��ʱ��
            //����1001�ĵ�ǰ����λ����1�� 100*1* �Ǻ��е�1���ǵ�ǰ����ʹ�õ�λ
            result *= base;     //�۳˵�ǰ��洢
        base *= base;           //������һ������統ǰ��n^2�Ļ�������һ��n^2��ֵ
        //n^4 = n^2 * n^2;
        index >>= 1;            //ָ��λ���ƣ�Ϊ��һ��������׼��
        //һ�ε����ƽ�����һ��λ����1011(2)һ�����ƺ���101(2)
    }
    return result;              //�������ս��
}

inline void minMatch(std::vector< short > v) {
    ll sum = 0;
    std::sort(v.begin(), v.end());
    if (v.front() != 0) {
        
        for (ll i = v.size() - 1; i >= 0; i--) {
            sum += v[i] * fast_pow(10, v.size() - i - 1);
        }
    }
    else {
        bool b = false;
        for (size_t i = 0; i < v.size(); i++) {
            if (v[i] != 0) {
                b = true;
                std::swap(v[0], v[i]);
                break;
            }
        }
        if (!b) {
            return;
        }
        else {
            for (ll i = v.size() - 1; i >= 0; i--) {
                sum += v[i] * fast_pow(10, v.size() - i - 1);
            }
        }
    }
    if (ans == -1) {
        ans = sum;
    }
    else {
        ans = std::min(ans, sum);
    }
    return;
}

inline void dfs(ll Stick, std::vector< short > v) {
    for (std::pair< short int, short int > i : match) {
        if (Stick - i.second == 0) {
            v.push_back(i.first);
            minMatch(v);
            v.pop_back();
        }
        else {
            if (Stick - i.second > 0) {
                v.push_back(i.first);
                dfs(Stick - i.second, v);
                v.pop_back();
            }
        }
    }
    
}

int main() {
    freopen("input.txt", "r", stdin);

    inputf(&t);
    while (t--) {
        inputf(&n);
        ans = -1;
        dfs(n, {});
        printf("%lld\n", ans);
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

template< typename T >
inline void inputf(T* p) {
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
    //return sgn ? -ret : ret;
    *p = (sgn) ? -ret : ret;
    return;
#endif
}