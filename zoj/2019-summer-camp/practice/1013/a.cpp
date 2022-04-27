#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
int n, m;
struct node {
    int l, r;
    ll k, b;
    node() {}
    node(int l, int r, ll k, ll b) : l(l), r(r), k(k), b(b) {}
};
vector<vector<node>> G;
ll dist[N];

struct SEG {
    struct node {
        bool F;
        ll k, b, Min;
        int l, r, Minid;
        node() {
            F = 0;
            k = 0;
            b = INFLL;
            Min = INFLL;
            Minid = -1;
            l = -1;
            r = -1;
        }
        ll gety(ll x) {
            return k * x + b;
        }
        void pushup(node ls, node rs) {
            if (ls.l == -1 && rs.l == -1) {
                l = r = -1;
            } else if (ls.l == -1) {
                l = rs.l;
                r = rs.r;
            } else if (rs.l == -1) {
                l = ls.l;
                r = ls.r;
            } else {
                l = ls.l;
                r = rs.r;
            }
            Min = INFLL;
            Minid = -1;
            if (ls.Min < rs.Min) {
                Min = ls.Min;
                Minid = ls.Minid;
            } else {
                Min = rs.Min;
                Minid = rs.Minid;
            }
            if (F) {
                if (l != -1) {
                    if (gety(l) < Min) {
                        Min = gety(l);
                        Minid = l;
                    }
                    if (gety(r) < Min) {
                        Min = gety(r);
                        Minid = r;
                    }
                }
            }
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id] = node();
            t[id].l = t[id].r = l;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id].pushup(t[id << 1], t[id << 1 | 1]);
    }
    void update(int id, int l, int r, ll k, ll b) {
        if (l == r) {
            if (t[id].l == -1)
                return;
            if (k * l + b < t[id].Min) {
                t[id].F = 1;
                t[id].k = k;
                t[id].b = b;
                t[id].Min = k * l + b;
                t[id].Minid = l;
                t[id].l = t[id].r = l;
            }
            return;
        }
        if (!t[id].F) {
            t[id].F = 1;
            t[id].k = k;
            t[id].b = b;
            t[id].pushup(t[id << 1], t[id << 1 | 1]);
            return;
        }
        int mid = (l + r) >> 1;
        ll kk = t[id].k, bb = t[id].b;
        ll l1 = 1ll * l * kk + bb, r1 = 1ll * r * kk + bb;
        ll l2 = 1ll * l * k + b, r2 = 1ll * r * k + b;
        if (l1 <= l2 && r1 <= r2)
            return;
        if (l2 < l1 && r2 < r1) {
            t[id].k = k;
            t[id].b = b;
            t[id].pushup(t[id << 1], t[id << 1 | 1]);
            return;
        }
        ll x = (bb - b) / (k - kk);
        if (x <= mid) {
            if (l1 < l2) {
                update(id << 1, l, mid, t[id].k, t[id].b);
                t[id].k = k;
                t[id].b = b;
            } else {
                update(id << 1, l, mid, k, b);
            }
        } else {
            if (l1 < l2) {
                update(id << 1 | 1, mid + 1, r, k, b);
            } else {
                update(id << 1 | 1, mid + 1, r, t[id].k, t[id].b);
                t[id].k = k;
                t[id].b = b;
            }
        }
        t[id].pushup(t[id << 1], t[id << 1 | 1]);
    }
    void update(int id, int l, int r, int ql, int qr, ll k, ll b) {
        if (l >= ql && r <= qr) {
            update(id, l, r, k, b);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, k, b);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, k, b);
        t[id].pushup(t[id << 1], t[id << 1 | 1]);
    }
    void del(int id, int l, int r, int pos) {
        if (l == r) {
            t[id].k = 0;
            t[id].b = INFLL;
            t[id].Min = INFLL;
            t[id].Minid = -1;
            t[id].l = t[id].r = -1;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            del(id << 1, l, mid, pos);
        else
            del(id << 1 | 1, mid + 1, r, pos);
        t[id].pushup(t[id << 1], t[id << 1 | 1]);
    }
} seg;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, x, l, r; i <= m; ++i) {
            ll k, b;
            scanf("%d%d%d%lld%lld", &x, &l, &r, &b, &k);
            G[x].emplace_back(l, r, k, b - 1ll * l * k);
        }
        seg.build(1, 1, n);
        seg.update(1, 1, n, 1, 1, 0, 0);
        fill(dist + 1, dist + 1 + n, -1);
        for (int i = 0; i < n; ++i) {
            int u = seg.t[1].Minid;
            if (u == -1 || seg.t[1].Min == INFLL)
                break;
            dist[u] = seg.t[1].Min;
            for (auto it : G[u]) {
                seg.update(1, 1, n, it.l, it.r, it.k, it.b + dist[u]);
            }
            seg.del(1, 1, n, u);
        }
        for (int i = 1; i <= n; ++i) printf("%lld ", dist[i]);
        puts("");
    }
    return 0;
}
