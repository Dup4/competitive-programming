#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

map<pii, ll> mp;

ll gao(ll n, ll m) {
    if (mp.find(pii(n, m)) != mp.end())
        return mp[pii(n, m)];
    if (n == 1 || m == 1) {
        if (n % 2 != m % 2) {
            mp[pii(n, m)] = 0;
        } else {
            mp[pii(n, m)] = 1;
        }
    } else if (n % 2 != m % 2) {
        mp[pii(n, m)] = 0ll;
    } else if (n == 1 && m == 1) {
        mp[pii(n, m)] = 1ll;
    } else if (n % 2 == 0) {
        mp[pii(n, m)] = 4ll * gao(n / 2, m / 2);
    } else {
        mp[pii(n, m)] = 1ll * gao(n / 2, m / 2) + 1ll * gao(n / 2 + 1, m / 2 + 1) + gao(n / 2 + 1, m / 2) +
                        gao(n / 2, m / 2 + 1);
    }
    return mp[pii(n, m)];
}

ll n, m;

int main() {
    freopen("chocolate.in", "r", stdin);
    freopen("chocolate.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld %lld", &n, &m);
        printf("%lld\n", gao(n, m));
    }
    return 0;
}
