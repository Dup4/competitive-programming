#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int n, m;
ll a[N];

struct SEG {
    struct node {
        int cnt;
        ll sum, lazy;
        node() {}
        void up(ll _lazy) {
            sum += _lazy * cnt;
            lazy += _lazy;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sum = sum + other.sum;
            res.cnt = cnt + other.cnt;
            return res;
        }
    } t[N << 2];
    void pushdown(int id) {
        ll &lazy = t[id].lazy;
        if (lazy) {
            t[id << 1].up(lazy);
            t[id << 1 | 1].up(lazy);
            lazy = 0;
        }
    }
    void build(int id, int l, int r) {
        if (l == r) {
            t[id].cnt = 1;
            t[id].sum = a[l];
            t[id].lazy = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int ql, int qr, ll v) {
        if (l >= ql && r <= qr) {
            t[id].up(v);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    ll query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id].sum;
        int mid = (l + r) >> 1;
        pushdown(id);
        ll res = 0;
        if (ql <= mid)
            res += query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            res += query(id << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }
} seg;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
        seg.build(1, 1, n);
        for (int i = 1, op, x, y; i <= m; ++i) {
            ll k;
            scanf("%d%d%d", &op, &x, &y);
            if (op == 1) {
                scanf("%lld", &k);
                seg.update(1, 1, n, x, y, k);
            } else {
                printf("%lld\n", seg.query(1, 1, n, x, y));
            }
        }
    }
    return 0;
}
