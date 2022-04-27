#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n;

namespace RectangularPerimeterUnion {
int m;
struct E {
    int l, r, h, d;
    E() {}
    E(int l, int r, int h, int d) : l(l), r(r), h(h), d(d) {}
    bool operator<(const E &other) const {
        if (h != other.h)
            return h < other.h;
        return d > other.d;
    }
} e[N << 1];
struct Hash {
    vector<int> a;
    int operator[](int x) {
        return a[x - 1];
    }
    int size() {
        return a.size();
    }
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int get(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hs;
struct SEG {
    struct node {
        int cnt, len, vtl, lbd, rbd;
        node() {
            cnt = len = vtl = lbd = rbd = 0;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void up(int id, int l, int r) {
        if (t[id].cnt > 0) {
            t[id].lbd = t[id].rbd = true;
            t[id].len = hs[r] - hs[l - 1];
            t[id].vtl = 2;
        } else {
            if (l == r) {
                t[id] = node();
            } else {
                t[id].lbd = t[id << 1].lbd;
                t[id].rbd = t[id << 1 | 1].rbd;
                t[id].len = t[id << 1].len + t[id << 1 | 1].len;
                t[id].vtl = t[id << 1].vtl + t[id << 1 | 1].vtl;
                if (t[id << 1].rbd && t[id << 1 | 1].lbd)
                    t[id].vtl -= 2;
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
int gao() {
    hs.init();
    m = 0;
    for (int i = 1; i <= n; ++i) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        e[++m] = E(x1, x2, y1, 1);
        e[++m] = E(x1, x2, y2, -1);
        hs.add(x1);
        hs.add(x2);
    }
    hs.gao();
    sort(e + 1, e + 1 + m);
    int _n = hs.size();
    seg.build(1, 1, _n);
    int res = 0, last = 0;
    e[m + 1].h = 0;
    for (int i = 1; i <= m; ++i) {
        int l = hs.get(e[i].l) + 1;
        int r = hs.get(e[i].r);
        seg.update(1, 1, _n, l, r, e[i].d);
        res += seg.t[1].vtl * (e[i + 1].h - e[i].h);
        int now = seg.t[1].len;
        res += abs(now - last);
        last = now;
    }
    return res;
}
}  // namespace RectangularPerimeterUnion

int main() {
    while (scanf("%d", &n) != EOF) printf("%d\n", RectangularPerimeterUnion::gao());
    return 0;
}
