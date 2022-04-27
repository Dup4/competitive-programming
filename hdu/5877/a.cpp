#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
int n, rt, vis[N];
ll a[N], k, res;
vector<vector<int>> G;
struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) a[x] += v;
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
        return res;
    }
} bit;
vector<ll> vec;
void DFS(int u) {
    bit.update(lower_bound(vec.begin(), vec.end(), a[u]) - vec.begin() + 1, 1);
    ll t;
    if (a[u] == 0)
        t = 1e9;
    else
        t = k / a[u];
    int pos = upper_bound(vec.begin(), vec.end(), t) - vec.begin();
    res -= bit.query(pos);
    for (auto &v : G[u]) DFS(v);
    res += bit.query(pos);
}

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%lld", &n, &k);
        G.clear();
        G.resize(n + 1);
        memset(vis, 0, sizeof vis);
        vec.clear();
        res = 0;
        bit.init();
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i), vec.push_back(a[i]);
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            vis[v] = 1;
        }
        for (int i = 1; i <= n; ++i)
            if (!vis[i])
                rt = i;
        DFS(rt);
        printf("%lld\n", res);
    }
    return 0;
}
