#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define ll long long
#define N 500010
int n, q, a[N];

struct SEG {
    struct node {
        // 0 加上一个数
        // 1 小于x的数变成x
        // 2 大于x的数变成x
        ll sum, lazy[3], Max[2], Min[2];
        int Max_num, Min_num, tot_num;
        node() {
            Max_num = Min_num = tot_num = 0;
            sum = lazy[0] = 0;
            lazy[1] = -INF;
            lazy[2] = INF;
            Max[0] = -INF, Max[1] = -INF;
            Min[0] = INF;
            Min[1] = INF;
        }
        //加上一个数
        void add(ll x) {
            sum += x * tot_num;
            lazy[0] += x;
            for (int i = 0; i < 2; ++i) {
                Max[i] += x;
                Min[i] += x;
            }
        }
        // 小于x的数变成x
        void add1(ll x) {
            if (x <= Min[0]) {
                return;
            } else {
                sum += 1ll * Min_num * (x - Min[0]);
                Min[0] = x;
                lazy[1] = x;
            }
        }
        // 大于x的数变成x
        void add2(ll x) {
            if (x >= Max[0]) {
                return;
            } else {
                sum += 1ll * Max_num * (x - Max[0]);
                Max[0] = x;
                lazy[2] = x;
            }
        }
        node operator+(const node &other) const {
            node res = node();
            res.sum = sum + other.sum;
            res.tot_num = tot_num + other.tot_num;
            if (Max[0] == other.Max[0]) {
                res.Max[0] = Max[0];
                res.Max_num = Max_num + other.Max_num;
                if (res.Max_num == tot_num) {
                    res.Max[1] = -INF;
                } else {
                    res.Max[1] = max(Max[1], other.Max[1]);
                }
            } else {
                if (Max[0] > other.Max[0]) {
                    res.Max[0] = Max[0];
                    res.Max_num = Max_num;
                    res.Max[1] = max(Max[1], other.Max[0]);
                } else {
                    res.Max[0] = other.Max[0];
                    res.Max_num = other.Max_num;
                    res.Max[1] = max(other.Max[1], Max[0]);
                }
            }
            if (Min[0] == other.Min[0]) {
                res.Min[0] = Min[0];
                res.Min_num = Min_num + other.Min_num;
                if (res.Min_num == tot_num) {
                    res.Min[1] = INF;
                } else {
                    res.Min[1] = min(Min[1], other.Min[1]);
                }
            } else {
                if (Min[0] < other.Min[0]) {
                    res.Min[0] = Min[0];
                    res.Min_num = Min_num;
                    res.Min[1] = min(Min[1], other.Min[0]);
                } else {
                    res.Min[0] = other.Min[0];
                    res.Min_num = other.Min_num;
                    res.Min[1] = min(other.Min[1], Min[0]);
                }
            }
            return res;
        }
    } t[N * 3], res;
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = node();
            t[id].tot_num = t[id].Max_num = t[id].Min_num = 1;
            t[id].Max[0] = t[id].Min[0] = t[id].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void pushdown(int id) {
        if (t[id].lazy[0] != 0) {
            ll &lazy = t[id].lazy[0];
            t[id << 1].add(lazy);
            t[id << 1 | 1].add(lazy);
            lazy = 0;
        }
        if (t[id].lazy[1] != -INF) {
            ll &lazy = t[id].lazy[1];
            t[id << 1].add1(lazy);
            t[id << 1 | 1].add1(lazy);
            lazy = -INF;
        }
        if (t[id].lazy[2] != INF) {
            ll &lazy = t[id].lazy[2];
            t[id << 1].add2(lazy);
            t[id << 1 | 1].add2(lazy);
            lazy = INF;
        }
    }
    void update(int id, int l, int r, int ql, int qr, int x) {
        if (l >= ql && r <= qr) {
            t[id].add(x);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, x);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update1(int id, int l, int r, int ql, int qr, int x) {
        if (x <= t[id].Min[0])
            return;
        if (l == r) {
            x = max(1ll * x, t[id].sum);
            t[id].sum = x;
            t[id].tot_num = 1;
            t[id].Min[0] = x;
            t[id].Min[1] = INF;
            t[id].Min_num = 1;
            t[id].Max[0] = x;
            t[id].Max[1] = -INF;
            t[id].Max_num = 1;
            return;
        }
        if (l >= ql && r <= qr) {
            if (x > t[id].Min[0] && x < t[id].Min[1]) {
                t[id].add1(x);
                return;
            }
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update1(id << 1, l, mid, ql, qr, x);
        if (qr > mid)
            update1(id << 1 | 1, mid + 1, r, ql, qr, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update2(int id, int l, int r, int ql, int qr, int x) {
        if (x >= t[id].Max[0])
            return;
        if (l == r) {
            x = min(1ll * x, t[id].sum);
            t[id].sum = x;
            t[id].tot_num = 1;
            t[id].Min[0] = x;
            t[id].Min[1] = INF;
            t[id].Min_num = 1;
            t[id].Max[0] = x;
            t[id].Max[1] = -INF;
            t[id].Max_num = 1;
            return;
        }
        if (l >= ql && r <= qr) {
            if (x > t[id].Max[1] && x < t[id].Max[0]) {
                t[id].add2(x);
                return;
            }
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update2(id << 1, l, mid, ql, qr, x);
        if (qr > mid)
            update2(id << 1 | 1, mid + 1, r, ql, qr, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            res = res + t[id];
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr);
    }
} seg;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    seg.build(1, 1, n);
    scanf("%d", &q);
    int tp, l, r, x;
    while (q--) {
        scanf("%d%d%d", &tp, &l, &r);
        switch (tp) {
            case 1:
                scanf("%d", &x);
                seg.update(1, 1, n, l, r, x);
                break;
            case 2:
                scanf("%d", &x);
                seg.update1(1, 1, n, l, r, x);
                break;
            case 3:
                scanf("%d", &x);
                seg.update2(1, 1, n, l, r, x);
                break;
            case 4:
                seg.res = SEG::node();
                seg.query(1, 1, n, l, r);
                printf("%lld\n", seg.res.sum);
                break;
            case 5:
                seg.res = SEG::node();
                seg.query(1, 1, n, l, r);
                printf("%lld\n", seg.res.Max[0]);
                break;
            case 6:
                seg.res = SEG::node();
                seg.query(1, 1, n, l, r);
                printf("%lld\n", seg.res.Min[0]);
                break;
        }
    }
    return 0;
}
