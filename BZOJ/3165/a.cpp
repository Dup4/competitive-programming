#include <bits/stdc++.h>
using namespace std;
typedef double db;
const int N = 1e5 + 10;
const db eps = 1e-8;
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}
int q, ans, tot;
db K[N], B[N];
struct SEG {
    struct node {
        db k, b;
        int pos;
        bool F;
        node(db k = 0, db b = 0, int pos = 0, bool F = 0) : k(k), b(b), pos(pos), F(F) {}
        db calc(db x) {
            return k * x + b;
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
    db div(db a, db b) {
        return a / b;
    }
    //	db div(db a, db b) { return a / b - ((a ^ b) < 0 && a % b); }
    void update(int id, int l, int r, node tmp) {
        if (t[id].F == 0) {
            t[id] = tmp;
            return;
        }
        int mid = (l + r) >> 1;
        db preL = t[id].calc(l), preR = t[id].calc(r);
        db newL = tmp.calc(l), newR = tmp.calc(r);
        if (sgn(preL - newL) >= 0 && sgn(preR - newR) >= 0)
            return;
        if (newL > preL && newR > preR) {
            t[id] = tmp;
            return;
        }
        db x = div(tmp.b - t[id].b, t[id].k - tmp.k);
        if (newL > preL) {
            if (x > mid) {
                update(id << 1 | 1, mid + 1, r, t[id]);
                t[id] = tmp;
            } else {
                update(id << 1, l, mid, tmp);
            }
        } else {
            if (x > mid) {
                update(id << 1 | 1, mid + 1, r, tmp);
            } else {
                update(id << 1, l, mid, t[id]);
                t[id] = tmp;
            }
        }
    }
    void update(int id, int l, int r, int ql, int qr, node tmp) {
        if (l >= ql && r <= qr) {
            update(id, l, r, tmp);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, tmp);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, tmp);
    }
    void update(int id, int l, int r, int ql, int qr, db k, db b, int pos) {
        update(id, l, r, ql, qr, node(k, b, pos, 1));
    }
    void Cmax(int &a, int b, int x) {
        db ya = K[a] * x + B[a];
        db yb = K[b] * x + B[b];
        if (ya < yb || (fabs(ya - yb) < eps && a > b))
            a = b;
    }
    int query(int id, int l, int r, int x) {
        if (l == r)
            return t[id].pos;
        int mid = (l + r) >> 1;
        int res = t[id].pos;
        if (x <= mid)
            Cmax(res, query(id << 1, l, mid, x), x);
        else
            Cmax(res, query(id << 1 | 1, mid + 1, r, x), x);
        return res;
    }
} seg;

int main() {
    while (scanf("%d", &q) != EOF) {
        int n = 100000;
        seg.build(1, 1, n);
        int op, x[2], y[2];
        int mod = 39989;
        ans = 0;
        for (int _q = 1; _q <= q; ++_q) {
            scanf("%d", &op);
            switch (op) {
                case 0:
                    scanf("%d", x);
                    x[0] = (x[0] + ans - 1) % mod + 1;
                    printf("%d\n", ans = seg.query(1, 1, n, x[0]));
                    break;
                case 1:
                    for (int i = 0; i < 2; ++i) {
                        scanf("%d%d", x + i, y + i);
                        x[i] = (x[i] + ans - 1) % mod + 1;
                        y[i] = (y[i] + ans - 1) % 1000000000 + 1;
                    }
                    if (x[0] > x[1]) {
                        swap(x[0], x[1]);
                        swap(y[0], y[1]);
                    }
                    ++tot;
                    K[tot] = 1.0 * (y[0] - y[1]) / (x[0] - x[1]);
                    B[tot] = y[0] - K[tot] * x[0];
                    seg.update(1, 1, n, x[0], x[1], K[tot], B[tot], tot);
                    break;
            }
        }
    }
    return 0;
}
