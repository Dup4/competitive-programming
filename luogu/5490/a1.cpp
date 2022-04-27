#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
#define fi first
#define se second
const int N = 2e5 + 20;
int n;

namespace RectangularAreaUnion {
int cx, cy;
vector<vector<pII>> add, del;
struct Hash {
    int a[N], tot;
    void init() {
        tot = 0;
        a[0] = 0;
    }
    void add(int x) {
        a[++tot] = x;
    }
    void gao() {
        sort(a + 1, a + 1 + tot);
        tot = unique(a + 1, a + 1 + tot) - a - 1;
    }
    int get(int x) {
        return lower_bound(a + 1, a + 1 + tot, x) - a;
    }
} hx, hy;

struct SEG {
    struct node {
        int cnt, len;
        void init() {
            cnt = len = 0;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id].init();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void up(int id, int l, int r) {
        if (t[id].cnt > 0) {
            t[id].len = hy.a[r] - hy.a[l - 1];
        } else {
            if (l == r)
                t[id].len = 0;
            else {
                t[id].len = t[id << 1].len + t[id << 1 | 1].len;
            }
        }
    }
    void update(int id, int l, int r, int ql, int qr, int v) {
        if (ql > qr)
            return;
        if (l >= ql && r <= qr) {
            t[id].cnt += v;
            up(id, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
        up(id, l, r);
    }
} seg;

struct E {
    int x[2], y[2];
    void scan() {
        scanf("%d%d%d%d", x, y, x + 1, y + 1);
        for (int i = 0; i < 2; ++i) {
            hx.add(x[i]);
            hy.add(y[i]);
        }
    }
} e[N];

ll gao() {
    hx.init();
    hy.init();
    for (int i = 1; i <= n; ++i) {
        e[i].scan();
    }
    hx.gao();
    hy.gao();
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 2; ++j) {
            e[i].x[j] = hx.get(e[i].x[j]);
            e[i].y[j] = hy.get(e[i].y[j]);
        }
    }
    ll res = 0;
    cx = hx.tot;
    cy = hy.tot;
    add.clear();
    add.resize(cx + 5);
    del.clear();
    del.resize(cx + 5);
    for (int i = 1; i <= n; ++i) {
        add[e[i].x[0]].push_back(pII(e[i].y[0] + 1, e[i].y[1]));
        del[e[i].x[1]].push_back(pII(e[i].y[0] + 1, e[i].y[1]));
    }
    seg.build(1, 1, cy);
    for (int i = 1; i <= cx; ++i) {
        res += 1ll * (hx.a[i] - hx.a[i - 1]) * seg.t[1].len;
        for (auto &it : add[i]) {
            seg.update(1, 1, cy, it.fi, it.se, 1);
        }
        for (auto &it : del[i]) {
            seg.update(1, 1, cy, it.fi, it.se, -1);
        }
    }
    return res;
}
}  // namespace RectangularAreaUnion

int main() {
    while (scanf("%d", &n) != EOF) printf("%lld\n", RectangularAreaUnion::gao());
    return 0;
}
