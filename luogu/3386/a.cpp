#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;
const int INF = 0x3f3f3f3f;
int n, m, e;
vector<vector<int>> G;
struct Hopcroft {
    // uN是左边的点数
    // Mx是左边的点指向的右边的点
    // My是右边的点指向的左边的点
    int Mx[N], My[N], dx[N], dy[N], dis, uN;
    bool used[N];
    bool SearchP() {
        queue<int> que;
        dis = INF;
        memset(dx, -1, sizeof dx);
        memset(dy, -1, sizeof dy);
        for (int i = 0; i < uN; ++i) {
            if (Mx[i] == -1) {
                que.push(i);
                dx[i] = 0;
            }
        }
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            if (dx[u] > dis)
                break;
            for (auto &v : G[u]) {
                if (dy[v] == -1) {
                    dy[v] = dx[u] + 1;
                    if (My[v] == -1)
                        dis = dy[v];
                    else {
                        dx[My[v]] = dy[v] + 1;
                        que.push(My[v]);
                    }
                }
            }
        }
        return dis != INF;
    }
    bool DFS(int u) {
        for (auto &v : G[u]) {
            if (!used[v] && dy[v] == dx[u] + 1) {
                used[v] = true;
                if (My[v] != -1 && dy[v] == dis)
                    continue;
                if (My[v] == -1 || DFS(My[v])) {
                    My[v] = u;
                    Mx[u] = v;
                    return true;
                }
            }
        }
        return false;
    }
    int MaxMatch() {
        int res = 0;
        memset(Mx, -1, sizeof Mx);
        memset(My, -1, sizeof My);
        while (SearchP()) {
            memset(used, 0, sizeof used);
            for (int i = 0; i < uN; ++i) {
                if (Mx[i] == -1 && DFS(i)) {
                    ++res;
                }
            }
        }
        return res;
    }
} hopcroft;

int main() {
    while (scanf("%d%d%d", &n, &m, &e) != EOF) {
        hopcroft.uN = n;
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i <= e; ++i) {
            scanf("%d%d", &u, &v);
            --u, --v;
            if (u >= n || v >= m)
                continue;
            G[u].push_back(v);
        }
        printf("%d\n", hopcroft.MaxMatch());
    }
    return 0;
}
