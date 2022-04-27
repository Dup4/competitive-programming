#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, q;

struct SEG {
    struct node {
        int cnt;
        double Max;
        node() {
            cnt = Max = 0;
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

    int query(int id, int l, int r, double v) {
        if (l == r)
            return t[id].Max > v;
        int mid = (l + r) >> 1;
        if (t[id].Max <= v)
            return 0;
        if (t[id << 1].Max <= v)
            return query(id << 1 | 1, mid + 1, r, v);
        else
            return t[id].cnt - t[id << 1].cnt + query(id << 1, l, mid, v);
    }

    void update(int id, int l, int r, int pos, double v) {
        if (l == r) {
            t[id].cnt = 1;
            t[id].Max = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, v);
        else
            update(id << 1 | 1, mid + 1, r, pos, v);
        t[id].cnt = t[id << 1].cnt + query(id << 1 | 1, mid + 1, r, t[id << 1].Max);
        t[id].Max = max(t[id << 1].Max, t[id << 1 | 1].Max);
    }
} seg;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        seg.build(1, 1, n);
        for (int i = 1, x, y; i <= q; ++i) {
            scanf("%d%d", &x, &y);
            double tmp = y * 1.0 / x;
            seg.update(1, 1, n, x, tmp);
            printf("%d\n", seg.t[1].cnt);
        }
    }
}
