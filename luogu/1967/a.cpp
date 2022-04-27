#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10;
#define pii pair<int, int>
#define fi first
#define se second
int n, m, q;
struct SEG {
    struct node {
        int ls, rs;
        int fa, sze;
        node() {
            ls = rs = 0;
            fa = 0;
            sze = 1;
        }
    } t[N * 50];
    int rt[N], tot;
    void init() {
        tot = 0;
        memset(rt, 0, sizeof rt);
        t[0] = node();
    }
    void build(int &id, int l, int r) {
        if (id == 0) {
            id = ++tot;
        }
        if (l == r) {
            t[id] = node();
            t[id].fa = l;
            return;
        }
        int mid = (l + r) >> 1;
        build(t[id].ls, l, mid);
        build(t[id].rs, mid + 1, r);
    }
    //更改父亲
    void update(int &now, int pre, int l, int r, int pos, int fa) {
        //保留副本，防止now和pre一样的时候，改掉now，而获取不到pre的值
        int tmp = ++tot;
        if (l == r) {
            t[tmp] = node();
            t[tmp].fa = fa;
            t[tmp].sze = t[pre].sze;
            now = tmp;
            return;
        }
        t[tmp].ls = t[pre].ls;
        t[tmp].rs = t[pre].rs;
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            update(t[tmp].ls, t[pre].ls, l, mid, pos, fa);
        } else {
            update(t[tmp].rs, t[pre].rs, mid + 1, r, pos, fa);
        }
        now = tmp;
    }
    //更改子树大小
    void add(int &now, int pre, int l, int r, int pos, int sze) {
        int tmp = ++tot;
        if (l == r) {
            t[tmp] = node();
            t[tmp].fa = t[pre].fa;
            t[tmp].sze = t[pre].sze + sze;
            now = tmp;
            return;
        }
        t[tmp].ls = t[pre].ls;
        t[tmp].rs = t[pre].rs;
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            add(t[tmp].ls, t[pre].ls, l, mid, pos, sze);
        } else {
            add(t[tmp].rs, t[pre].rs, mid + 1, r, pos, sze);
        }
        now = tmp;
    }
    pii query(int now, int l, int r, int pos) {
        if (l == r) {
            return pii(t[now].fa, t[now].sze);
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            return query(t[now].ls, l, mid, pos);
        } else {
            return query(t[now].rs, mid + 1, r, pos);
        }
    }
} seg;
pii find(int k, int x) {
    pii pre = seg.query(seg.rt[k], 1, n, x);
    if (pre.fi == x) {
        return pre;
    } else {
        return find(k, pre.fi);
    }
}
void join(int k, int x, int y) {
    pii fx = find(k, x), fy = find(k, y);
    if (fx.fi != fy.fi) {
        //启发式合并
        if (fx.se > fy.se) {
            swap(fx, fy);
        }
        seg.update(seg.rt[k], seg.rt[k], 1, n, fx.fi, fy.fi);
        seg.add(seg.rt[k], seg.rt[k], 1, n, fy.fi, fx.se);
    }
}
bool same(int k, int x, int y) {
    pii fx = find(k, x), fy = find(k, y);
    return fx.fi == fy.fi;
}
struct Edge {
    int u, v, w;
    void scan() {
        scanf("%d%d%d", &u, &v, &w);
    }
    bool operator<(const Edge &other) const {
        return w > other.w;
    }
} e[N];
int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        seg.init();
        seg.build(seg.rt[0], 1, n);
        for (int i = 1; i <= m; ++i) e[i].scan();
        sort(e + 1, e + 1 + m);
        for (int i = 1; i <= m; ++i) {
            seg.rt[i] = seg.rt[i - 1];
            join(i, e[i].u, e[i].v);
        }
        scanf("%d", &q);
        while (q--) {
            int x, y;
            scanf("%d%d", &x, &y);
            int l = 1, r = m, res = -1;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (same(mid, x, y)) {
                    res = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (res != -1)
                res = e[res].w;
            printf("%d\n", res);
        }
    }
    return 0;
}
