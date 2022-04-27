#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define fi first
#define se second
ll n, a, b, c, d;
int q;

pll cross(ll a, ll b, ll c, ll d) {
    return pll(max(a, b), min(c, d));
}

int main() {
    while (scanf("%lld%d", &n, &q) != EOF) {
        while (q--) {
            scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
            ll res = 0;
            pll A = cross(a, b, c, d);
            pll B = cross(a, n - d - 1, c, n - b - 1);
            if (A.fi <= A.se)
                res += A.se - A.fi + 1;
            if (B.fi <= B.se)
                res += B.se - B.fi + 1;
            if (n & 1) {
                ll mid = n / 2;
                if (mid >= a && mid <= c && mid >= b && mid <= d)
                    --res;
            }
            printf("%lld\n", res);
        }
    }
    return 0;
}
