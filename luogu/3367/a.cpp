#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, q;

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

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        ufs.init(n);
        for (int i = 1, op, x, y; i <= q; ++i) {
            scanf("%d%d%d", &op, &x, &y);
            if (op == 1)
                ufs.merge(x, y);
            else
                puts(ufs.same(x, y) ? "Y" : "N");
        }
    }
    return 0;
}
