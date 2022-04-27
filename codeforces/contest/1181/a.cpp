#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define fi first
#define se second
ll x, y, z;

int main() {
    while (scanf("%lld%lld%lld", &x, &y, &z) != EOF) {
        vector<pll> res;
        res.emplace_back(x / z + y / z, 0);
        if (y >= z - x % z)
            res.emplace_back(x / z + 1 + (y - (z - x % z)) / z, z - x % z);
        if (x >= z - y % z)
            res.emplace_back((x - (z - y % z)) / z + y / z + 1, z - y % z);
        sort(res.begin(), res.end(), [&](pll x, pll y) {
            if (x.fi != y.fi) {
                return x.fi > y.fi;
            }
            return x.se < y.se;
        });
        printf("%lld %lld\n", res[0].fi, res[0].se);
    }
    return 0;
}
