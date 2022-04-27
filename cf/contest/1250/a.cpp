#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 4e5 + 10;
int n, m, a[N], fa[N], b[N];
pII res[N];
void up(int x, int y) {
    res[x].fi = min(res[x].fi, y);
    res[x].se = max(res[x].se, y);
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) a[i] = i, fa[i] = i, res[i] = pII(i, i);
        for (int i = 1; i <= m; ++i) scanf("%d", b + i);
        for (int i = 1; i <= m; ++i) {
            int x = b[i];
            if (fa[x] == 1)
                continue;
            int pre = a[fa[x] - 1];
            swap(fa[x], fa[pre]);
            swap(a[fa[x]], a[fa[pre]]);
            up(x, fa[x]);
            up(pre, fa[pre]);
            //	for (int j = 1; j <= n; ++j)
            //		printf("%d%c", a[j], " \n"[j == n]);
        }
        for (int i = 1; i <= n; ++i) printf("%d %d\n", res[i].fi, res[i].se);
    }
    return 0;
}
