#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define INF 0x3f3f3f3f
int n, a[N];
ll res;

struct Cartesian_Tree {
    struct node {
        int id, val, fa;
        // 0 前缀最值
        // 1 后缀最值
        ll Min[2], Max[2], sum;
        int son[2];
        node() {}
        node(int id, int val, int fa) : id(id), val(val), fa(fa) {
            memset(son, 0, sizeof son);
            memset(Min, 0, sizeof Min);
            memset(Max, 0, sizeof Max);
            sum = 0;
        }
        bool operator<(const node &other) const {
            return id < other.id;
        }

    } t[N];
    int root;
    void init() {
        t[0] = node(0, -INF, 0);
    }
    void build(int n, int *a) {
        for (int i = 1; i <= n; ++i) {
            t[i] = node(i, a[i], 0);
        }
        for (int i = 1; i <= n; ++i) {
            int k = i - 1;

            while (t[k].val > t[i].val) {
                k = t[k].fa;
            }

            t[i].son[0] = t[k].son[1];
            t[k].son[1] = i;
            t[i].fa = k;
            t[t[i].son[0]].fa = i;
        }
        root = t[0].son[1];
    }
    void DFS(int u) {
        if (!u)
            return;
        int ls = t[u].son[0], rs = t[u].son[1];
        DFS(ls);
        DFS(rs);
        res = max(res, t[u].val * (t[u].val + t[ls].Min[1] + t[rs].Min[0]));
        res = max(res, t[u].val * (t[u].val + t[ls].Max[1] + t[rs].Max[0]));
        t[u].sum = t[ls].sum + t[rs].sum + t[u].val;
        t[u].Min[0] = min(t[ls].Min[0], t[ls].sum + t[u].val + t[rs].Min[0]);
        t[u].Min[1] = min(t[rs].Min[1], t[rs].sum + t[u].val + t[ls].Min[1]);
        t[u].Max[0] = max(t[ls].Max[0], t[ls].sum + t[u].val + t[rs].Max[0]);
        t[u].Max[1] = max(t[rs].Max[1], t[rs].sum + t[u].val + t[ls].Max[1]);
    }
} CT;

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        res = -1e18;
        CT.init();
        CT.build(n, a);
        CT.DFS(CT.root);
        printf("%lld\n", res);
    }
    return 0;
}
