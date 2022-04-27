#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;

struct SEG2 {
    struct node {
        int ls, rs;
        ll sum, sze, cnt;
        ll a, b;
        node() {}
        void init() {
            ls = rs = 0;
            sum = sze = cnt = a = b = 0;
        }
        void add(ll _a, ll _b) {
            sum += _a * sze + _b * cnt;
            a += _a;
            b += _b;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sze = sze + other.sze;
            res.cnt = cnt + other.cnt + sze * other.sze;
            res.sum = sum + other.sum;
            return res;
        }
    } t[N * 20];
    int tot;
    void init() {
        tot = 0;
        t[0].init();
    }
    int newnode(int l, int r) {
        ++tot;
        t[tot].init();
        t[tot].return tot;
    }
    void pushdown(int id) {
        ll &a = t[id].a, &b = t[id].b;
        if (a == 0 && b == 0)
            return;
        t[id << 1].add(a, b);
        a += b * (t[id << 1].sze);
        t[id << 1 | 1].add(a, b);
        a = 0, b = 0;
    }
    void update(int id, int l, int r, int ql, int qr, ll a, ll b) {
        if (l >= ql && r <= qr) {
            t[id].add(a + b * (l - ql), b);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, a, b);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, a, b);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    ll query(int id, int l, int r, int pos) {
        if (l == r)
            return t[id].sum;
        int mid = (l + r) >> 1;
        pushdown(id);
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} seg;

int main() {
    return 0;
}
