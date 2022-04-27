#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 20
int n, m;
ll f[N][1 << 11];

void DFS(int i, int j, int state, int nx) {
    if (j == m) {
        f[i + 1][nx] += f[i][state];
        return;
    }
    if (state >> j & 1)
        DFS(i, j + 1, state, nx);
    if ((state >> j & 1) == 0)
        DFS(i, j + 1, state, nx | (1 << j));
    if (j + 1 < m && (state >> j & 1) == 0 && (state >> (j + 1) & 1) == 0)
        DFS(i, j + 2, state, nx);
}

int main() {
    while (scanf("%d%d", &n, &m), n + m) {
        memset(f, 0, sizeof f);
        f[1][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < (1 << m); ++j) {
                if (f[i][j]) {
                    DFS(i, 0, j, 0);
                }
            }
        }
        printf("%lld\n", f[n + 1][0]);
    }
    return 0;
}
