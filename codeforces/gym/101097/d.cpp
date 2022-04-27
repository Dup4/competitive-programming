#include <bits/stdc++.h>

using namespace std;

#define N 1010
#define M 200010
const int INF = 0x3f3f3f3f;
int e[M][3], res[M];
vector<vector<int>> G;
struct qnode {
    // 0加边 1 询问
    int op, p;
    qnode() {}
    qnode(int op, int p) : op(op), p(p) {}
} que[M];
int n, m, q;
int dis[N];

void BFS(int u) {
    queue<int> qu;
    qu.push(u);
    while (!qu.empty()) {
        u = qu.front();
        qu.pop();
        for (auto v : G[u]) {
            if (dis[u] + 1 < dis[v]) {
                dis[v] = dis[u] + 1;
                qu.push(v);
            }
        }
    }
}

int main() {
    freopen("evacuation.in", "r", stdin);
    freopen("evacuation.out", "w", stdout);
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        G.clear();
        G.resize(n + 1);
        memset(dis, 0x3f, sizeof dis);
        dis[1] = 0;
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d", &e[i][0], &e[i][1]);
            e[i][2] = 0;
        }
        for (int i = 1; i <= q; ++i) {
            char op[10];
            int p;
            scanf("%s %d", op, &p);
            que[i] = qnode(op[0] == 'U' ? 0 : 1, p);
            if (op[0] == 'U') {
                e[p][2] = 1;
            }
        }
        for (int i = 1; i <= m; ++i)
            if (e[i][2] == 0) {
                G[e[i][0]].push_back(e[i][1]);
                //	G[e[i][1]].push_back(e[i][0]);
            }
        BFS(1);
        for (int i = q; i >= 1; --i) {
            if (que[i].op == 0) {
                int x = e[que[i].p][0], y = e[que[i].p][1];
                G[x].push_back(y);
                if (dis[x] + 1 < dis[y]) {
                    dis[y] = dis[x] + 1;
                    BFS(y);
                }
            } else {
                res[i] = dis[que[i].p];
            }
        }
        for (int i = 1; i <= q; ++i) {
            if (que[i].op == 1) {
                printf("%d\n", res[i] >= INF ? -1 : res[i]);
            }
        }
    }
    return 0;
}
