#include <bits/stdc++.h>
using namespace std;

using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10;
int n, k, a[N], f[N], g[N];

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%d", &n, &k);
        ++k;
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= n; ++i) f[i] = g[i] = 0;
        set<int> se;
        for (int i = 1; i <= n; ++i) {
            if (i > k)
                se.erase(a[i - k]);
            auto pos = se.lower_bound(a[i]);
            if (pos != se.begin()) {
                --pos;
                f[a[i]] = *pos;
            }
            se.insert(a[i]);
        }
        se.clear();
        for (int i = n; i >= 1; --i) {
            if (n - i + 1 > k)
                se.erase(a[i + k]);
            auto pos = se.lower_bound(a[i]);
            if (pos != se.begin()) {
                --pos;
                f[a[i]] = max(f[a[i]], *pos);
            }
            se.insert(a[i]);
        }
        //	for (int i = 1; i <= n; ++i)
        //		printf("%d %d\n", i, f[i]);
        g[0] = 0;
        for (int i = 1; i <= n; ++i) {
            g[i] = g[f[i]] + 1;
            printf("%d%c", g[i], " \n"[i == n]);
        }
    }
    return 0;
}
