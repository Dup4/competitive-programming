#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 105
const ll p = (ll)1e9 + 7;
int n, m, a[N], v[N];
ll f[N][N][N][N];
ll inv[N];

int mpgcd[N][N];
int gcd(int a, int b) {
    if (mpgcd[a][b] != -1) {
        return mpgcd[a][b];
    }
    return b ? gcd(b, a % b) : a;
}

int main() {
    memset(mpgcd, -1, sizeof mpgcd);
    inv[0] = 1;
    for (int i = 1; i <= 100; ++i) {
        inv[i] = inv[p % i] * (p - p / i) % p;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d", v + i);
        }
        memset(f, 0, sizeof f);
    }
    return 0;
}
