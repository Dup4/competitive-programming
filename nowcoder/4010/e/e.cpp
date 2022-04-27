#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
const int N = 1e5 + 10;
int n, fa[N];
ll res[N];
vector<vector<int>> G;
set<int> se[N];

inline ll sqr(ll x) {
    return x * x;
}

void dfs(int u) {
    se[u].clear();
    se[u].insert(u);
    res[u] = 0;
    for (auto &v : G[u]) {
        dfs(v);
        if (se[v].size() > se[u].size()) {
            se[v].swap(se[u]);
            res[u] = res[v];
        }
        for (auto &it : se[v]) {
            auto pos = se[u].lower_bound(it);
            if (pos == se[u].end()) {
                auto pre = pos;
                --pre;
                res[u] += sqr(it - *pre);
            } else if (pos == se[u].begin()) {
                res[u] += sqr(*pos - it);
            } else {
                auto pre = pos;
                --pre;
                res[u] -= sqr(*pos - *pre);
                res[u] += sqr(it - *pre);
                res[u] += sqr(*pos - it);
            }
            se[u].insert(it);
        }
        se[v].clear();
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 2; i <= n; ++i) {
            scanf("%d", fa + i);
            G[fa[i]].push_back(i);
        }
        for (int i = 1; i <= n; ++i) {
            res[i] = 0;
            se[i].clear();
        }
        dfs(1);
        for (int i = 1; i <= n; ++i) printf("%lld\n", res[i]);
    }
    return 0;
}
