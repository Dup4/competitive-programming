#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;
int n, vis[N][N][N];
char g[N][N][N];

struct E {
    int x, y, z, s;
};
int Move[][3] = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};
bool ok(E it) {
    if (it.x < 1 || it.x > n || it.y < 1 || it.y > n || it.z < 1 || it.z > n || g[it.x][it.y][it.z] == '*' ||
            vis[it.x][it.y][it.z])
        return false;
    return true;
}

void bfs() {
    memset(vis, 0, sizeof vis);
    queue<E> que;
    que.push({1, 1, 1, 1});
    vis[1][1][1] = 1;
    while (!que.empty()) {
        E top = que.front();
        que.pop();
        if (top.x == n && top.y == n && top.z == n) {
            cout << top.s << endl;
            return;
        }
        for (int i = 0; i < 6; ++i) {
            E nx = top;
            nx.s = top.s + 1;
            nx.x += Move[i][0];
            nx.y += Move[i][1];
            nx.z += Move[i][2];
            if (ok(nx)) {
                vis[nx.x][nx.y][nx.z] = 1;
                que.push(nx);
            }
        }
    }
    cout << -1 << endl;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%s", g[i][j] + 1);
            }
        }
        bfs();
    }
    return 0;
}
