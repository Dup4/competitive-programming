#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;
using heap = __gnu_pbds::priority_queue<int, less<int>, binomial_heap_tag>;
const int N = 1e5 + 10;
heap ph[N];

struct UFS {
    int fa[N], sze[N];
    void init(int n, int *a) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = 0;
            sze[i] = 1;
            ph[i].clear();
            ph[i].push(a[i]);
        }
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    int merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (sze[fx] > sze[fy])
                swap(fx, fy);
            fa[fx] = fy;
            sze[fy] += sze[fx];
            int X = ph[fx].top() / 2;
            ph[fx].pop();
            int Y = ph[fy].top() / 2;
            ph[fy].pop();
            ph[fx].push(X);
            ph[fy].push(Y);
            ph[fy].join(ph[fx]);
            return ph[fy].top();
        }
        return -1;
    }
} ufs;

int n, q, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        ufs.init(n, a);
        scanf("%d", &q);
        for (int i = 1, x, y; i <= q; ++i) {
            scanf("%d%d", &x, &y);
            printf("%d\n", ufs.merge(x, y));
        }
    }
    return 0;
}
