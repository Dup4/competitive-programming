#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
const ll p = 1e9 + 7;
int n, k, q;
vector<vector<int>> G;
int fa[N], is_S[N], pre_S[N], cnt[N], in[N], ord[N], cnt_in;
ll inv[N * 10], P[N], f[N], g[N];
#define erp() for (int _ = 1, i = ord[1]; _ <= n; ++_, i = ord[_])

void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}

void BFS() {
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in[u] = ++cnt_in;
        for (auto v : G[u]) {
            pre_S[v] = is_S[u] ? u : pre_S[u];
            q.push(v);
        }
    }
}

int main() {
    inv[1] = 1;
    for (int i = 2; i < N * 10; ++i) {
        inv[i] = 1ll * inv[p % i] * (p - p / i) % p;
    }
    while (scanf("%d%d%d", &n, &k, &q) != EOF) {
        cnt_in = 0;
        G.clear();
        G.resize(n + 1);
        memset(is_S, 0, sizeof is_S);
        memset(cnt, 0, sizeof cnt);
        fa[1] = 0;
        for (int i = 2; i <= n; ++i) {
            scanf("%d", fa + i);
            ++cnt[fa[i]];
            G[fa[i]].push_back(i);
        }
        for (int i = 2, X, Y; i <= n; ++i) {
            scanf("%d%d", &X, &Y);
            P[i] = 1ll * X * inv[Y] % p;
        }
        for (int i = 1, x; i <= q; ++i) {
            scanf("%d", &x);
            is_S[x] = 1;
        }
        BFS();
        for (int i = 1; i <= n; ++i) ord[i] = i;
        sort(ord + 1, ord + 1 + n, [&](int x, int y) {
            return in[x] > in[y];
        });
        //单独处理0的贡献
        for (int i = 1; i <= n; ++i) f[i] = g[i] = 0;
        erp() {
            if (cnt[i] == 0) {
                f[i] = P[i];
            } else {
                f[i] = 1ll * P[i] * f[i] % p * inv[cnt[i]] % p;
            }
            add(f[fa[i]], f[i]);
        }
        erp() {
            if (cnt[i] == 0) {
                g[i] = 1;
            } else {
                g[i] = 1ll * g[i] * inv[cnt[i]] % p;
            }
            add(g[fa[i]], f[i]);
        }
        for (int j = 1; j <= k; ++j) {
            for (int i = 1; i <= n; ++i) f[i] = 0;
            erp() {
                if (cnt[i] == 0) {
                    f[i] = (1ll * P[i] + 1ll * (1 - P[i] + p) % p * g[pre_S[i]] % p) % p;
                } else {
                    f[i] = 1ll * P[i] * f[i] % p * inv[cnt[i]] % p;
                    add(f[i], 1ll * (1 - P[i] + p) % p * g[pre_S[i]] % p);
                }
                add(f[fa[i]], f[i]);
            }
            for (int i = 1; i <= n; ++i) g[i] = 0;
            erp() {
                if (cnt[i] == 0) {
                    g[i] = 1;
                } else {
                    g[i] = 1ll * g[i] * inv[cnt[i]] % p;
                }
                add(g[fa[i]], f[i]);
            }
        }
        printf("%lld\n", g[1]);
    }
    return 0;
}
