#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m, q, a[N], b[N];

inline int get(int x) {
    return lower_bound(b + 1, b + 1 + *b, x) - b;
}

struct SEG {
    struct node {
        int ls, rs, sum;
        void init() {
            ls = rs = sum = 0;
        }
    } t[N * 40];
    int rt[N], tot;
    void init() {
        memset(rt, 0, sizeof rt);
        tot = 0;
        t[0].init();
    }
    int newnode() {
        ++tot;
        t[tot].init();
        return tot;
    }
    void build(int &id, int l, int r) {
        id = newnode();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(t[id].ls, l, mid);
        build(t[id].rs, mid + 1, r);
    }
    void update(int &now, int pre, int l, int r, int pos, int v) {
        now = newnode();
        t[now] = t[pre];
        t[now].sum += v;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, t[pre].ls, l, mid, pos, v);
        else
            update(t[now].rs, t[pre].rs, mid + 1, r, pos, v);
    }
    int query(int tl, int tr, int l, int r, int ql, int qr) {
        if (ql > qr || tr == 0)
            return 0;
        if (l >= ql && r <= qr) {
            return t[tr].sum - t[tl].sum;
        }
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res += query(t[tl].ls, t[tr].ls, l, mid, ql, qr);
        if (qr > mid)
            res += query(t[tl].rs, t[tr].rs, mid + 1, r, ql, qr);
        return res;
    }
} seg;

int main() {
    while (scanf("%d", &n) != EOF) {
        *b = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            b[++*b] = a[i];
        }
        sort(b + 1, b + 1 + *b);
        *b = unique(b + 1, b + 1 + *b) - b - 1;
        m = *b;
        seg.init();
        seg.build(seg.rt[0], 1, m);
        for (int i = 1; i <= n; ++i) {
            seg.update(seg.rt[i], seg.rt[i - 1], 1, m, get(a[i]), a[i]);
        }
        scanf("%d", &q);
        while (q--) {
            int l, r;
            scanf("%d%d", &l, &r);
            --l;
            int S = 0;
            int it = 1;
            while (1) {
                int nx = upper_bound(b + 1, b + 1 + *b, S + 1) - b;
                --nx;
                int add = seg.query(seg.rt[l], seg.rt[r], 1, m, it, nx);
                if (!add)
                    break;
                S += add;
                it = nx + 1;
            }
            printf("%d\n", S + 1);
        }
    }
    return 0;
}
