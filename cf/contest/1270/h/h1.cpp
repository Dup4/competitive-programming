#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, q, a[N];

struct SEG {
    struct node {
        int cnt, Max, Min;
        node() {
            cnt = 0;
            Min = 1e9;
            Max = -1e9;
        }
        node operator+(const node &other) const {
            node res = node();
            res.Max = max(Max, other.Max);
            res.Min = min(Min, other.Min);
            return res;
        }
    } t[N << 2];
    int queryl(int id, int l, int r, int v) {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (t[id << 1].Min < v)
            return queryl(id << 1, l, mid, v);
        else
            return query(id << 1 | 1, mid + 1, r, v);
    }
    int queryr(int id, int l, int r, int v) {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (t[id << 1 | 1].Max > v)
            return queryr(id << 1 | 1, mid + 1, r, v);
        else
            return queryr(id << 1, l, mid, v);
    }
    int calc(int id, int l, int r) {
        if (l > r)
            return 0;
        if (l == r)
            return 1;
        if (t[id << 1].Min > t[id << 1 | 1].Max)
            return t[id << 1].cnt + t[id << 1 | 1].cnt;
        int mid = (l + r) >> 1;
    }
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].Max = t[id].Min = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
        t[id].cnt = calc(id, l, r);
    }
    void update(int id, int l, int r, int pos, int v) {
        if (l == r) {
            t[id].cnt = 1;
            t[id].Max = t[id].Min = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, v);
        else
            update(id << 1 | 1, mid + 1, r, pos, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    int query(int id, int l, int r, int v) {
        if (l == r)
            return t[id].Min < v;
        int mid = (l + r) >> 1;
        if (t[id].Min >= v)
            return 0;
        if (t[id << 1].Min >= v)
            return query(id << 1 | 1, mid + 1, r, v);
        else
            return t[id].cnt - t[id << 1].cnt + query(id << 1, l, mid, v);
    }
    void update(int id, int l, int r, int pos, int v) {
        if (l == r) {
            t[id].cnt = 1;
            t[id].Min = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, v);
        else
            update(id << 1 | 1, mid + 1, r, pos, v);
        t[id].cnt = t[id << 1].cnt + query(id << 1 | 1, mid + 1, r, t[id << 1].Min);
        t[id].Min = min(t[id << 1].Min, t[id << 1 | 1].Min);
    }
} seg;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        seg.build(1, 1, n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), seg.update(1, 1, n, i, a[i]);
        for (int i = 1, pos, x; i <= q; ++i) {
            scanf("%d%d", &pos, &x);
            seg.update(1, 1, n, pos, x);
            printf("%d\n", seg.t[1].cnt);
        }
    }
    return 0;
}
