#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 5010
const int p = 998244353;
int n;
int a[N], b[N];

template <class T1, class T2>
inline void add(T1 &x, T2 y) {
    x += y;
    if (x >= p)
        x -= p;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= n; ++i) scanf("%d", b + i);
        for (int i = 1; i <= n; ++i) {
            int base = i;
            int res = 0;
            for (int j = 1; j <= n; ++j) {
                add(res, 1ll * base * kgcd(a[i], b[j]) % p);
                base = 1ll * base * i % p;
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
