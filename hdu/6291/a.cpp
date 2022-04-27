#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
const int block = 450;
int n, m, arr[N];
vector<vector<int>> G;

namespace DivOnTree {
int deep[N], fa[N], top[N], son[N], sze[N], cnt;
int szeblock[N], Belong[N], dfn[N], dfscnt, dfssize;
stack<int> sta;
void dfs(int u) {
    dfn[u] = ++dfscnt;
    sta.push(u);
    szeblock[u] = 0;
    sze[u] = 1;
    son[u] = 0;
    for (auto v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            deep[v] = deep[u] + 1;
            dfs(v);
            sze[u] += sze[v];
            szeblock[u] += szeblock[v];
            if (son[u] == 0 || sze[v] > sze[son[u]])
                son[u] = v;
            if (szeblock[u] >= block) {
                szeblock[u] = 0;
                ++dfssize;
                while (!sta.empty() && sta.top() != u) {
                    Belong[sta.top()] = dfssize;
                    sta.pop();
                }
            }
        }
    ++szeblock[u];
}
void gettop(int u, int tp) {
    top[u] = tp;
    if (son[u])
        gettop(son[u], tp);
    for (auto v : G[u])
        if (v != son[u] && v != fa[u])
            gettop(v, v);
}
int querylca(int u, int v) {
    int fu = top[u], fv = top[v];
    while (fu != fv) {
        if (deep[fu] < deep[fv]) {
            swap(fu, fv);
            swap(u, v);
        }
        u = fa[fu];
        fu = top[u];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return u;
}
struct qnode {
    int u, v, id, lca;
    qnode(int u = 0, int v = 0, int id = 0, int lca = 0) : u(u), v(v), id(id), lca(lca) {}
    bool operator<(const qnode &r) const {
        return Belong[u] == Belong[r.u] ? dfn[v] < dfn[r.v] : Belong[u] < Belong[r.u];
    }
} que[N];
int ans[N];
int used[N], cnt_num[N], num_block[block];
void work(int x) {
    if (used[x])
        --cnt_num[arr[x]];
    else
        ++cnt_num[arr[x]];
    num_block[(arr[x] - 1) / block] += 1 * ((cnt_num[arr[x]] & 1) ? 1 : -1);
    used[x] ^= 1;
}
void update(int u, int v) {
    while (u != v) {
        if (deep[u] > deep[v])
            swap(u, v);
        work(v);
        v = fa[v];
    }
}
int Get() {
    for (int k = 0; k < block; ++k)
        if (num_block[k] != block) {
            int l = k * block + 1, r = (k + 1) * block;
            for (int j = l; j <= r; ++j)
                if (cnt_num[j] % 2 == 0)
                    return j;
        }
    return 0;
}
void gao() {
    cnt = 0;
    dfssize = 0;
    dfscnt = 0;
    memset(num_block, 0, sizeof num_block);
    memset(cnt_num, 0, sizeof cnt_num);
    memset(used, 0, sizeof used);
    dfs(1);
    gettop(1, 1);
    while (!sta.empty()) {
        Belong[sta.top()] = dfssize;
        sta.pop();
    }
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        if (Belong[u] > Belong[v])
            swap(u, v);
        que[i] = qnode(u, v, i, querylca(u, v));
    }
    sort(que + 1, que + 1 + m);
    update(que[1].u, que[1].v);
    work(que[1].lca);
    ans[que[1].id] = Get();
    work(que[1].lca);
    for (int i = 2; i <= m; ++i) {
        update(que[i - 1].u, que[i].u);
        update(que[i - 1].v, que[i].v);
        work(que[i].lca);
        ans[que[i].id] = Get();
        work(que[i].lca);
    }
    for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
}
}  // namespace DivOnTree

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &m);
        G.clear();
        G.resize(n + 1);
        for (int i = 1; i <= n; ++i) scanf("%d", arr + i);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        DivOnTree::gao();
    }
    return 0;
}
