#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define pii pair<int, int>
#define fi first
#define se second
int n, m, a[N];
vector<vector<int>> G;
vector<map<int, int>> mp;
ll res[N], tot;

ll f(ll x) {
    return x * (x - 1) / 2;
}

ll getse(map<int, int> &mp, int x) {
    if (mp.find(x) == mp.end())
        return 0;
    return f(mp[x]);
}

void del(map<int, int> &mp, int x, int num, ll &tmp) {
    tmp -= getse(mp, x);
    if (mp[x] == num)
        mp.erase(x);
    else
        mp[x] -= num;
    tmp += getse(mp, x);
}

void add(map<int, int> &mp, int x, int num, ll &tmp) {
    tmp -= getse(mp, x);
    mp[x] += num;
    tmp += getse(mp, x);
}

int fa[N];
void DFS(int u) {
    mp[u].clear();
    mp[u][a[u]] = 1;
    for (auto v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            DFS(v);
            ++mp[u][a[v]];
        }
    for (auto it : mp[u]) {
        tot += f(it.se);
    }
}

void DFS2(int u) {
    res[u] = 0;
    ll tmp = tot;
    if (u != 1) {
        del(mp[fa[u]], a[u], 1, tmp);
    }
    del(mp[u], a[u], 1, tmp);
    res[u] = tmp;
    for (auto v : G[u])
        if (v != fa[u]) {
            del(mp[u], a[v], 1, tmp);
            for (auto it : mp[v]) {
                add(mp[u], it.fi, it.se, tmp);
                tmp -= getse(mp[v], it.fi);
            }
            if (u != 1) {
                add(mp[fa[u]], a[v], 1, tmp);
            }
            res[u] = max(res[u], tmp);
            for (auto it : mp[v]) {
                del(mp[u], it.fi, it.se, tmp);
                tmp += getse(mp[v], it.fi);
            }
            if (u != 1) {
                del(mp[fa[u]], a[v], 1, tmp);
            }
            add(mp[u], a[v], 1, tmp);
        }
    if (u != 1) {
        ++mp[fa[u]][a[u]];
    }
    ++mp[u][a[u]];
    for (auto v : G[u])
        if (v != fa[u])
            DFS2(v);
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        mp.clear();
        mp.resize(n + 1);
        G.clear();
        G.resize(n + 1);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        fa[1] = 0;
        DFS(1);
        DFS2(1);
        for (int i = 1; i <= n; ++i) printf("%lld%c", res[i], " \n"[i == n]);
    }
    return 0;
}
