#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1e5 + 10;
int n, m, r;
struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
} e[N];

int fa[N];
int find(int x) {
    return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}
void Kruskal() {
    int res = 0;
    memset(fa, 0, sizeof fa);
    int tot = n + m + r;
    sort(e + 1, e + 1 + tot);
    for (int i = 1; i <= tot; ++i) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int fu = find(u), fv = find(v);
        if (fu == fv)
            continue;
        res += w;
        fa[fu] = fv;
    }
    printf("%d\n", res);
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d%d", &n, &m, &r);
        for (int i = 1, u, v, w; i <= r; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            ++u, ++v;
            e[i] = Edge(u, v + n, 10000 - w);
        }
        for (int i = r + 1; i <= r + n + m; ++i) {
            e[i] = Edge(i - r, n + m + 1, 10000);
        }
        Kruskal();
    }
    return 0;
}
