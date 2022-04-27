#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
struct Hash {
    int a[N];
    void init() {
        *a = 0;
    }
    void add(int x) {
        a[++*a] = x;
    }
    void gao() {
        sort(a + 1, a + 1 + *a);
        *a = unique(a + 1, a + 1 + *a) - a - 1;
    }
    int get(int x) {
        return lower_bound(a + 1, a + 1 + *a, x) - a;
    }
} hs;
int n, m, x[N], y[N], op[N], sze[N];
ll a[N], b[N];
vector<vector<int>> vec;

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        memset(b, 0, sizeof(b[0]) * (n + 10));
        vec.clear();
        vec.resize(n + 1);
        hs.init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", op + i);
            if (op[i] == 1) {
                scanf("%d", sze + i);
                vec[i].resize(sze[i]);
                for (int j = 0; j < sze[i]; ++j) {
                    scanf("%d", &vec[i][j]);
                    hs.add(vec[i][j]);
                }
            } else {
                scanf("%d%d", x + i, y + i);
            }
        }
        hs.gao();
        m = hs.a[0];
        memset(a, 0, sizeof(a[0]) * (m + 10));
        b[n] = 1;
        for (int i = n; i >= 1; --i) {
            if (b[i] == 0)
                continue;
            if (op[i] == 1) {
                for (int j = 0; j < sze[i]; ++j) {
                    vec[i][j] = hs.get(vec[i][j]);
                    a[vec[i][j]] += b[i];
                }
            } else {
                b[x[i]] += b[i];
                b[y[i]] += b[i];
            }
        }
        ll tot = 0, Max = 0;
        for (int i = 1; i <= m; ++i) {
            tot += a[i];
            Max = max(Max, a[i]);
        }
        ll res = 0;
        if (Max <= tot / 2)
            res = tot;
        else
            res = (tot - Max) * 2;
        printf("%lld\n", res);
    }
    return 0;
}
