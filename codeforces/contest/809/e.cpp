#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 2e5 + 10;
const ll mod = 1e9 + 7;
int n, ans, a[N], b[N], pri[N], check[N], mu[N], phi[N], fa[N], deep[N], son[N], sze[N], top[N], in[N], out[N], sta[N],
        p[N << 1], vis[N], f[N], g[N], F[N];
vector<vector<int>> G;
inline void add(int &x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}
ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
void sieve() {
    memset(check, 0, sizeof check);
    *pri = 0;
    mu[1] = phi[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (1ll * i * pri[j] >= N)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                mu[i * pri[j]] = 0;
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                mu[i * pri[j]] = -mu[i];
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
            }
        }
    }
}
void DFS(int u) {
    son[u] = 0;
    sze[u] = 1;
    for (auto &v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            deep[v] = deep[u] + 1;
            DFS(v);
            sze[u] += sze[v];
            if (!son[u] || sze[v] > sze[son[u]])
                son[u] = v;
        }
}
void gettop(int u, int tp) {
    top[u] = tp;
    in[u] = ++*in;
    if (son[u])
        gettop(son[u], tp);
    for (auto &v : G[u])
        if (v != son[u] && v != fa[u])
            gettop(v, v);
    out[u] = *in;
}
int querylca(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return u;
}
void dp(int u, int fa) {
    f[u] = 0;
    if (vis[u])
        f[u] = phi[a[u]];
    add(ans, mod - 1ll * f[u] * f[u] % mod * deep[u] % mod);
    for (auto &v : G[u])
        if (v != fa) {
            dp(v, u);
            add(ans, mod - 2ll * f[u] * f[v] % mod * deep[u] % mod);
            add(f[u], f[v]);
        }
}

int main() {
    sieve();
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), b[a[i]] = i;
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        deep[1] = 0;
        fa[1] = 1;
        DFS(1);
        gettop(1, 1);
        G.clear();
        G.resize(n + 1);
        memset(vis, 0, sizeof vis);
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        memset(F, 0, sizeof G);
        ans = 0;
        for (int T = 1; T <= n; ++T) {
            int s1 = 0, s2 = 0;
            *sta = 0;
            *p = n / T;
            for (int i = 1; i <= *p; ++i) p[i] = b[i * T];
            for (int i = 1; i <= *p; ++i) {
                add(s1, phi[a[p[i]]]);
                add(s2, 1ll * phi[a[p[i]]] * deep[p[i]] % mod);
                vis[p[i]] = 1;
            }
            sort(p + 1, p + 1 + *p, [&](int x, int y) {
                return in[x] < in[y];
            });
            for (int i = *p; i > 1; --i) {
                p[++*p] = querylca(p[i], p[i - 1]);
            }
            sort(p + 1, p + 1 + *p, [&](int x, int y) {
                return in[x] < in[y];
            });
            *p = unique(p + 1, p + 1 + *p) - p - 1;
            for (int i = 1; i <= *p; ++i) {
                while (*sta && out[sta[*sta]] < in[p[i]]) --*sta;
                if (*sta)
                    G[sta[*sta]].push_back(p[i]);
                sta[++*sta] = p[i];
            }
            dp(p[1], p[1]);
            add(ans, ans);
            add(ans, 2ll * s1 * s2 % mod);
            for (int i = 1; i <= *p; ++i) vis[p[i]] = 0, G[p[i]].clear();
            F[T] = ans;
            ans = 0;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = i; j <= n; j += i)
                if (mu[j / i])
                    add(g[i], (1ll * mu[j / i] * F[j] % mod + mod) % mod);
        for (int i = 1; i <= n; ++i) add(ans, 1ll * i * qpow(phi[i], mod - 2) % mod * g[i] % mod);
        ans = 1ll * ans * qpow(n, mod - 2) % mod * qpow(n - 1, mod - 2) % mod;
        printf("%d\n", ans);
    }
    return 0;
}
