#include <bits/stdc++.h>
using namespace std;

#define N 2000010
#define pii pair<int, int>
#define fi first
#define se second
struct SEG {
    struct node {
        int x, y;
        node() {
            x = 0;
            y = -1;
        }
        node(int x, int y) : x(x), y(y) {}
        node operator+(const node &other) const {
            if (x > other.x) {
                return *this;
            } else {
                return other;
            }
        }
    } a[N << 2], res;
    void build(int id, int l, int r) {
        if (l == r) {
            a[id] = node(0, l);
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        a[id] = a[id << 1] + a[id << 1 | 1];
    }
    void update(int id, int l, int r, int pos, node tmp) {
        if (l == r) {
            a[id] = a[id] + tmp;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, tmp);
        else
            update(id << 1 | 1, mid + 1, r, pos, tmp);
        a[id] = a[id << 1] + a[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            res = res + a[id];
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr);
        a[id] = a[id << 1] + a[id << 1 | 1];
    }
} seg;
int n, m, a[N], b[N], f[N], g[N];
void Hash() {
    for (int i = 1; i <= m; ++i) {
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + m);
    b[0] = unique(b + 1, b + 1 + m) - b - 1;
    for (int i = 1; i <= m; ++i) {
        a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
    }
}

void out() {
    int pos = -1;
    for (int i = m; i >= 1; --i) {
        if (f[i] == 2 * n) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        puts("IMPOSSIBLE");
        return;
    }
    vector<int> res;
    while (pos != -1) {
        res.push_back(pos);
        pos = g[pos];
    }
    reverse(res.begin(), res.end());
    for (int i = 0; i < 2 * n; ++i) {
        printf("%d%c", res[i], " \n"[i == 2 * n - 1]);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        m = n * (n + 1);
        for (int i = 1; i <= m; ++i) {
            scanf("%d", a + i);
        }
        Hash();
        seg.build(1, 1, b[0]);
        for (int i = 1; i <= m; ++i) {
            seg.res = SEG::node();
            seg.query(1, 1, b[0], 1, a[i]);
            f[i] = seg.res.x + 1;
            g[i] = seg.res.y;
            if (f[i] == 1)
                g[i] = -1;
            if (f[i] == 2 * n)
                break;
            seg.update(1, 1, b[0], a[i], SEG::node(f[i], i));
        }
        out();
    }
    return 0;
}
