#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e2 + 10;
constexpr int INF = 0x3f3f3f3f;
int n, m, sx, sy, ex, ey, a[N][N], b[N][N], f[2][N][N];

bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m)
        return false;
    return true;
}

struct node {
    int t, x, y;
    node() {}
    node(int t, int x, int y) : t(t), x(x), y(y) {}
};

int bfs() {
    if (sx == ex && sy == ey)
        return 0;
    queue<node> que;
    que.push(node(0, sx, sy));
    memset(f, 0, sizeof f);
    f[0][sx][sy] = 1;
    for (int nowt = 0;; ++nowt) {
        int p = nowt & 1;
        if (f[p][ex][ey])
            return nowt;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j)
                if (f[p][i][j]) {
                    f[p ^ 1][i][j] = 1;
                    int _a = a[i][j], _b = b[i][j];
                    int _t = nowt;
                    int tot = _a + _b;
                    int remind = _t % tot;
                    if (remind < _a) {
                        if (i > 1)
                            f[p ^ 1][i - 1][j] = 1;
                        if (i < n)
                            f[p ^ 1][i + 1][j] = 1;
                    } else {
                        if (j > 1)
                            f[p ^ 1][i][j - 1] = 1;
                        if (j < m)
                            f[p ^ 1][i][j + 1] = 1;
                    }
                }
        }
    }
}

int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &ex, &ey);
    for (auto &arr : {a, b}) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", arr[i] + j);
            }
        }
    }
    printf("%d\n", bfs());
    return 0;
}
