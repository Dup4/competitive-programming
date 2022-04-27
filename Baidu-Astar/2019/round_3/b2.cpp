#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
const int N = 1e3 + 10;
const int mod = 998244353;
inline void chadd(int &x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m, ans, id[N], used[N];
ll dis[N];
vector<vector<pii>> G;
struct node {
    int v;
    ll w;
    node() {}
    node(int v, ll w) : v(v), w(w) {}
    bool operator<(const node &other) const {
        return w > other.w;
    }
};
void Dijkstra(int s) {
    for (int i = 1; i <= n; ++i) {
        dis[i] = 1e18;
        used[i] = 0;
        id[i] = 0;
    }
    dis[s] = 0;
    priority_queue<node> pq;
    pq.push(node(s, 0));
    while (!pq.empty()) {
        int u = pq.top().v;
        pq.pop();
        if (used[u])
            continue;
        used[u] = 1;
        chadd(ans, id[u]);
        //		cout << s << " " << u << " " << id[u] << endl;
        for (auto &it : G[u]) {
            int v = it.fi, w = it.se;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                id[v] = max(id[u], (u == s ? 0 : u));
                pq.push(node(v, dis[v]));
            } else if (dis[v] == dis[u] + w) {
                id[v] = min(id[v], max(id[u], (u == s ? 0 : u)));
            }
        }
    }
}

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%d", &n, &m);
        G.clear();
        G.resize(n + 1);
        ans = 0;
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G[u].push_back(pii(v, w));
            G[v].push_back(pii(u, w));
        }
        for (int i = 1; i <= n; ++i) Dijkstra(i);
        printf("%d\n", ans);
    }
    return 0;
}
