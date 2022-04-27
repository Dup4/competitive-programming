#include <bits/stdc++.h>
using namespace std;
int func(int x, int y, int i, int j, int r, int t);
int main() {
    int map[25][25];
    int n, m, t;
    int i, j, p;
    for (i = 0; i < 25; ++i) {
        for (j = 0; j < 25; ++j) {
            map[i][j] = 0;
        }
    }
    scanf("%d%d%d", &n, &m, &t);
    int x, y, r;
    for (p = 0; p < 3; ++p) {
        scanf("%d %d %d", &x, &y, &r);
        for (i = 0; i < n; ++i) {
            for (j = 0; j < m; ++j) {
                map[i][j] += func(x - 1, y - 1, i, j, r, t);
            }
        }
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            printf("%d", map[i][j]);
            printf("%c", j == m - 1 ? '\n' : ' ');
        }
    }
}

int func(int x, int y, int i, int j, int r, int t) {
    int dis = abs(x - i) + abs(y - j);
    if (dis > t)
        return 0;
    return ((t - dis) % 2) ? -r : r;
}
