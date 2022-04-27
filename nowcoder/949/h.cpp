#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, q, a[N], b[N];
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

struct SEG1 {
    struct node {
        ll sum;
        int cnt, lazy, l, r, Max;
        node() {
            sum = cnt = lazy = 0;
            l = r = Max = 0;
        }
        void add(int x) {
            sum += 1ll * cnt * x;
            lazy += x;
            l += x;
            r += x;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sum = sum + other.sum;
            res.cnt = cnt + other.cnt;
            res.l = l;
            res.r = other.r;
            res.Max = max(Max, other.Max);
            res.Max = max(res.Max, abs(r - other.l));
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = node();
            t[id].sum = a[l];
            t[id].cnt = 1;
            t[id].l = t[id].r = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void down(int id) {
        int &lazy = t[id].lazy;
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
        down(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, x);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    node query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id];
        int mid = (l + r) >> 1;
        down(id);
        if (ql <= mid && qr > mid) {
            node L = query(id << 1, l, mid, ql, qr);
            node R = query(id << 1 | 1, mid + 1, r, ql, qr);
            return L + R;
        } else if (ql <= mid) {
            return query(id << 1, l, mid, ql, qr);
        } else if (qr > mid) {
            return query(id << 1 | 1, mid + 1, r, ql, qr);
        } else {
            assert(0);
        }
    }
} seg1;

struct SEG2 {
    int t[N << 2];
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = b[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = gcd(t[id << 1], t[id << 1 | 1]);
    }
    void update(int id, int l, int r, int x, int v) {
        if (l == r) {
            t[id] += v;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(id << 1, l, mid, x, v);
        else
            update(id << 1 | 1, mid + 1, r, x, v);
        t[id] = gcd(t[id << 1], t[id << 1 | 1]);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (ql > qr)
            return 0;
        if (l >= ql && r <= qr)
            return t[id];
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res = gcd(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            res = gcd(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg2;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            b[i] = a[i] - a[i - 1];
        }
        seg1.build(1, 1, n);
        seg2.build(1, 1, n);
        int op, l, r, x;
        while (q--) {
            scanf("%d%d%d", &op, &l, &r);
            switch (op) {
                case 1:
                    scanf("%d", &x);
                    seg1.update(1, 1, n, l, r, x);
                    seg2.update(1, 1, n, l, x);
                    if (r < n)
                        seg2.update(1, 1, n, r + 1, -x);
                    break;
                case 2:
                    seg1.res = seg1.query(1, 1, n, l, r);
                    printf("%d\n", seg1.res.Max);
                    break;
                case 3:
                    seg1.res = seg1.query(1, 1, n, l, l);
                    printf("%d\n", abs(gcd(seg1.res.sum, seg2.query(1, 1, n, l + 1, r))));
                    break;
            }
        }
    }
    return 0;
}
