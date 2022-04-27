#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n;
ll f[110][2];

ll getcnt(ll x) {
    ll res = 0;
    while (x) {
        res += x % 2;
        x /= 2;
    }
    return res;
}

ll get(ll x) {
    ll res = 0;
    for (int i = 63; i > 0; --i) {
        if ((x >> i) & 1) {
            res += f[i - 1][0];
        }
    }
    if ((x & 1) || (getcnt(x) & 1))
        ++res;
    return res;
}

int main() {
    memset(f, 0, sizeof f);
    f[0][0] = f[0][1] = 1;
    for (int i = 1; i <= 64; ++i) {
        f[i][0] = f[i - 1][0] + f[i - 1][1];
        f[i][1] = f[i - 1][0] + f[i - 1][1];
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld", &n);
        ll l = 1, r = 4e18, res = -1;
        while (r - l >= 0) {
            ll mid = (l + r) >> 1;
            //		cout << mid << " " << get(mid) << " " << n << endl;
            if (get(mid) >= n) {
                r = mid - 1;
                res = mid;
            } else {
                l = mid + 1;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
