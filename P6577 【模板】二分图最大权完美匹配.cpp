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

std::vector< std::vector< ll > >  graph;
std::vector< ll >  object; // object[i]Ϊ�Ҳ���i��ƥ����󲿵�
std::vector< ll > ltag, rtag;// �󲿵㶥�� left-tag �Ҳ��㶥�� right-tag
std::vector< bool > rb; // right-bool ���Ҳ���i�Ƿ��Ѿ�����
ll n, m;



int main() {
    freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >();

    graph.resize(n, std::vector< ll >(n, 0)); //graph[i][j]Ϊ�󲿵�i���Ҳ���j֮���Ȩֵ
    for (size_t i = 0; i < m; i++){
        ll u1 = readf< ll >(), v2 = readf< ll >(), w = readf< ll >();
        graph[u1 - 1][v2 - 1] = w;
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