#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
using ll = long long;
using db = double;

const int N = 1e5 + 10;
const db eps = 1e-8;
const ll p = 1e9 + 7;

int sgn(db x) {
    if (fabs(x) < eps) return 0;
    else return x > 0 ? 1 : -1;
}

int n, m, k;
int vis[N], fa[N], sze[N], a[N];
vector<vector<int>> G;

void Init() {
    G.clear();
    G.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        sze[i] = 1;
        vis[i] = 0;
    }
}

int find(int x) {
    return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}

void Union(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        if (sze[x] > sze[y]) swap(x, y);
        fa[x] = y;
        sze[y] += sze[x];
    }
}

void RUN() {
    scanf("%d %d %d", &n, &m, &k);
    Init();
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= k; ++i) {
        scanf("%d", a + i);
        vis[a[i]] = 1;
    }
    for (int u = 1; u <= n; ++u) {
        if (vis[u]) continue;
        for (auto v : G[u]) {
            if (vis[v]) continue;
            Union(u, v);
        }
    }
    db res = sze[find(1)];
    db other = 0;
    for (int u = 1; u <= n; ++u) {
        if (vis[u]) {
            bool F = false;
            for (auto v : G[u]) {
                if (find(v) == 1) {
                    F = true;
                    break;
                }
            }
            if (!F) continue;
            ll cnt = 0;
            for (auto v : G[u]) {
                if (vis[v]) continue;
                if (find(v) == 1) continue;
                cnt += sze[find(v)];
            }
            db tmp = 1.0 * cnt / G[u].size();
            if (sgn(tmp - other) > 0) {
                other = tmp;
            }
        }
    }
    printf("%.10f\n", res + other);
}

int main() {

    int _T;
    scanf("%d", &_T);
    while (_T--) {
        RUN();
    }
    return 0;
}
