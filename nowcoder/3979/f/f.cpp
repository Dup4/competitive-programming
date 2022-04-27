#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}
const int N = 1e5 + 10;
int n, m;
ll a[N], b[N], K;

ll calc(ll x) {
    ll tot = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 0) {
            if (0 <= x)
                tot += m;
        } else if (a[i] < 0) {
            int l = 1, r = m, res = m + 1;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (a[i] * b[mid] <= x) {
                    res = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            tot += m - res + 1;
        } else {
            int l = 1, r = m, res = 0;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (a[i] * b[mid] <= x) {
                    res = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            tot += res;
        }
    }
    return tot;
}

int main() {
    while (scanf("%d%d%lld", &n, &m, &K) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
        for (int i = 1; i <= m; ++i) scanf("%lld", b + i);
        K = 1ll * n * m - K + 1;
        sort(a + 1, a + 1 + n);
        sort(b + 1, b + 1 + m);
        ll l = -1e12, r = 1e12, res = 1e18;
        while (r - l >= 0) {
            ll mid = (l + r) >> 1;
            if (calc(mid) >= K) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
