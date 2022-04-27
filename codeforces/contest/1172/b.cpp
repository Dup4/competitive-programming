#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define ll long long
const ll p = 998244353;
int n;
vector<vector<int> > G;
ll fac[N], f[N], g[N], res;

ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * base % p;
        }
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return qmod(x, p - 2);
}

void add(ll &x, ll y) {
    x += y;
    if (x >= p) {
        x -= p;
    }
}

int sze(int u) {
    return (int)G[u].size();
}

void DFS1(int u, int fa) {
    if (u == 1) {
        f[u] = fac[sze(u)];
    } else {
        f[u] = fac[sze(u) - 1];
    }
    for (auto v : G[u])
        if (v != fa) {
            DFS1(v, u);
            f[u] = f[u] * f[v] % p;
            if (sze(v) > 1) {
                f[u] = f[u] * 2 % p;
            }
        }
}

void DFS2(int u, int fa) {
    if (u == 1) {
        g[u] = 1;
        add(res, f[u]);
    } else {
        g[u] = g[fa] * 2 * f[fa] % p * inv(f[u]) % p;
        if (sze(u) > 1) {
            g[u] = g[u] * inv(2) % p;
        }
        add(res, g[u] * f[u] % p * inv(sze(u) - 1) % p * fac[sze(u)] % p);
    }
    for (auto v : G[u])
        if (v != fa) {
            DFS2(v, u);
        }
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) {
        fac[i] = fac[i - 1] * i % p;
    }
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        res = 0;
        DFS1(1, 1);
        DFS2(1, 1);
        printf("%lld\n", res);
    }
    return 0;
}
