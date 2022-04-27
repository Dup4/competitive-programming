#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pLL = pair<ll, ll>;
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
#define fi first
#define se second
int n, p[20];
pLL f[(1 << 16) + 10];

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", p + i);
        memset(f, 0, sizeof f);
        f[0] = pLL(0, 1);
        for (int mask = 1; mask < (1 << n); ++mask) {
            int cnt = __builtin_popcount(mask);
            for (int i = 0; i < n; ++i) {
                if (((mask >> i) & 1) && p[i + 1] != cnt) {
                    ll fee = 0;
                    for (int j = 0; j < n; ++j)
                        if (j != i) {
                            if ((mask >> j) & 1) {
                                if (i < j)
                                    fee += abs(i - j) * cnt;
                            } else {
                                if (i > j)
                                    fee -= abs(i - j) * cnt;
                            }
                        }
                    int pre = mask ^ (1 << i);
                    f[mask].se += f[pre].se;
                    f[mask].fi += f[pre].fi + fee * f[pre].se;
                }
            }
        }
        printf("%lld\n", f[(1 << n) - 1].fi);
    }
    return 0;
}
