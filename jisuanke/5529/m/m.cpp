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
    cout << arg << " ";
    err(args...);
}
const int N = 2e5 + 10;

int n;
vector<vector<int> > G;
int sze[N], fa[N], son[N], res[N];

void dfs(int u, int pre = 0) {
    sze[u] = 1;
    fa[u] = pre;
    for (auto &v : G[u]) {
        if (v == pre)
            continue;
        dfs(v, u);
        sze[u] += sze[v];
        if (son[u] == -1 || sze[son[u]] < sze[v]) {
            son[u] = v;
        }
    }
    if (son[u] == -1)
        son[u] = u;
}

void gao(int u) {
    if (sze[u] == 1) {
        res[u] = u;
        return;
    }
    for (auto &v : G[u]) {
        if (v == fa[u])
            continue;
        gao(v);
    }
    int now = res[son[u]];
    while (now != u) {
        int tmp = max(sze[u] - sze[now], sze[son[now]]);
        if (tmp <= sze[u] / 2) {
            break;
        }
        now = fa[now];
    }
    //	assert(max(sze[u] - sze[now], sze[son[now]]) <= sze[u] / 2);
    res[u] = now;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(son, -1, sizeof son);
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d %d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1);
        gao(1);
        for (int i = 1; i <= n; ++i) {
            vector<int> vec;
            int x = res[i], y = -1;
            vec.push_back(x);
            if (x != i) {
                y = fa[x];
                if (max(sze[i] - sze[y], sze[son[y]]) <= sze[i] / 2) {
                    vec.push_back(y);
                }
            }
            if (vec.size() > 1 && vec[0] > vec[1])
                swap(vec[0], vec[1]);
            for (int j = 0, sze = vec.size(); j < sze; ++j) printf("%d%c", vec[j], " \n"[j == sze - 1]);
        }
    }
    return 0;
}
