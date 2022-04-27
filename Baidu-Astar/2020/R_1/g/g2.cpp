#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
#define rep(i, j, k) for (int i = (int)(j); i <= (int)(k); i++)
#define per(i, j, k) for (int i = (int)(j); i >= (int)(k); i--)
using namespace std;
typedef long long LL;
typedef double db;
int n, m, k;
int wx[7], wy[7], ww[7];
int f[2005][64], g[2005][64];
namespace aby {
const int N = 100005;
int head[N], np[N], p[N], flow[N], tot;
int n, S, T;
void init(int node) {
    n = node;
    S = n + 1;
    T = S + 1;
    rep(i, 1, T) head[i] = 0;
    rep(i, 1, tot) np[i] = p[i] = flow[i] = 0;
    tot = 1;
}
void add(int a, int b, int w) {
    ++tot;
    p[tot] = b;
    np[tot] = head[a];
    head[a] = tot;
    flow[tot] = w;
    ++tot;
    p[tot] = a;
    np[tot] = head[b];
    head[b] = tot;
    flow[tot] = 0;
}
int q[N], dis[N];
int bfs() {
    rep(i, 1, T) dis[i] = -1;
    dis[S] = 0;
    q[q[0] = 1] = S;
    rep(i, 1, q[0]) {
        int x = q[i];
        for (int u = head[x]; u; u = np[u])
            if (flow[u])
                if (dis[p[u]] == -1) {
                    dis[p[u]] = dis[x] + 1;
                    q[++q[0]] = p[u];
                }
    }
    return dis[T];
}
int dinic(int x, int fl) {
    if (x == T)
        return fl;
    if (!fl)
        return 0;
    int res = 0;
    for (int u = head[x]; u; u = np[u])
        if (flow[u])
            if (dis[p[u]] == dis[x] + 1) {
                int tmp = dinic(p[u], min(fl, flow[u]));
                fl -= tmp;
                res += tmp;
                flow[u] -= tmp;
                flow[u ^ 1] += tmp;
            }
    if (!res)
        dis[x] = -1;
    return res;
}
int getMaxFlow() {
    int res = 0;
    while (bfs() != -1) res += dinic(S, 1e9);
    return res;
}
};  // namespace aby

inline int dis(int x, int y, int nx, int ny) {
    return abs(x - nx) + abs(y - ny);
}

bool check(int lm) {
    memset(g, 0, sizeof g);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int now = 0;
            for (int o = 0; o <= k - 1; ++o) {
                //	if (o) now <<= 1;
                if (dis(i, j, wx[o], wy[o]) <= lm) {
                    now |= (1 << o);
                    //		now |= 1;
                }
            }
            //		for (int o = now; o; o = (o - 1) & now) ++f[lm][now];
            ++g[lm][now];
        }
    }
    rep(i, 1, (1 << k) - 1) if (f[lm][i] != g[lm][i]) cout << 1 / 0 << endl;
    aby::init(k + (1 << k));
    rep(i, 0, k - 1) aby::add(aby::S, i + 1, ww[i]);
    //   assert(f[lm][0]==0);
    rep(i, 1, (1 << k) - 1) aby::add(k + i, aby::T, f[lm][i]);
    rep(i, 0, k - 1) rep(j, 1, (1 << k) - 1) if (j & (1 << i)) aby::add(i + 1, k + j, 1e9);
    return aby::getMaxFlow() == n * m;
}
void Main() {
    memset(f, 0, sizeof f);
    scanf("%d%d%d", &n, &m, &k);
    int _ = 0;
    rep(i, 0, k - 1) {
        scanf("%d%d%d", &wx[i], &wy[i], &ww[i]);
        _ += ww[i];
    }
    if (_ < n * m) {
        printf("-1\n");
        return;
    }
    int least = 0;
    rep(i, 1, n) rep(j, 1, m) {
        vector<pii> t;
        rep(s, 0, k - 1) t.pb(pii(abs(i - wx[s]) + abs(j - wy[s]), s));
        sort(t.begin(), t.end());
        least = max(least, t[0].fi);
        int S = 0;
        rep(s, 0, k - 1) {
            S |= (1 << t[s].se);
            f[t[s].fi][S]++;
            if (s < k - 1)
                f[t[s + 1].fi][S]--;
        }
    }
    rep(i, 1, n + m) rep(j, 0, (1 << k) - 1) f[i][j] += f[i - 1][j];
    int L = 0, R = n + m, res = 0;
    while (R - L >= 0) {
        int mid = (L + R) >> 1;
        if (check(mid)) {
            res = mid;
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }
    printf("%d\n", res);
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) Main();
    return 0;
}
