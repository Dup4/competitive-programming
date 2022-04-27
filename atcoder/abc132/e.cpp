#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define N 100010
int n, m, s, t;
vector<vector<int>> G;
struct node {
    int u, w;
    node() {}
    node(int u, int w) : u(u), w(w) {}
    bool operator<(const node &other) const {
        return w > other.w;
    }
};

int dis[N][3], used[N][3];
void BFS() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) {
            dis[i][j] = INF;
            used[i][j] = 0;
        }
    }
    dis[s][0] = 0;
    priority_queue<node> pq;
    pq.push(node(s, 0));
    while (!pq.empty()) {
        int u = pq.top().u, w = pq.top().w;
        pq.pop();
        if (used[u][w % 3])
            continue;
        used[u][w % 3] = 1;
        for (auto v : G[u]) {
            if (dis[v][(w + 1) % 3] > w + 1) {
                dis[v][(w + 1) % 3] = w + 1;
                pq.push(node(v, w + 1));
            }
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
        }
        scanf("%d%d", &s, &t);
        BFS();
        if (dis[t][0] == INF)
            puts("-1");
        else {
            printf("%d\n", dis[t][0] / 3);
        }
    }
    return 0;
}
