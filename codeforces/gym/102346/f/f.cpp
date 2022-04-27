#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
int n, rate;

struct P {
    int x, y;
    void scan() {
        scanf("%d%d", &x, &y);
    }
};

struct node {
    P s, e;
    void scan() {
        s.scan();
        e.scan();
    }
};

node li[N];
node Tri;

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

node rec[N];
vector<vector<P>> add, del;

ll calc(int r) {
    hx.init();
    hy.init();
    for (int i = 1; i <= n; ++i) {
        node tmp;
        tmp.s.x = min(li[i].s.x, li[i].e.x) - r;
        tmp.s.x = max(tmp.s.x, Tri.s.x);
        tmp.s.y = min(li[i].s.y, li[i].e.y) - r;
        tmp.s.y = max(tmp.s.y, Tri.s.y);
        tmp.e.x = max(li[i].s.x, li[i].e.x) + r;
        tmp.e.x = min(tmp.e.x, Tri.e.x);
        tmp.e.y = max(li[i].s.y, li[i].e.y) + r;
        tmp.e.y = min(tmp.e.y, Tri.e.y);
        rec[i] = tmp;
        hx.add(tmp.s.x);
        hx.add(tmp.e.x);
        hy.add(tmp.s.y);
        hy.add(tmp.e.y);
    }
    hx.gao();
    hy.gao();
    for (int i = 1; i <= n; ++i) {
        rec[i].s.x = hx.get(rec[i].s.x);
        rec[i].e.x = hx.get(rec[i].e.x);
        rec[i].s.y = hy.get(rec[i].s.y);
        rec[i].e.y = hy.get(rec[i].e.y);
    }
    int cx = hx.tot, cy = hy.tot;
    add.clear();
    add.resize(cx + 5);
    del.clear();
    del.resize(cx + 5);
    for (int i = 1; i <= n; ++i) {
        add[rec[i].s.x].push_back({rec[i].s.y + 1, rec[i].e.y});
        del[rec[i].e.x].push_back({rec[i].s.y + 1, rec[i].e.y});
    }
    seg.build(1, 1, cy);
    ll res = 0;
    for (int i = 1; i <= cx; ++i) {
        res += 1ll * (hx.a[i] - hx.a[i - 1]) * seg.t[1].len;
        for (auto &it : add[i]) {
            seg.update(1, 1, cy, it.x, it.y, 1);
        }
        for (auto &it : del[i]) {
            seg.update(1, 1, cy, it.x, it.y, -1);
        }
    }
    return res * 100;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        li[i].scan();
    }
    scanf("%d", &rate);
    Tri.scan();
    ll area = 1ll * (Tri.e.x - Tri.s.x) * (Tri.e.y - Tri.s.y) * rate;
    int l = 0, r = 1e5, res = 1e5;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (calc(mid) >= area) {
            r = mid - 1;
            res = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", res);
    return 0;
}
