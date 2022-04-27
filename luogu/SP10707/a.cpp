#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
#define block 400
int n, m, q;
int arr[N], brr[N], ans[N], cnt[N], res;
vector<int> G[N];
int top[N], fa[N], deep[N], num[N], ord[N], st[N], ed[N], son[N], pos;
bool used[N];

void Init() {
    memset(son, -1, sizeof son);
    memset(used, 0, sizeof used);
    memset(cnt, 0, sizeof cnt);
    res = 0;
    for (int i = 1; i <= n; ++i) G[i].clear();
    for (int i = 1; i <= n; ++i) brr[i] = arr[i];
    sort(brr + 1, brr + 1 + n);
    m = unique(brr + 1, brr + 1 + n) - brr - 1;
    for (int i = 1; i <= n; ++i) arr[i] = lower_bound(brr + 1, brr + 1 + m, arr[i]) - brr;
    pos = 0;
    deep[1] = 0;
    fa[1] = 1;
}

void DFS(int u) {
    num[u] = 1;
    for (auto &v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            deep[v] = deep[u] + 1;
            DFS(v);
            num[u] += num[v];
            if (son[u] == -1 || num[v] > num[son[u]])
                son[u] = v;
        }
}

void gettop(int u, int sp) {
    top[u] = sp;
    ord[++pos] = u;
    st[u] = pos;
    if (son[u] != -1) {
        gettop(son[u], sp);
    }
    for (auto v : G[u])
        if (v != fa[u] && v != son[u])
            gettop(v, v);
    ord[++pos] = u;
    ed[u] = pos;
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]])
            swap(u, v);
        u = fa[u];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return u;
}

struct QUE {
    int l, r, id, lca;
    QUE() {}
    QUE(int l, int r, int id, int lca) : l(l), r(r), id(id), lca(lca) {}
    bool operator<(const QUE &r) const {
        int posl = l / block, posr = r.l / block;
        return posl == posr ? this->r < r.r : posl < posr;
    }
} que[N];

void update(int pos) {
    int x = ord[pos];
    if (used[x]) {  // minus
        if (cnt[arr[x]] == 1)
            --res;
        --cnt[arr[x]];
    } else {
        if (cnt[arr[x]] == 0)
            ++res;
        ++cnt[arr[x]];
    }
    used[x] ^= 1;
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", arr + i);
        Init();
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        DFS(1);
        gettop(1, 1);
        for (int i = 1, u, v; i <= q; ++i) {
            scanf("%d%d", &u, &v);
            int LCA = lca(u, v);
            if (st[u] > st[v])
                swap(u, v);
            if (u == LCA)
                que[i] = QUE(st[u], st[v], i, 0);
            else
                que[i] = QUE(ed[u], st[v], i, LCA);
        }
        sort(que + 1, que + 1 + q);
        for (int i = 1, l = 1, r = 0; i <= q; ++i) {
            for (; r < que[i].r; ++r) update(r + 1);
            for (; r > que[i].r; --r) update(r);
            for (; l < que[i].l; ++l) update(l);
            for (; l > que[i].l; --l) update(l - 1);
            ans[que[i].id] = res;
            //特判lca的贡献
            if (que[i].lca)
                if (cnt[arr[que[i].lca]] == 0)
                    ++ans[que[i].id];
        }
        for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
    }
    return 0;
}
