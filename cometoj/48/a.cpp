#include <bits/stdc++.h>
using namespace std;

#define N 310
int n, m;
int fa[N];
int find(int x) {
    return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}
void join(int u, int v) {
    int fu = find(u), fv = find(v);
    if (fu != fv) {
        fa[fu] = fv;
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(fa, 0, sizeof fa);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            join(u, v);
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            res += (fa[i] == 0);
        }
        puts((res & 1) == 0 ? "Illyasviel" : "Star-dust");
    }
    return 0;
}
