#include <bits/stdc++.h>
using namespace std;
typedef double db;
const db eps = 1e-8;
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}
const int N = 5e4 + 10;
#define N 50010
int n, q;

struct SEG {
    struct node {
        bool F;
        db k, b;
        node(bool F = 0, db k = 0, db b = 0) : F(F), k(k), b(b) {}
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
        //维护最大值优势线段
        if (sgn(preL - newL) >= 0 && sgn(preR - newR) >= 0)
            return;
        if (newL > preL && newR > preR) {
            t[id] = tmp;
            return;
        }
        //计算交点
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
    void update(int id, int l, int r, db k, db b) {
        update(id, l, r, node(1, k, b));
    }
    db query(int id, int l, int r, int x) {
        if (l == r)
            return t[id].calc(x);
        int mid = (l + r) >> 1;
        db res = t[id].calc(x);
        if (x <= mid)
            res = max(res, query(id << 1, l, mid, x));
        else
            res = max(res, query(id << 1 | 1, mid + 1, r, x));
        return res;
    }
} seg;

int main() {
    n = 50000;
    while (scanf("%d", &q) != EOF) {
        seg.build(1, 1, n);
        char op[20];
        db k, b;
        int x;
        for (int _q = 1; _q <= q; ++_q) {
            scanf("%s", op + 1);
            switch (op[1]) {
                case 'P':
                    scanf("%lf%lf", &b, &k);
                    seg.update(1, 1, n, k, b - k);
                    break;
                case 'Q':
                    scanf("%d\n", &x);
                    printf("%lld\n", (long long)(seg.query(1, 1, n, x) / 100));
                    break;
            }
        }
    }
    return 0;
}
