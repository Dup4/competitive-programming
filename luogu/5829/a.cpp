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
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
const int N = 1e6 + 5;
int q;
char s[N];

struct BorderTree {
    int Next[N], sze[N], top[N], son[N], deep[N], len;
    vector<vector<int>> G;
    // 0-index
    void get_Next(char *s) {
        int i, j;
        j = Next[0] = -1;
        i = 0;
        while (i < len) {
            while (-1 != j && s[i] != s[j]) j = Next[j];
            Next[++i] = ++j;
        }
    }
    void dfs(int u) {
        son[u] = 0;
        sze[u] = 1;
        for (auto &v : G[u]) {
            deep[v] = deep[u] + 1;
            dfs(v);
            sze[u] += sze[v];
            if (!son[u] || sze[v] > sze[son[u]])
                son[u] = v;
        }
    }
    void gettop(int u, int tp) {
        top[u] = tp;
        if (son[u])
            gettop(son[u], tp);
        for (auto &v : G[u]) {
            if (v == son[u])
                continue;
            gettop(v, v);
        }
    }
    int query(int u, int v) {
        u = Next[u], v = Next[v];
        while (top[u] != top[v]) {
            if (deep[top[u]] < deep[top[v]])
                swap(u, v);
            u = Next[top[u]];
        }
        if (deep[u] > deep[v])
            swap(u, v);
        return u;
    }
    void build(char *s) {
        len = strlen(s);
        get_Next(s);
        G.clear();
        G.resize(len + 5);
        for (int i = 1; i <= len; ++i) {
            G[Next[i]].push_back(i);
        }
        deep[1] = 0;
        dfs(1);
        gettop(1, 1);
        Next[0] = 0;
        deep[0] = -1;
    }
} borderTree;

int main() {
    scanf("%s", s);
    borderTree.build(s);
    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", borderTree.query(u, v));
    }
    return 0;
}
