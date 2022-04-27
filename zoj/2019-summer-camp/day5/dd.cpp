#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define N 300010
int n, q, a[N];
map<ull, int> mp;
ull base[N], Hashsum;

struct SEG {
    struct node {
        int a, ls, rs;
        node() {
            ls = rs = -1;
        }
        node(int a, int ls, int rs) : a(a), ls(ls), rs(rs) {}
    } t[N * 50];
    int rt[N * 10], tot;
    void init() {
        rt[0] = 0;
        tot = 0;
    }
    void build(int &id, int l, int r) {
        id = ++tot;
        if (l == r) {
            t[id] = node();
            t[id].a = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(t[id].ls, l, mid);
        build(t[id].rs, mid + 1, r);
    }
    void update(int &now, int pre, int l, int r, int pos, int x) {
        now = ++tot;
        t[now] = t[pre];
        if (l == r) {
            t[now].a = x;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, t[pre].ls, l, mid, pos, x);
        else
            update(t[now].rs, t[pre].rs, mid + 1, r, pos, x);
    }
    int query(int id, int l, int r, int pos) {
        if (l == r)
            return t[id].a;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return query(t[id].ls, l, mid, pos);
        else
            return query(t[id].rs, mid + 1, r, pos);
    }
} seg;

int main() {
    ull tmp = 31;
    Hashsum = 0;
    for (int i = 1; i <= 100000; ++i) {
        base[i] = tmp;
        tmp *= 31;
    }
    while (scanf("%d%d", &n, &q) != EOF) {
        mp.clear();
        seg.init();
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= n; ++i) {
            Hashsum = base[i] * a[i];
        }
        seg.build(seg.rt[0], 1, n);
        int P = 1, st = 1, ed = 1;
        mp[Hashsum] = 1;
        while (1) {
            int it = 1;
            vector<pii> vec;
            while (1) {
                vec.push_back(pii(it, a[it]));
                int ls = it * 2, rs = it * 2 + 1;
                if (ls > n)
                    break;
                if (a[ls] > a[rs]) {
                    it = ls;
                } else {
                    it = rs;
                }
            }
            for (auto it : vec) {
                Hashsum -= base[it.fi] * it.se;
            }
            int sze = (int)vec.size();
            for (int i = 0; i < sze - 1; ++i) {
                a[vec[i].fi] = vec[i + 1].se;
            }
            a[vec.end()[-1].fi] = vec[0].se;
            for (auto it : vec) {
                Hashsum += base[it.fi] * a[it.fi];
            }
            if (mp.find(Hashsum) != mp.end()) {
                st = mp[Hashsum], ed = P;
                break;
            }
            seg.rt[P] = seg.rt[P - 1];
            for (auto it : vec) {
                seg.update(seg.rt[P], seg.rt[P], 1, n, it.fi, a[it.fi]);
            }
            ++P;
            mp[Hashsum] = P;
        }
        ll m;
        int x;
        for (int i = 1; i <= q; ++i) {
            scanf("%lld%d", &m, &x);
            ++m;
            if (m <= st) {
                printf("%d ", seg.query(seg.rt[m - 1], 1, n, x));
            } else {
                m -= st;
                m %= (ed - st + 1);
                printf("%d ", seg.query(seg.rt[st + m - 1], 1, n, x));
            }
        }
        puts("");
    }
    return 0;
}
