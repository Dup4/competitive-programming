#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_cxx;
const int N = 2e5 + 10;
int n, q, a[N];

struct UFS {
    rope<int> *fa;
    int find(int x) {
        if (fa->at(x) == 0)
            return x;
        fa->replace(x, find(fa->at(x)));
        return fa->at(x);
    }
    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            fa->replace(fx, fy);
        }
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
} ufs[N];

int main() {
    scanf("%d%d", &n, &q);
    memset(a, 0, sizeof(a[0]) * (n + 5));
    //用数组新建rope
    ufs[0].fa = new rope<int>(a, a + 1 + n);
    for (int i = 1, op, x, y, k; i <= q; ++i) {
        scanf("%d", &op);
        //复制之前版本的rope，不会影响之前的版本
        ufs[i].fa = new rope<int>(*ufs[i - 1].fa);
        if (op == 1) {
            scanf("%d%d", &x, &y);
            ufs[i].merge(x, y);
        } else if (op == 2) {
            scanf("%d", &k);
            //直接继承，会影响之前的版本
            ufs[i].fa = ufs[k].fa;
        } else if (op == 3) {
            scanf("%d%d", &x, &y);
            printf("%d\n", ufs[i].same(x, y));
        }
    }
}
