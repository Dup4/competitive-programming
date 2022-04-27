#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 2e5 + 10;
int n, q;

struct SEG {
    struct node {
        int ls, rs, fa, sze;
        node() {}
        void init() {
            ls = rs = fa = 0;
            sze = 1;
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
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(t[id].ls, l, mid);
        build(t[id].rs, mid + 1, r);
    }
    void update(int &now, int pre, int l, int r, int pos, int fa, int sze) {
        now = newnode();
        t[now] = t[pre];
        if (l == r) {
            t[now].fa = fa;
            t[now].sze = sze;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, t[pre].ls, l, mid, pos, fa, sze);
        else
            update(t[now].rs, t[pre].rs, mid + 1, r, pos, fa, sze);
    }
    // fi 父亲 se 子树大小
    pII query(int now, int l, int r, int pos) {
        if (l == r)
            return pII(t[now].fa, t[now].sze);
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return query(t[now].ls, l, mid, pos);
        else
            return query(t[now].rs, mid + 1, r, pos);
    }
} seg;

struct UFS {
    int segrt;
    UFS() {}
    UFS(int segrt) : segrt(segrt) {}
    pII find(int x) {
        pII pre = seg.query(segrt, 1, n, x);
        if (pre.fi == 0) {
            return pII(x, pre.se);
        } else {
            return find(pre.fi);
        }
    }
    void merge(int x, int y) {
        pII fx = find(x), fy = find(y);
        if (fx.fi != fy.fi) {
            if (fx.se > fy.se)
                swap(fx, fy);
            seg.update(segrt, segrt, 1, n, fx.fi, fy.fi, fx.se);
            seg.update(segrt, segrt, 1, n, fy.fi, 0, fx.se + fy.se);
        }
    }
    bool same(int x, int y) {
        pII fx = find(x), fy = find(y);
        return fx.fi == fy.fi;
    }
} ufs[N];

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        seg.init();
        ufs[0] = UFS(0);
        seg.build(ufs[0].segrt, 1, n);
        int op, x, y, k;
        for (int i = 1; i <= q; ++i) {
            scanf("%d", &op);
            ufs[i] = ufs[i - 1];
            switch (op) {
                case 1:
                    scanf("%d%d", &x, &y);
                    ufs[i].merge(x, y);
                    break;
                case 2:
                    scanf("%d", &k);
                    ufs[i].segrt = ufs[k].segrt;
                    break;
                case 3:
                    scanf("%d%d", &x, &y);
                    puts(ufs[i].same(x, y) ? "1" : "0");
                    break;
            }
        }
    }
    return 0;
}
