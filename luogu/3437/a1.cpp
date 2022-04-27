#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int n, m, q;

struct ODTree {
    struct node {
        int Max, lazy;
        node(){};
        void init() {
            Max = lazy = 0;
        }
    } t[N * 3];
    void build(int id, int l, int r, int Tl, int Tr) {
        t[id].init();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid, Tl, Tr);
        build(id << 1 | 1, mid + 1, r, Tl, Tr);
    }
    void update(int id, int l, int r, int ql, int qr, int v) {
        if (min(r, qr) - max(l, ql) + 1 > 0) {
            t[id].Max = max(t[id].Max, v);
        }
        if (l >= ql && r <= qr) {
            t[id].lazy = max(t[id].lazy, v);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id].Max;
        int mid = (l + r) >> 1;
        int res = t[id].lazy;
        if (ql <= mid)
            res = max(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
};

struct TDTree {
    struct node {
        ODTree Max, lazy;
        node() {}
    } t[N * 3];
    void build(int id, int l, int r) {
        t[id].Max.build(1, 1, m, l, r);
        t[id].lazy.build(1, 1, m, l, r);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int ql, int qr, int Ol, int Or, int v) {
        if (min(r, qr) - max(l, ql) + 1 > 0) {
            t[id].Max.update(1, 1, m, Ol, Or, v);
        }
        if (l >= ql && r <= qr) {
            t[id].lazy.update(1, 1, m, Ol, Or, v);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, Ol, Or, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, Ol, Or, v);
    }
    int query(int id, int l, int r, int ql, int qr, int Ol, int Or) {
        if (l >= ql && r <= qr)
            return t[id].Max.query(1, 1, m, Ol, Or);
        int mid = (l + r) >> 1;
        int res = t[id].lazy.query(1, 1, m, Ol, Or);
        if (ql <= mid)
            res = max(res, query(id << 1, l, mid, ql, qr, Ol, Or));
        if (qr > mid)
            res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr, Ol, Or));
        return res;
    }
} td;

int main() {
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        ++n, ++m;
        td.build(1, 1, n);
        for (int i = 1, d, s, w, x, y; i <= q; ++i) {
            scanf("%d%d%d%d%d", &d, &s, &w, &x, &y);
            td.update(1, 1, n, x + 1, x + d, y + 1, y + s, td.query(1, 1, n, x + 1, x + d, y + 1, y + s) + w);
        }
        printf("%d\n", td.query(1, 1, n, 1, n, 1, m));
    }
    return 0;
}
