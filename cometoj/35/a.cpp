#include <bits/stdc++.h>
using namespace std;

#define N 50
int n, m;
char G[N][N];

int ok(int x, int y) {
    int r = -1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (G[i][j] == '.') {
                r = max(r, abs(i - x) + abs(j - y));
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (G[i][j] == '#' && abs(i - x) + abs(j - y) <= r) {
                return -1;
            }
        }
    }
    return r;
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (G[i][j] == '.') {
                int r = ok(i, j);
                if (r != -1) {
                    printf("%d %d %d\n", r, i, j);
                    return;
                }
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            scanf("%s", G[i] + 1);
        }
        solve();
    }
    return 0;
}
