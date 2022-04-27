#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e2 + 10, INF = 0x3f3f3f3f;
int n;
int G[maxn][maxn];
int Max, Min;
bool Input() {
    scanf("%d", &n);
    Max = 0;
    Min = INF;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", G[i] + j);
            Max = max(Max, G[i][j]);
            Min = min(Min, G[i][j]);
        }
    return true;
}

int Move[][2] = {
        1,
        0,
        -1,
        0,
        0,
        -1,
        0,
        1,
};
bool used[maxn][maxn];
bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > n || used[x][y] == true)
        return false;
    return true;
}

bool DFS(int x, int y, int l, int r) {
    if (G[x][y] > r || G[x][y] < l)
        return false;
    if (x == n && y == n)
        return true;
    for (int i = 0; i < 4; i++) {
        int nx = x + Move[i][0];
        int ny = y + Move[i][1];
        if (ok(nx, ny)) {
            used[nx][ny] = true;
            if (DFS(nx, ny, l, r))
                return true;
        }
    }
    return false;
}

bool check(int mid) {
    for (int i = Min; i + mid <= Max; i++) {
        memset(used, false, sizeof used);
        used[1][1] = true;
        if (DFS(1, 1, i, i + mid))
            return true;
    }
    return false;
}

void Solve() {
    int l = 0, r = Max - Min, res = INF;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", res);
}

int main() {
    Input();
    Solve();
    return 0;
}
