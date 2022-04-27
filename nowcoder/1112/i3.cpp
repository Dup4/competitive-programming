#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10;
int n, c[N], cnt[N][2], ans[N], res;
vector<vector<pII>> G;
int fa[N], sze[N], son[N], son_id[N], big[N];
void dfs(int u) {
    sze[u] = 1;
    son[u] = 0;
    for (auto &it : G[u]) {
        int v = it.fi;
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs(v);
        sze[u] += sze[v];
        if (!son[u] || sze[v] > sze[son[u]]) {
            son[u] = v;
            son_id[u] = it.se;
        }
    }
}
void add(int u, int f) {
    if (cnt[c[u]][0] && cnt[c[u]][1])
        --res;
    if (f) {
        --cnt[c[u]][0];
        ++cnt[c[u]][1];
    } else {
        ++cnt[c[u]][0];
        --cnt[c[u]][1];
    }
    if (cnt[c[u]][0] && cnt[c[u]][1])
        ++res;
}
void up(int u, int f) {
    add(u, f);
    for (auto &it : G[u]) {
        int v = it.fi;
        //如果v被标记为重儿子，那么它的贡献已经在里面了
        if (big[v] || v == fa[u])
            continue;
        up(v, f);
    }
}
void gao(int u, int id) {
    //先处理完轻儿子的答案
    for (auto &it : G[u]) {
        int v = it.fi;
        if (v == fa[u] || v == son[u])
            continue;
        gao(v, it.se);
    }
    //再处理重儿子的答案
    if (son[u]) {
        big[son[u]] = 1;
        gao(son[u], son_id[u]);
    }
    //重新加上轻儿子的贡献和当前点的贡献
    up(u, u);
    ans[id] = res;
    if (son[u])
        big[son[u]] = 0;
    //如果当前点不是其父亲的重儿子，那么删除它对答案的影响
    if (!big[u])
        up(u, 0);
}
void run() {
    memset(cnt[0], 0, sizeof(cnt[0]) * (n + 10));
    memset(cnt[1], 0, sizeof(cnt[1]) * (n + 10));
    memset(ans, 0, sizeof(ans[0]) * (n + 10));
    G.clear();
    G.resize(n + 1);
    res = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
        ++cnt[c[i]][0];
    }
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].push_back(pII(v, i));
        G[v].push_back(pII(u, i));
    }
    dfs(1);
    gao(1, 0);
    for (int i = 1; i < n; ++i) printf("%d\n", ans[i]);
}

int main() {
    while (scanf("%d", &n) != EOF) run();
    return 0;
}
