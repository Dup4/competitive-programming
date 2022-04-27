#include <bits/stdc++.h>
using namespace std;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}
#define SZ(x) (int(x.size()))
const int N = 2e5 + 10;
int n, q, a[N], ans;
vector<vector<int> > G, BG;

namespace MoTree {
int blo, cnt;
int belong[N], fa[N];
struct Blocks {
    vector<int> a;
    int sze;
    void clear() {
        a.clear();
        sze = 0;
    }
    void ins(int x) {
        a.push_back(x);
        ++sze;
        for (int i = sze - 2; i >= 0; --i) {
            if (a[i] > a[i + 1])
                swap(a[i], a[i + 1]);
        }
    }
    void modify(int x, int y) {
        int pos = lower_bound(a.begin(), a.end(), x) - a.begin();
        a[pos] = y;
        for (int i = pos + 1; i < sze; ++i) {
            if (a[i] < a[i - 1])
                swap(a[i], a[i - 1]);
        }
        for (int i = pos - 1; i >= 0; --i) {
            if (a[i] > a[i + 1])
                swap(a[i], a[i + 1]);
        }
    }
    void del(int x) {
        int pos = lower_bound(a.begin(), a.end(), x) - a.begin();
        for (int i = pos + 1; i < sze; ++i) {
            swap(a[i - 1], a[i]);
        }
        a.pop_back();
        --sze;
    }
    int query(int x) {
        int pos = upper_bound(a.begin(), a.end(), x) - a.begin();
        return sze - pos;
    }
} b[N];
void getk(int u, int x) {
    ans += b[u].query(x);
    for (int i = 0; i < SZ(BG[u]); ++i) getk(BG[u][i], x);
}
void getans(int u, int x) {
    if (a[u] > x)
        ++ans;
    for (int i = 0; i < SZ(G[u]); ++i) {
        int v = G[u][i];
        if (v == fa[u])
            continue;
        if (belong[v] == belong[u])
            getans(v, x);
        else
            getk(belong[v], x);
    }
}
void modify(int u, int x) {
    b[belong[u]].modify(a[u], x);
    a[u] = x;
}
void addBlock(int u) {
    if (b[belong[fa[u]]].sze == blo) {
        belong[u] = ++cnt;
        b[cnt].ins(a[u]);
        BG[belong[fa[u]]].push_back(cnt);
    } else {
        b[belong[u] = belong[fa[u]]].ins(a[u]);
    }
}
void addItem(int u, int x) {
    a[++n] = x;
    G[u].push_back(n);
    G[n].push_back(u);
    fa[n] = u;
    addBlock(n);
}
void dfs(int u) {
    addBlock(u);
    for (int i = 0; i < SZ(G[u]); ++i) {
        int v = G[u][i];
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs(v);
    }
}
void del(vector<int>& vec, int x) {
    vec.erase(find(vec.begin(), vec.end(), x));
}
void reBuild(int u, int preBlk) {
    for (int i = 0; i < SZ(G[u]); ++i) {
        int v = G[u][i];
        if (v == fa[u])
            continue;
        if (belong[v] == preBlk) {
            belong[v] = belong[u];
            b[preBlk].del(a[v]);
            b[belong[v]].ins(a[v]);
            reBuild(v, preBlk);
        } else {
            del(BG[preBlk], belong[v]);
            BG[belong[u]].push_back(belong[v]);
        }
    }
}
void del(int u) {
    if (fa[u] == 0)
        return;
    del(G[u], fa[u]);
    del(G[fa[u]], u);
    if (belong[u] != belong[fa[u]]) {
        del(BG[belong[fa[u]]], belong[u]);
    } else {
        belong[u] = ++cnt;
        b[cnt].ins(a[u]);
        b[belong[fa[u]]].del(a[u]);
        reBuild(u, belong[fa[u]]);
    }
    fa[u] = 0;
}
void init() {
    blo = (int)sqrt(n);
    cnt = 0;
    BG.clear();
    BG.resize(N);
    fa[1] = 0;
    dfs(1);
}
}  // namespace MoTree

int main() {
    scanf("%d", &n);
    G.clear();
    G.resize(N);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    MoTree::init();
    ans = 0;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        int opt, u, x;
        scanf("%d", &opt);
        if (opt == 3) {
            scanf("%d", &u);
            u ^= ans;
            MoTree::del(u);
        } else {
            scanf("%d%d", &u, &x);
            u ^= ans;
            x ^= ans;
            if (opt == 0) {
                ans = 0;
                MoTree::getans(u, x);
                printf("%d\n", ans);
            } else if (opt == 1) {
                MoTree::modify(u, x);
            } else if (opt == 2) {
                MoTree::addItem(u, x);
            }
        }
    }
}
