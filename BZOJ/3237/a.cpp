#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m, q;
int e[N][2], ans[N], used[N], t_used;

struct qnode {
    int id, c[10];
    void scan(int id) {
        this->id = id;
        scanf("%d", c);
        for (int i = 1; i <= c[0]; ++i) {
            scanf("%d", c + i);
        }
    }
} qrr[N];

struct UFS {
    struct node {
        int fa, sze;
        void init() {
            fa = 0;
            sze = 1;
        }
    } t[N];
    struct BackNode {
        int who;
        node t;
    } Back[N];
    int T;
    void init(int n) {
        T = 0;
        for (int i = 1; i <= n; ++i) t[i].init();
    }
    int find(int x) {
        return t[x].fa == 0 ? x : find(t[x].fa);
    }
    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (t[fx].sze > t[fy].sze)
                swap(fx, fy);
            Back[++T] = {fx, t[fx]};
            Back[++T] = {fy, t[fy]};
            t[fx].fa = fy;
            t[fy].sze += t[fx].sze;
        }
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    void rollback(int _T) {
        while (T != _T) {
            BackNode tmp = Back[T];
            t[tmp.who] = tmp.t;
            --T;
        }
    }
} ufs;

void CDQ(int l, int r) {
    int T = ufs.T;
    if (l > r)
        return;
    if (l == r) {
        int id = qrr[l].id;
        ans[id] = 1;
        for (int i = 1; i <= qrr[l].c[0]; ++i) {
            int now = qrr[l].c[i];
            ans[id] &= ufs.same(e[now][0], e[now][1]);
        }
        return;
    }
    int mid = (l + r) >> 1;
    ++t_used;
    //标记左区间中被删去的边
    for (int i = l; i <= mid; ++i) {
        for (int j = 1; j <= qrr[i].c[0]; ++j) {
            used[qrr[i].c[j]] = t_used;
        }
    }
    //从右区间找左区间中所有询问都存在的边,将它们合并起来
    for (int i = mid + 1; i <= r; ++i) {
        for (int j = 1; j <= qrr[i].c[0]; ++j) {
            int now = qrr[i].c[j];
            if (used[now] != t_used) {
                ufs.merge(e[now][0], e[now][1]);
            }
        }
    }
    CDQ(l, mid);
    ufs.rollback(T);
    ++t_used;
    for (int i = mid + 1; i <= r; ++i) {
        for (int j = 1; j <= qrr[i].c[0]; ++j) {
            used[qrr[i].c[j]] = t_used;
        }
    }
    for (int i = l; i <= mid; ++i) {
        for (int j = 1; j <= qrr[i].c[0]; ++j) {
            int now = qrr[i].c[j];
            if (used[now] != t_used) {
                ufs.merge(e[now][0], e[now][1]);
            }
        }
    }
    CDQ(mid + 1, r);
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        ufs.init(n);
        t_used = 1;
        for (int i = 1; i <= m; ++i) {
            used[i] = 0;
            scanf("%d%d", e[i], e[i] + 1);
        }
        scanf("%d", &q);
        for (int i = 1; i <= q; ++i) {
            qrr[i].scan(i);
            for (int j = 1; j <= qrr[i].c[0]; ++j) {
                used[qrr[i].c[j]] = 1;
            }
        }
        for (int i = 1; i <= m; ++i)
            if (!used[i]) {
                ufs.merge(e[i][0], e[i][1]);
            }
        CDQ(1, q);
        for (int i = 1; i <= q; ++i) {
            if (!ans[i]) {
                puts("Disconnected");
            } else {
                puts("Connected");
            }
        }
    }
    return 0;
}
