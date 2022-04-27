#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))
const int N = 1e5 + 10;
int n, m;

struct E {
    int u, v, w;
    E() {}
    E(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const E &other) const {
        return w < other.w;
    }
};

vector<E> G;

struct UFS {
    int fa[N], rk[N];
    void init(int n) {
        memset(fa, 0, sizeof(fa[0]) * (n + 5));
        memset(rk, 0, sizeof(rk[0]) * (n + 5));
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (rk[fx] > rk[fy])
                swap(fx, fy);
            fa[fx] = fy;
            if (rk[fx] == rk[fy])
                ++rk[fy];
            return true;
        }
        return false;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
} ufs;

int gao() {
    sort(all(G));
    int res = 0;
    for (auto &e : G) {
        int u = e.u, v = e.v, w = e.w;
        if (ufs.merge(u, v)) {
            res += w;
        }
    }
    return res;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &m);
        G.clear();
        ufs.init(n + 1);
        for (int i = 1, w; i <= n; ++i) {
            scanf("%d", &w);
            G.emplace_back(i, n + 1, w);
        }
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            G.emplace_back(u, v, w);
        }
        printf("%d\n", gao());
    }
    return 0;
}