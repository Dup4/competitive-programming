#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 40

int n, m;
ll w[N], p;
int G[N][N], vis[N];
ll mark[N];
map<ll, ll> mp;

ll DFS(int u) {
    vis[u] = 1;
    ll S = 1ll << (u - 1);
    for (int i = 1; i <= n; ++i) {
        if (G[u][i]) {
            if (!vis[i]) {
                vis[i] = 1;
                S |= DFS(i);
            }
        }
    }
    return S;
}

ll gao(ll S) {
    if (S == 0)
        return 1ll;
    if (mp.find(S) != mp.end())
        return mp[S];
    ll res = 0;
    int i = 0;
    while (~S & (1ll << i)) ++i;
    ll now = S & mark[i + 1];
    if (~now & (1ll << i)) {
        ll tmp = 1;
        for (int j = 0; j < n; ++j) {
            if (now & (1ll << j)) {
                tmp = tmp * w[j + 1] % p;
            }
        }
        res = (res + tmp * gao(S ^ ((1ll << i) | now)) % p) % p;
    }
    res = (res + w[i + 1] * gao(S ^ (1ll << i)) % p) % p;
    mp[S] = res;
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        printf("Case #%d: ", cas);
        scanf("%d %d %lld", &n, &m, &p);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                G[i][j] = 0;
            }
            vis[i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", w + i);
            w[i] %= p;
        }
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d %d", &u, &v);
            G[u][v] = G[v][u] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            ll S = 0ll;
            for (int j = 1; j <= n; ++j) {
                if (i != j && G[i][j]) {
                    S |= 1ll << (j - 1);
                }
            }
            mark[i] = S;
        }
        ll ans = 1;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) {
                vis[i] = 1;
                ll S = DFS(i);
                mp.clear();
                ans = ans * gao(S) % p;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
