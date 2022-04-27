#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
struct E {
    int to, nx;
} e[N << 1];
int h[N], tot;
inline void add(int u, int v) {
    e[tot] = {v, h[u]};
    h[u] = tot++;
}
int n, vis[N];
vector<int> res;
void dfs(int u) {
    for (int &i = h[u]; i != -1; i = e[i].nx) {
        int v = e[i].to;
        if (vis[v] == 0) {
            vis[v] = 1;
            dfs(v % (n >> 1));
            res.push_back(v % n);
        }
        if (i == -1)
            break;
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        if (n & 1)
            puts("-1");
        else {
            tot = 0;
            memset(h, -1, sizeof h);
            memset(vis, 0, sizeof vis);
            for (int i = 0; i < n; ++i) {
                add(i, i << 1);
                add(i, i << 1 | 1);
            }
            res.clear();
            dfs(0);
            res.push_back(0);
            reverse(res.begin(), res.end());
            for (int i = 0; i <= n; ++i) printf("%d%c", res[i], " \n"[i == n]);
        }
    }
    return 0;
}
