#include <bits/stdc++.h>

using namespace std;

#define N 510

vector<vector<int> > G;
int linker[N];
bool used[N];
int uN;

bool DFS(int u) {
    for (auto v : G[u]) {
        if (!used[v]) {
            used[v] = true;
            if (linker[v] == -1 || DFS(linker[v])) {
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}

int n, m, r, t, k;
int Time[N];

int main() {
    freopen("contest.in", "r", stdin);
    freopen("contest.out", "w", stdout);
    while (scanf("%d %d %d %d %d", &n, &m, &r, &t, &k) != EOF) {
        G.clear();
        G.resize(n + 1);
        memset(linker, -1, sizeof linker);
        memset(Time, 0, sizeof Time);
        for (int i = 1, a, b; i <= k; ++i) {
            scanf("%d %d", &a, &b);
            G[a].push_back(b);
        }
        int ans1 = 0, ans2 = 0;
        for (int i = 1; i * r <= t; ++i) {
            bool F = 0;
            for (int u = 1; u <= n; ++u) {
                memset(used, false, sizeof used);
                if (DFS(u)) {
                    F = 1;
                    ans1++;
                    ans2 += i;
                }
            }
            if (!F) {
                break;
            }
        }
        printf("%d %d\n", ans1, ans2 * r);
        for (int i = 1; i <= m; ++i) {
            if (linker[i] == -1)
                continue;
            int u = linker[i];
            printf("%d %d %d\n", u, i, Time[u]);
            Time[u] += r;
        }
    }
    return 0;
}
