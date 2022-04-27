#include <bits/stdc++.h>
using namespace std;

#define N 10010
int n, m, t, a[N], b[N], H[N];
// 0 表示是第一个数
// 1 表示当前数等于之前那个数
// 2 表示当前数小于之前那个数
// 3 表示当前数大于之前那个数
int g[N][4], f[4];

struct BIT

        struct SEG {
    int t[N << 1];
    void build(int id, int l, int r) {
        t[id] = 0;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int pos, int x) {
        if (l == r) {
            t[id] = max(t[id], x);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, x);
        else
            update(id << 1 | 1, mid + 1, r, pos, x);
        t[id] = max(t[id << 1], t[id << 1 | 1]);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (ql > qr)
            return 0;
        if (l >= ql && r <= qr) {
            return t[id];
        }
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res = max(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg[4];

int get(int x) {
    return lower_bound(H + 1, H + 1 + t, x) - H;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(g, 0, sizeof g);
        t = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i) {
            scanf("%d", b + i);
            H[++t] = b[i];
        }
        sort(H + 1, H + 1 + t);
        t = unique(H + 1, H + 1 + t) - H - 1;
        int tmp = 0;
        for (int i = 1; i <= n; ++i) {
            int pos = get(a[i]);
            if (H[pos] == a[i]) {
                a[++tmp] = pos;
            }
        }
        n = tmp;
        for (int i = 1; i <= m; ++i) b[i] = get(b[i]);
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 4; ++j) {
            }
            for (int j = 1; j <= m; ++j) {
                for (int k = 0; k < 4; ++k) {
                    f[k] = g[j][k];
                }
                if (a[i] == b[j]) {
                    g[j][0] = 1;
                    for (int k = 1, x, l, r; k <= 3; ++k) {
                        switch (k) {
                            case 1:
                                l = b[j] + 1, r = t;
                                break;
                            case 2:
                                l = b[j], r = b[j];
                                break;
                            case 3:
                                l = 1, r = b[j] - 1;
                                break;
                        }
                        x = seg[0].query(1, 1, t, l, r);
                        if (k == 2) {
                            ++x;
                            g[j][k] = max(g[j][k], x);
                            continue;
                        }
                        for (int _ = 1; _ <= 3; ++_)
                            if (k != _) {
                                x = max(x, seg[_].query(1, 1, t, l, r));
                            }
                        ++x;
                        g[j][k] = max(g[j][k], x);
                    }
                }
                for (int k = 0; k < 4; ++k) {
                    res = max(res, g[j][k]);
                    seg[k].update(1, 1, t, b[j], f[k]);
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
