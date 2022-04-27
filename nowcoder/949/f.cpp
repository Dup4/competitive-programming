#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, b[N], tot, res[N];
struct node {
    int x, y, id;
    node() {}
    void scan(int id) {
        this->id = id;
        scanf("%d%d", &x, &y);
        b[++tot] = y;
    }
    bool operator<(const node &other) const {
        if (x != other.x)
            return x > other.x;
        return y < other.y;
    }
} a[N];
void Hash() {
    sort(b + 1, b + 1 + tot);
    tot = unique(b + 1, b + 1 + tot) - b - 1;
    for (int i = 1; i <= n; ++i) {
        a[i].y = lower_bound(b + 1, b + 1 + tot, a[i].y) - b;
    }
}

struct SEG {
    int a[N << 2];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int id, int l, int r, int pos, int v) {
        if (l == r) {
            a[id] = max(a[id], v);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, v);
        else
            update(id << 1 | 1, mid + 1, r, pos, v);
        a[id] = max(a[id << 1], a[id << 1 | 1]);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (ql > qr)
            return 0;
        if (l >= ql && r <= qr)
            return a[id];
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res = max(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg;

int main() {
    while (scanf("%d", &n) != EOF) {
        tot = 0;
        for (int i = 1; i <= n; ++i) a[i].scan(i);
        Hash();
        seg.init();
        sort(a + 1, a + 1 + n);
        for (int i = 1; i <= n; ++i) {
            res[a[i].id] = seg.query(1, 1, tot, a[i].y + 1, tot) + 1;
            seg.update(1, 1, tot, a[i].y, res[a[i].id]);
        }
        for (int i = 1; i <= n; ++i) printf("%d\n", res[i]);
    }
    return 0;
}
