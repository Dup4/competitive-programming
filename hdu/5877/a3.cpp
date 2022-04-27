#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
int n, rt, vis[N];
ll a[N], k, res;
vector<vector<int>> G;
struct FHQ {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int son[2], key, rnd, sze;
    } t[N];
    int tot, rt;
    inline void init() {
        tot = rt = 0;
    }
    inline void pushup(int x) {
        t[x].sze = t[ls].sze + t[rs].sze + 1;
    }
    inline int random() {
        static int seed = 703;
        return seed = int(seed * 48217ll % 2147483647);
    }
    inline int newnode(int key) {
        ++tot;
        t[tot].sze = 1;
        t[tot].key = key;
        t[tot].rnd = random();
        t[tot].son[0] = t[tot].son[1] = 0;
        return tot;
    }
    //默认x < y
    //假设第一棵树的权值小于等于第二棵树的权值，那么就比较它们的随机权值
    //如果rnd[l] < rnd[r]，那么保留第一棵树的左子树，另一棵树作为它的右子树
    //如果rnd[l] >= rnd[r]，那么保留第二棵树的右子树，另一棵树作为它的左子树
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
        if (t[x].rnd < t[y].rnd) {
            t[x].son[1] = merge(t[x].son[1], y);
            pushup(x);
            return x;
        } else {
            t[y].son[0] = merge(x, t[y].son[0]);
            pushup(y);
            return y;
        }
    }
    //以权值key分离now成x, y
    void split(int now, int key, int &x, int &y) {
        if (!now)
            x = y = 0;
        else {
            //将所有权值小于等于key的保留在左边
            if (t[now].key <= key) {
                x = now;
                split(t[now].son[1], key, t[now].son[1], y);
                //权值大于key的去右边
            } else {
                y = now;
                split(t[now].son[0], key, x, t[now].son[0]);
            }
            pushup(now);
        }
        //最终得到的根为x的树，里面的权值是小于key的
        //得到的根为y的树，里面的权值是大于key的
    }
    //查询key的排名，若有多个相同的数，输出最大的排名
    //按照key - 1将树分成x, y两棵，那么x树中最大的权值应该小于等于a - 1, 那么a的排名就是sze[x] + 1
    inline int getRank(int key) {
        int x, y;
        split(rt, key, x, y);
        int res = t[x].sze;
        rt = merge(x, y);
        return res;
    }
    //插入一个数key
    //先按权值key将树分成两段，x树中是权值小于等于key的，y树中是权值大于key的
    //那么新建一个节点z，它的权值为key，那么先将x, z合并起来，再将x和y合并起来
    inline void insert(int key) {
        int x, y;
        split(rt, key, x, y);
        rt = merge(merge(x, newnode(key)), y);
    }
} fhq;
void DFS(int u) {
    fhq.insert(a[u]);
    ll t;
    if (a[u] == 0)
        t = 1e9;
    else
        t = k / a[u];
    t = min(t, 1000000000ll);
    res -= fhq.getRank(t);
    for (auto &v : G[u]) DFS(v);
    res += fhq.getRank(t);
}

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%lld", &n, &k);
        G.clear();
        G.resize(n + 1);
        memset(vis, 0, sizeof vis);
        res = 0;
        fhq.init();
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            vis[v] = 1;
        }
        for (int i = 1; i <= n; ++i)
            if (!vis[i])
                rt = i;
        DFS(rt);
        printf("%lld\n", res);
    }
    return 0;
}
