#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10;

struct LeftTree {
    struct node {
        int w, id, lc, rc, h;
        node() {}
        node(int w, int id, int lc, int rc, int h) : w(w), id(id), lc(lc), rc(rc), h(h) {}
        void init() {
            w = id = lc = rc = h = 0;
        }
        bool operator<(const node &other) const {
            if (w != other.w)
                return w < other.w;
            return id < other.id;
        }
    } a[N * 20];
    int tot;
    void init() {
        tot = 0;
    }
    int newnode() {
        ++tot;
        a[tot].init();
        return tot;
    }
    //合并操作
    int merge(int A, int B) {
        if (!A || !B)
            return A + B;
        if (a[A] < a[B])
            swap(A, B);
        // if (a[A].w < a[B].w || (a[A].w == a[B].w && a[A].id < a[B].id)) swap(A, B);
        a[A].rc = merge(a[A].rc, B);
        if (a[a[A].lc].h < a[a[A].rc].h)
            swap(a[A].lc, a[A].rc);
        if (a[A].rc)
            a[A].h = a[a[A].rc].h + 1;
        else
            a[A].h = 0;
        return A;
    }
    void insert(int &A, int x, int id) {
        int tmp = newnode();
        a[tmp] = node(x, id, 0, 0, 0);
        if (A)
            A = merge(A, tmp);
        else
            A = tmp;
    }
    //删除堆顶的数
    pII del(int &A) {
        pII res = pII(a[A].w, a[A].id);
        A = merge(a[A].lc, a[A].rc);
        return res;
    }
} lt;

struct UFS {
    int fa[N], sze[N], rt[N];
    void init(int n, int *a) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = 0;
            sze[i] = 1;
            rt[i] = 0;
            lt.insert(rt[i], a[i], i);
        }
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    int merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (sze[fx] > sze[fy])
                swap(fx, fy);
            fa[fx] = fy;
            sze[fy] += sze[fx];
            pII X = pII(lt.a[rt[fx]].w, lt.a[rt[fx]].id);
            pII Y = pII(lt.a[rt[fy]].w, lt.a[rt[fy]].id);
            X.fi /= 2;
            Y.fi /= 2;
            lt.del(rt[fx]);
            lt.del(rt[fy]);
            lt.insert(rt[fx], X.fi, X.se);
            lt.insert(rt[fy], Y.fi, Y.se);
            rt[fy] = lt.merge(rt[fx], rt[fy]);
            return lt.a[rt[fy]].w;
        }
        return -1;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
} ufs;

int n, q, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        lt.init();
        ufs.init(n, a);
        scanf("%d", &q);
        for (int i = 1, x, y; i <= q; ++i) {
            scanf("%d%d", &x, &y);
            printf("%d\n", ufs.merge(x, y));
        }
    }
    return 0;
}
