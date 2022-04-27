#include <bits/stdc++.h>
using namespace std;

#define N 1010
int G[N][N];
char s[N];
int n, m;
int cnt;
int Move[][2] = {
        -1,
        0,
        1,
        0,
        0,
        -1,
        0,
        1,
};
bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m) {
        return false;
    }
    return true;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        cnt = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s + 1);
            for (int j = 1; j <= m; ++j) {
                if (s[j] == '#') {
                    ++cnt;
                    G[i][j] = 0;
                } else {
                    G[i][j] = n * m;
                }
            }
        }
        int res = 0;
        while (cnt < n * m) {
            ++res;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j)
                    if (G[i][j] == n * m) {
                        for (int k = 0; k < 4; ++k) {
                            int nx = i + Move[k][0];
                            int ny = j + Move[k][1];
                            if (ok(nx, ny) && G[nx][ny] < res) {
                                G[i][j] = res;
                                ++cnt;
                                break;
                            }
                        }
                    }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
