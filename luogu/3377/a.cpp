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
        //小根堆，维护左儿子最小, 用大于号
        bool operator<(const node &other) const {
            if (w != other.w)
                return w > other.w;
            return id > other.id;
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
        //小根堆的排序规则
        if (a[A] < a[B])
            swap(A, B);
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
    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (sze[fx] > sze[fy])
                swap(fx, fy);
            fa[fx] = fy;
            sze[fy] += sze[fx];
            rt[fy] = lt.merge(rt[fx], rt[fy]);
        }
    }
} ufs;

int n, q, a[N], dead[N];

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        memset(dead, 0, sizeof dead);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        ufs.init(n, a);
        int op, x, y;
        while (q--) {
            scanf("%d%d", &op, &x);
            if (op == 1) {
                scanf("%d", &y);
                if (dead[x] + dead[y] == 0)
                    ufs.merge(x, y);
            } else {
                if (dead[x]) {
                    puts("-1");
                } else {
                    int fx = ufs.find(x);
                    pII tmp = lt.del(ufs.rt[fx]);
                    printf("%d\n", tmp.fi);
                    dead[tmp.se] = 1;
                }
            }
        }
    }
    return 0;
}
