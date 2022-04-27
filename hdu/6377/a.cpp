#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1010
const ll p = 998244353;
int n, D;
// f[n][i]表示在第2n个位置，有i对情侣相邻的方案数
ll f[N][N];
void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}

int main() {
    memset(f, 0, sizeof f);
    f[1][1] = 2;
    for (int i = 2; i <= 1000; ++i) {
        for (int j = 0; j <= i; ++j) {
            //情侣看成一个点插入
            if (j)
                add(f[i][j], f[i - 1][j - 1] * (2 * i - 1 - (j - 1)) % p * 2 % p);
            add(f[i][j], f[i - 1][j] * j % p * 2 % p);
            //情侣看成两个点插入
            add(f[i][j], f[i - 1][j] * (2 * i - 1 - j) % p * (2 * i - 1 - j - 1) % p);
            if (j < i - 1)
                add(f[i][j], f[i - 1][j + 1] * (j + 1) % p * (2 * i - 1 - (j + 1)) % p * 2 % p);
            if (j < i - 2)
                add(f[i][j], f[i - 1][j + 2] * (j + 2) % p * (j + 1) % p);
        }
    }
    while (scanf("%d%d", &n, &D) != EOF) {
        ll DD = 1;
        ll res = 0;
        for (int i = 0; i <= n; ++i) {
            add(res, DD * f[n][i] % p);
            DD = DD * D % p;
        }
        printf("%lld\n", res);
    }
    return 0;
}
