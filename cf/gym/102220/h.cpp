#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, m, a[N];

struct SEG {
    struct node {
        ll sum, lazy, l, r;
        node() {
            sum = lazy = 0;
            l = r = 0;
        }
        node(ll sum, ll lazy, ll l, ll r) : sum(sum), lazy(lazy), l(l), r(r) {}
        void add(ll x) {
            sum += x;
            lazy += x;
            l += x;
            r += x;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sum = sum + other.sum - min(r, other.l);
            res.l = l;
            res.r = other.r;
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].sum = a[l];
            t[id].l = a[l];
            t[id].r = a[r];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void pushdown(int id) {
        ll &lazy = t[id].lazy;
        if (!lazy)
            return;
        t[id << 1].add(lazy);
        t[id << 1 | 1].add(lazy);
        lazy = 0;
    }
    void update(int id, int l, int r, int ql, int qr, int x) {
        if (l >= ql && r <= qr) {
            t[id].add(x);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, x);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            res = res + t[id];
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr);
    }
} seg;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        seg.build(1, 1, n);
        int op, l, r, x;
        while (m--) {
            scanf("%d%d%d", &op, &l, &r);
            switch (op) {
                case 1:
                    scanf("%d", &x);
                    seg.update(1, 1, n, l, r, x);
                    break;
                case 2:
                    seg.res = SEG::node();
                    seg.query(1, 1, n, l, r);
                    printf("%lld\n", seg.res.sum);
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}
