#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 510
const ll p = 998244353;
int n, m, a[N];
ll f[N][N];

void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}

ll dp(int l, int r) {
    if (l > r)
        return 1;
    if (f[l][r] != -1)
        return f[l][r];
    if (l == r)
        return f[l][r] = 1;
    f[l][r] = 0;
    int pos = l;
    for (int i = l + 1; i <= r; ++i) {
        if (a[i] < a[pos])
            pos = i;
    }
    ll L = dp(l, pos - 1), R = dp(pos + 1, r);
    for (int i = l; i < pos; ++i) {
        add(L, dp(l, i) * dp(i + 1, pos - 1) % p);
    }
    for (int i = pos + 1; i <= r; ++i) {
        add(R, dp(pos + 1, i) * dp(i + 1, r) % p);
    }
    return f[l][r] = L * R % p;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(f, -1, sizeof f);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        printf("%lld\n", dp(1, n));
    }
    return 0;
}
