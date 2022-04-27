#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, a[N][N], fa[N];
int find(int x) {
    return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}
void merge(int u, int v) {
    int fu = find(u), fv = find(v);
    if (fu != fv) {
        fa[fu] = fv;
    }
}

int main() {
    memset(fa, 0, sizeof fa);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", a[i] + j);
            if (a[i][j]) {
                merge(i, j);
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        if (fa[i] == 0)
            ++res;
    }
    puts(res == 1 ? "Yes" : "No");
    return 0;
}
