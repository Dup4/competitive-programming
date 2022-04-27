#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, q, a[N], rt[N];

struct SEG {
    struct node {
        int ls, rs, x;
        node() {}
        void init() {
            ls = rs = x = 0;
        }
    } t[N * 40];
    int tot;
    int newnode() {
        ++tot;
        t[tot].init();
        return tot;
    }
    void init() {
        tot = 0;
    }
    void build(int &id, int l, int r) {
        if (!id)
            id = newnode();
        if (l == r) {
            t[id].x = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(t[id].ls, l, mid);
        build(t[id].rs, mid + 1, r);
    }
    void update(int &now, int pre, int l, int r, int pos, int x) {
        now = newnode();
        t[now] = t[pre];
        if (l == r) {
            t[now].x = x;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, t[pre].ls, l, mid, pos, x);
        else
            update(t[now].rs, t[pre].rs, mid + 1, r, pos, x);
    }
    int query(int now, int l, int r, int pos) {
        if (l == r)
            return t[now].x;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return query(t[now].ls, l, mid, pos);
        else
            return query(t[now].rs, mid + 1, r, pos);
    }
} seg;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        seg.build(rt[0], 1, n);
        for (int i = 1, back, op, x, y; i <= q; ++i) {
            scanf("%d%d%d", &back, &op, &x);
            rt[i] = rt[back];
            if (op == 1) {
                scanf("%d", &y);
                seg.update(rt[i], rt[i], 1, n, x, y);
            } else if (op == 2) {
                printf("%d\n", seg.query(rt[i], 1, n, x));
            }
        }
    }
    return 0;
}
