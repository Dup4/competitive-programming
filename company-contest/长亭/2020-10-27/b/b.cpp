#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))

const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
int n, p, t[N], vis[N];
vector <vector<int>> G;

int ok(int x) {
    if (t[1] >= x) return 0;
    queue <int> que;
    que.push(1);
    int cnt = 1;
    for (int i = 1; i <= n; ++i) vis[i] = 0;
    vis[1] = 1;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        for (auto &v : G[u]) {
            if (!vis[v] && t[v] < x) {
                que.push(v);
                vis[v] = 1;
                ++cnt;
            }
        }
    }
    return cnt;
}

int main() {
    int _T; scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &p);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", t + i);
        }
        G.clear(); G.resize(n + 1);
        for (int i = 1, m, x; i <= n; ++i) {
            scanf("%d", &m);
            G[i].clear();
            for (int j = 0; j < m; ++j) {
                scanf("%d", &x);
                assert(x >= 1 && x <= n);
                G[i].push_back(x);
            }
        }
        int l = 0, r = INF, res = r;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (ok(mid) * 100 >= n * p) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        if (res == INF) res = -1;
        printf("%d\n", res);
    }
    return 0;
}