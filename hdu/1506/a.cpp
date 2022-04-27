#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, a[N];
ll res;

struct Cartesian_Tree {
    struct node {
        int id, val, fa;
        int son[2];
        node() {}
        node(int id, int val, int fa) : id(id), val(val), fa(fa) {
            son[0] = son[1] = 0;
        }
        bool operator<(const node &other) const {
            return id < other.id;
        }
    } t[N];
    int root, stk[N], top;
    void init() {
        t[0] = node(0, 0, 0);
    }
    //这里建的是小根堆
    void build(int n, int *a) {
        for (int i = 1; i <= n; ++i) {
            t[i] = node(i, a[i], 0);
        }
        for (int i = 1; i <= n; ++i) {
            int k = i - 1;

            //一直找到比i位置小的位置k
            while (t[k].val > t[i].val) {
                k = t[k].fa;
            }

            //将父节点的右子树放到自己的左子树上
            t[i].son[0] = t[k].son[1];

            //父节点的右子树重新指向
            t[k].son[1] = i;

            //设置i的父节点
            t[i].fa = k;

            //设置父节点的父亲
            t[t[i].son[0]].fa = i;
        }
        root = t[0].son[1];
    }
    int DFS(int u) {
        if (!u)
            return 0;
        int sze = DFS(t[u].son[0]) + DFS(t[u].son[1]) + 1;
        res = max(res, 1ll * sze * t[u].val);
        return sze;
    }
    void print(int u) {
        if (!u)
            return;
        print(t[u].son[0]);
        printf("%d %d\n", t[u].id, t[u].val);
        print(t[u].son[1]);
    }
} CT;

int main() {
    while (scanf("%d", &n), n) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        CT.init();
        CT.build(n, a);
        //	CT.print(CT.root);
        res = 0;
        CT.DFS(CT.root);
        printf("%lld\n", res);
    }
    return 0;
}
