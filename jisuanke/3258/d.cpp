#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
const int N = 1e5 + 10;
const ll p = 998244353;
int n, K;
vector<vector<pii>> G;
ll C[20][20];
ll res;

ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % p;
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}
int fa[N];
ll f[N][15], g[N][15], h[15];
void DFS(int u) {
    memset(f[u], 0, sizeof f[u]);
    f[u][0] = 1;
    for (auto it : G[u]) {
        int v = it.fi, w = it.se;
        if (v == fa[u])
            continue;
        fa[v] = u;
        DFS(v);
        h[0] = 1;
        for (int i = 1; i <= K; ++i) h[i] = h[i - 1] * w % p;
        for (int i = K; i >= 0; --i) {
            ll tmp = 0;
            for (int j = 0; j <= i; ++j) {
                add(tmp, C[i][j] * h[i - j] % p * f[v][j] % p);
            }
            add(f[u][i], tmp);
        }
    }
    add(res, f[u][K]);
}

void DFS2(int u) {
    for (auto it : G[u]) {
        int v = it.fi, w = it.se;
        if (v == fa[u])
            continue;
        memset(g[v], 0, sizeof g[v]);
        h[0] = 1;
        for (int i = 1; i <= K; ++i) {
            h[i] = h[i - 1] * w % p;
        }
        ll hh[15];
        memset(hh, 0, sizeof hh);
        for (int i = K; i >= 0; --i) {
            ll tmp = 0;
            for (int j = 0; j <= i; ++j) {
                add(tmp, C[i][j] * h[i - j] % p * f[v][j] % p);
            }
            add(hh[i], tmp);
        }
        for (int i = K; i >= 0; --i) {
            ll tmp = 0;
            for (int j = 0; j <= i; ++j) {
                ll t = g[u][j] + f[u][j] - hh[j];
                t = (t + p) % p;
                add(tmp, C[i][j] * h[i - j] % p * t % p);
            }
            add(g[v][i], tmp);
        }
        add(res, g[v][K]);
        DFS2(v);
    }
}

int main() {
    for (int i = 0; i < 20; ++i) C[i][0] = C[i][i] = 1;
    for (int i = 1; i < 20; ++i)
        for (int j = 1; j < i; ++j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
    while (scanf("%d%d", &n, &K) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G[u].push_back(pii(v, w));
            G[v].push_back(pii(u, w));
        }
        res = 0;
        DFS(1);
        //	for (int i = 0; i <= K; ++i) {
        //		printf("%lld %lld\n", f[1][i], f[2][i]);
        //	}
        memset(g[1], 0, sizeof g[1]);
        DFS2(1);
        //    for (int i = 1; i <= n; ++i)
        //		printf("%d %lld\n", i, g[i][K]);
        ll inv = qmod(n, p - 2);
        res = res * inv % p * inv % p;
        printf("%lld\n", res);
    }
    return 0;
}
