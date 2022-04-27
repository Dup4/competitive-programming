#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, m;
ll f(int x, int n) {
    return 1ll * (x + x + n - 1) * n / 2;
}
struct SEG {
    struct node {
        ll sum, lazy;
        node() {
            sum = lazy = 0;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sum = sum + other.sum;
            return res;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = node();
            t[id].sum = l;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void pushdown(int id, int l, int mid, int r) {
        ll &x = t[id].lazy;
        if (x == 0) {
            return;
        }
        t[id << 1].sum = f(x, mid - l + 1);
        t[id << 1].lazy = x;
        t[id << 1 | 1].sum = f(x + mid - l + 1, r - mid);
        t[id << 1 | 1].lazy = x + mid - l + 1;
        x = 0;
    }
    void update(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            t[id].lazy = l - ql + 1;
            t[id].sum = f(l - ql + 1, r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id, l, mid, r);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    ll query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            return t[id].sum;
        }
        int mid = (l + r) >> 1;
        pushdown(id, l, mid, r);
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
        int op, l, r;
        seg.build(1, 1, n);
        while (m--) {
            scanf("%d%d%d", &op, &l, &r);
            switch (op) {
                case 1:
                    seg.update(1, 1, n, l, r);
                    break;
                case 2:
                    printf("%lld\n", seg.query(1, 1, n, l, r));
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}
