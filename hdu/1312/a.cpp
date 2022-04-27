#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define x first
#define y second
const int N = 1e2 + 10;
int n, m, sx, sy;
char s[N][N];
int use[N][N];
int Move[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
};

bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m)
        return false;
    if (s[x][y] == '#')
        return false;
    if (use[x][y] == 1)
        return false;
    return true;
}

void bfs() {
    memset(use, 0, sizeof use);
    queue<pII> que;
    que.push(pII(sx, sy));
    use[sx][sy] = 1;
    int res = 0;
    while (!que.empty()) {
        pII u = que.front();
        que.pop();
        ++res;
        for (int i = 0; i < 4; ++i) {
            int nx = u.x + Move[i][0];
            int ny = u.y + Move[i][1];
            // if (nx == 5 && ny == 6) cout << ok(nx, ny) << endl;
            if (ok(nx, ny)) {
                use[nx][ny] = 1;
                que.push(pII(nx, ny));
            }
        }
    }
    printf("%d\n", res);
}

int main() {
    while (scanf("%d%d", &m, &n), n + m) {
        for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s[i][j] == '@') {
                    sx = i;
                    sy = j;
                }
            }
        }
        bfs();
    }
    return 0;
}
