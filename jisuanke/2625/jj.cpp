#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, fa[N], w[N];
vector<vector<int> > G;
vector<int> vec;
int deep[N];
void DFS(int u) {
    for (auto v : G[u]) {
        deep[v] = deep[u] + 1;
        DFS(v);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        w[1] = 0;
        G.clear();
        G.resize(n + 1);
        for (int i = 2; i <= n; ++i) {
            scanf("%d%d", fa + i, w + i);
            w[i] ^= w[fa[i]];
            G[fa[i]].push_back(i);
        }
        deep[1] = 0;
        DFS(1);
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                vec.clear();
                int u = i, v = j;
                while (u != v) {
                    if (deep[u] < deep[v]) {
                        swap(u, v);
                    }
                    vec.push_back(u);
                    u = fa[u];
                }
                vec.push_back(u);
                int sze = (int)vec.size();
                for (int o = 0; o < sze; ++o) {
                    for (int l = o + 1; l < sze; ++l) {
                        if (w[vec[o]] == w[vec[l]]) {
                            ++res;
                        }
                    }
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
