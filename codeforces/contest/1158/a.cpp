#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, m;
int a[N], b[N];
int Min, Max;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        Min = 1e9, Max = -1e9;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            Max = max(Max, a[i]);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d", b + i);
            Min = min(Min, b[i]);
        }
        if (Min < Max) {
            puts("-1");
        } else {
            multiset<int> se;
            for (int i = 1; i <= m; ++i) {
                se.insert(b[i]);
            }
            ll res = 0;
            sort(a + 1, a + 1 + n);
            for (int i = n; i >= 1; --i) {
                res += a[i];
                auto pos = se.lower_bound(a[i]);
                if (pos != se.end() && *pos == a[i]) {
                    se.erase(pos);
                }
                int cnt = m - 1;
                while (!se.empty() && cnt) {
                    --cnt;
                    auto pos = se.end();
                    --pos;
                    res += *pos;
                    se.erase(pos);
                }
                res += 1ll * cnt * a[i];
            }
            printf("%lld\n", res);
        }
    }
    return 0;
}
