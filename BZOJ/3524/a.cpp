#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, q, m, a[N];

struct Hash {
    vector<int> a;
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int get(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hs;

struct SEG {
    struct node {
        int ls, rs, cnt;
        void init() {
            ls = rs = cnt = 0;
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
    void up(int id) {
        int ls = t[id].ls, rs = t[id].rs;
        t[id].cnt = 0;
        if (ls)
            t[id].cnt += t[ls].cnt;
        if (rs)
            t[id].cnt += t[rs].cnt;
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
        if (l == r) {
            t[now].cnt += v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, t[pre].ls, l, mid, pos, v);
        else
            update(t[now].rs, t[pre].rs, mid + 1, r, pos, v);
        up(now);
    }
    int query(int tl, int tr, int l, int r, int cnt) {
        if (l == r)
            return l - 1;
        int mid = (l + r) >> 1;
        int lsum = t[t[tr].ls].cnt - t[t[tl].ls].cnt;
        int rsum = t[t[tr].rs].cnt - t[t[tl].rs].cnt;
        if (lsum > cnt) {
            return query(t[tl].ls, t[tr].ls, l, mid, cnt);
        } else if (rsum > cnt) {
            return query(t[tl].rs, t[tr].rs, mid + 1, r, cnt);
        } else {
            return -1;
        }
    }
} seg;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        hs.init();
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), hs.add(a[i]);
        hs.gao();
        m = hs.a.size();
        for (int i = 1; i <= n; ++i) a[i] = hs.get(a[i]);
        seg.init();
        seg.build(seg.rt[0], 1, m);
        for (int i = 1; i <= n; ++i) seg.update(seg.rt[i], seg.rt[i - 1], 1, m, a[i], 1);
        for (int i = 1, l, r; i <= q; ++i) {
            scanf("%d%d", &l, &r);
            int ans = seg.query(seg.rt[l - 1], seg.rt[r], 1, m, (r - l + 1) >> 1);
            if (ans == -1)
                ans = 0;
            else
                ans = hs.a[ans];
            printf("%d\n", ans);
        }
    }
    return 0;
}
