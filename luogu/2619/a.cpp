#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, C;

struct Edge {
    int u, v, w, k, vis;
    Edge() {}
    Edge(int u, int v, int w, int vis) : u(u), v(v), w(w), vis(vis) {
        k = 0;
    }
    bool operator<(const Edge &other) const {
        if (k + w == other.k + other.w)
            return vis > other.vis;
        return k + w < other.k + other.w;
    }
} e[N];

struct UFS {
    int fa[N];
    void init() {
        memset(fa, 0, sizeof fa);
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    bool merge(int u, int v) {
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            fa[fu] = fv;
            return true;
        }
        return false;
    }
} ufs;

namespace WQS {
int check(int K) {
    for (int i = 1; i <= m; ++i) {
        e[i].k = e[i].vis * K;
    }
    sort(e + 1, e + 1 + m);
    ufs.init();
    int cnt_e = 0;
    for (int i = 1; i <= m; ++i) {
        int u = e[i].u, v = e[i].v;
        if (ufs.merge(u, v))
            cnt_e += e[i].vis;
    }
    return cnt_e;
}
int calc(int K) {
    for (int i = 1; i <= m; ++i) {
        e[i].k = e[i].vis * K;
    }
    sort(e + 1, e + 1 + m);
    ufs.init();
    ll tot = 0;
    for (int i = 1; i <= m; ++i) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (ufs.merge(u, v))
            tot += w + e[i].k;
    }
    return tot - C * K;
}
void gao() {
    int l = -200, r = 100, res = -200;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (check(mid) >= C) {
            l = mid + 1;
            res = mid;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", calc(res));
}
}  // namespace WQS

int main() {
    while (scanf("%d%d%d", &n, &m, &C) != EOF) {
        for (int i = 1, u, v, w, vis; i <= m; ++i) {
            scanf("%d%d%d%d", &u, &v, &w, &vis);
            ++u, ++v;
            e[i] = Edge(u, v, w, vis ^ 1);
        }
        WQS::gao();
    }
    return 0;
}
