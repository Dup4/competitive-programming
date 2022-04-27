#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
using ll = long long;

const int N = 310;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Edge {
    int v;
    ll w;

    Edge(int _v = 0, ll _w = 0) : v(_v), w(_w) {}
};

int n, m;
vector<vector<Edge>> G;
bool vis[N];
int cnt[N];
ll dis[N];

bool SPFA(int s, int t, int w) {
    G[s].push_back(Edge(t, w));
    for (int i = 0; i <= n; ++i) {
        vis[i] = false;
        cnt[i] = 0;
        dis[i] = INFLL;
    }
    vis[s] = true;
    dis[s] = 0;
    cnt[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (auto e : G[u]) {
            int v = e.v;
            ll cost = e.w;
            if (dis[v] > dis[u] + cost) {
                dis[v] = dis[u] + cost;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                    if (++cnt[v] > n) {
                        G[s].pop_back();
                        return false;
                    }
                }
            }
        }
    }
    G[s].pop_back();
    return true;
}

void RUN() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d %d", &n, &m);
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            G[u].push_back(Edge(v, w));
        }
        for (int _q = 1, s, t; _q <= 6; ++_q) {
            scanf("%d %d", &s, &t);
            int l = -1e9, r = 1e9, res = 1e9;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (SPFA(s, t, mid)) {
                    r = mid - 1;
                    res = mid;
                } else {
                    l = mid + 1;
                }
            }
            G[s].push_back(Edge(t, res));
            printf("%d\n", res);
        }
    }
}

int main() {
#ifdef LOCAL_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    RUN();

#ifdef LOCAL_JUDGE
//    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
