#include <bits/stdc++.h>
using namespace std;

#define N 300010
int n, m;
vector<int> G[N];
int a[N];
int DFS(int u) {
    if (G[u].size() == 0) {
        ++m;
        return 1;
    }
    int res;
    if (a[u]) {
        res = 1e9;
        for (auto v : G[u]) {
            res = min(res, DFS(v));
        }
    } else {
        res = 0;
        for (auto v : G[u]) {
            res += DFS(v);
        }
    }
    return res;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        m = 0;
        for (int i = 1; i <= n; ++i) {
            G[i].clear();
            scanf("%d", a + i);
        }
        for (int u = 2, v; u <= n; ++u) {
            scanf("%d", &v);
            G[v].push_back(u);
        }
        int t = DFS(1);
        printf("%d\n", m - t + 1);
    }
    return 0;
}
