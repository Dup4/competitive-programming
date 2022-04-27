#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define pii pair<int, int>
#define fi first
#define se second
int n, m;
ll a[N];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", a + i);
        }
        sort(a + 1, a + 1 + n);
        priority_queue<pii, vector<pii>> pq;
        for (int i = 1, x, y; i <= m; ++i) {
            scanf("%d%d", &x, &y);
            pq.push(pii(y, x));
        }
        for (int i = 1; i <= n; ++i) {
            if (!pq.empty() && pq.top().fi > a[i]) {
                pii it = pq.top();
                pq.pop();
                a[i] = it.fi;
                --it.se;
                if (it.se > 0)
                    pq.push(it);
            }
        }
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            res += a[i];
        }
        printf("%lld\n", res);
    }
    return 0;
}
