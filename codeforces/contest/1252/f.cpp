#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
const int N = 4e3 + 10;

int n, m;
vector<vector<int> > G;

struct node {
    int id;
    uint v;

    node() {}

    node(int id, uint v) : id(id), v(v) {}

    bool operator<(const node &other) const {
        return v < other.v;
    }
};

vector<node> a[N];

uint base = 233;

node dfs(int u, int fa) {
    vector<node> vec;
    for (auto &v : G[u]) {
        if (v == fa)
            continue;
        vec.push_back(dfs(v, u));
    }
    sort(vec.begin(), vec.end());
    uint now = 1;
    for (auto &it : vec) {
        now = now * base + it.v;
    }
    return node(u, now * base + 1);
}

void addedge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

void gao() {
    for (int u = 1; u <= n; ++u) {
        for (auto &v : G[u]) {
            a[u].push_back(dfs(v, u));
        }
    }
}

bool same(int x, int y, int rt) {
    if (a[x].size() != a[y].size())
        return false;
    for (int i = 0, j = 0, szei = a[x].size(), szej = a[y].size(); i < szei && j < szej; ++i, ++j) {
        if (a[x][i].id == rt)
            ++i;
        if (a[y][j].id == rt)
            ++j;
        if (a[x][i].v != a[y][j].v)
            return false;
    }
    return true;
}

int solve(int rt) {
    for (auto &v : G[rt]) {
        if (!same(G[rt][0], v, rt))
            return 0;
    }
    return G[rt].size();
}

int main() {
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d %d", &u, &v);
            addedge(u, v);
        }
        gao();
        int res = -1;
        for (int i = 1; i <= n; ++i) {
            res = max(res, solve(i));
        }
        printf("%d\n", res);
    }
    return 0;
}
