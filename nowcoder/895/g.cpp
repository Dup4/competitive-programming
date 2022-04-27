#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
#define N 100010
struct SEG {
    struct node {
        ll sum, lazy;
        node() {}
        node(ll sum, ll lazy) : sum(sum), lazy(lazy) {}
        void add(ll x) {
            sum = min(sum, x);
            lazy = min(lazy, x);
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node(INFLL, INFLL);
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void pushdown(int id) {
        t[id << 1].add(t[id].lazy);
        t[id << 1 | 1].add(t[id].lazy);
    }
    void update(int id, int l, int r, int ql, int qr, ll v) {
        if (l >= ql && r <= qr) {
            t[id].add(v);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
    }
    ll query(int id, int l, int r, int pos) {
        if (l == r) {
            return t[id].sum;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} seg[12];
int n, q, a[N];

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 0; i <= 10; ++i) {
            seg[i].build(1, 1, n);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        int op, l, r, x, y;
        ll res;
        while (q--) {
            scanf("%d", &op);
            switch (op) {
                case 1:
                    scanf("%d%d%d%d", &l, &r, &x, &y);
                    seg[y + 5].update(1, 1, n, l, r, 1ll * y * (-l) + x);
                    break;
                case 2:
                    scanf("%d", &x);
                    res = a[x];
                    for (int i = 0; i <= 10; ++i) {
                        res = min(res, 1ll * (i - 5) * x + seg[i].query(1, 1, n, x));
                    }
                    printf("%lld\n", res);
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}
