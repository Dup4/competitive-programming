#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
using ll = long long;
using db = double;

const int N = 1e6 + 10;
const ll p = 1e9 + 7;
const db eps = 1e-8;

int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    else
        return x > 0 ? 1 : -1;
}

ll qpow(ll x, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * x % p;
        }
        x = x * x % p;
        n >>= 1;
    }
    return res;
}

int n;
int h[N];
ll f[N];
vector<vector<int>> G;

void DFS(int u, int pre) {
    h[u] = 0;
    int cnt = 0;
    for (auto v : G[u]) {
        if (v == pre) {
            continue;
        }
        cnt++;
        DFS(v, u);
        h[u] = max(h[u], h[v] + 1);
    }
    if (!cnt) {
        h[u] = 1;
    }
}

void gao(int u, int pre) {
    int cnt = 0, hight = h[u] - 1;
    for (auto v : G[u]) {
        if (v == pre)
            continue;
        if (h[v] == hight) {
            gao(v, u);
        } else {
            f[v] = 1ll;
        }
        cnt++;
    }
    if (!cnt) {
        f[u] = 0;
        return;
    }
    ll res = 1, sum = 0;
    for (auto v : G[u]) {
        if (v == pre)
            continue;
        sum = (sum + f[v]) % p;
    }
    for (int i = 1; i <= cnt; ++i) {
        res = (res * sum) % p;
    }
    res = res * qpow(qpow(cnt, cnt), p - 2) % p;
    f[u] = res;
}

void RUN() {
    while (scanf("%d", &n) != EOF) {
        memset(f, 0, sizeof f);
        G.clear(), G.resize(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d %d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        DFS(1, 1);
        gao(1, 1);
        ll res = (1ll - f[1] + p) % p;
        printf("%lld\n", res);
    }
}

int main() {
#ifdef LOCAL_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    //    ios::sync_with_stdio(false);
    //    cin.tie(nullptr), cout.tie(nullptr);

    RUN();

#ifdef LOCAL_JUDGE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
