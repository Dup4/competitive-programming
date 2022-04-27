#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e2 + 10, M = 1e4 + 10, INF = 0x3f3f3f3f;
int n, m;
struct UFS {
    int fa[N];
    void init(int n) {
        for (int i = 0; i <= n; ++i) fa[i] = i;
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y)
            fa[x] = y;
    }
    int same(int x, int y) {
        return find(x) == find(y);
    }
} ufs;

struct E {
    int u, v, w, a, b;
    bool operator<(const E &other) const {
        return w < other.w;
    }
} e[M];
int h[N];

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    int cross(const Point &b) const {
        return x * b.y - y * b.x;
    }
} ans;

Point Kruskal() {
    Point res = Point(0, 0);
    int tot = 0;
    sort(e + 1, e + m + 1);
    ufs.init(n);
    for (int i = 1; i <= m; ++i) {
        int u = e[i].u, v = e[i].v, a = e[i].a, b = e[i].b;
        if (ufs.same(u, v))
            continue;
        ufs.merge(u, v);
        res.x += a, res.y += b;
        ++tot;
        if (tot == n - 1)
            break;
    }
    ll pre = 1ll * ans.x * ans.y;
    ll now = 1ll * res.x * res.y;
    if (pre > now || (pre == now && ans.x > res.x))
        ans = res;
    return res;
}

void gao(Point A, Point B) {
    for (int i = 1; i <= m; ++i) {
        e[i].w = e[i].b * (B.x - A.x) + e[i].a * (A.y - B.y);
    }
    Point C = Kruskal();
    if ((B - A).cross(C - A) >= 0)
        return;
    gao(A, C);
    gao(C, B);
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        ans = Point(INF, INF);
        for (int i = 1, u, v, a, b; i <= m; ++i) {
            scanf("%d%d%d%d", &u, &v, &a, &b);
            ++u, ++v;
            e[i] = {u, v, 0, a, b};
        }
        for (int i = 1; i <= m; ++i) e[i].w = e[i].a;
        Point A = Kruskal();
        for (int i = 1; i <= m; ++i) e[i].w = e[i].b;
        Point B = Kruskal();
        gao(A, B);
        printf("%d %d\n", ans.x, ans.y);
    }
    return 0;
}
