#include <bits/stdc++.h>
using namespace std;

#define N 1000010
int pre[N];
int sze[N];
int find(int x) {
    return pre[x] == 0 ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        if (sze[x] > sze[y]) {
            swap(x, y);
        }
        pre[x] = y;
        sze[y] += sze[x];
    }
}
int n, m;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(pre, 0, sizeof pre);
        memset(sze, 0, sizeof sze);
        for (int i = 1; i <= n; ++i) {
            sze[i] = 1;
        }
        for (int i = 1, k; i <= m; ++i) {
            scanf("%d", &k);
            for (int j = 1, x; j <= k; ++j) {
                scanf("%d", &x);
                join(x, n + i);
            }
        }
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", sze[find(i)], " \n"[i == n]);
        }
    }
    return 0;
}
