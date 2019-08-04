#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int mod = 998244353;
constexpr ll inv2 = 499122177;
constexpr ll inv6 = 166374059;

struct Query {
    ll f, g, h;
};

Query solve(ll a, ll b, ll c, ll n) {
    Query ans, tmp;
    if (a == 0) {
        ans.f = (n + 1) * (b / c) % mod;
        ans.g = (b / c) * n % mod * (n + 1) % mod * inv2 % mod;
        ans.h = (n + 1) * (b / c) % mod * (b / c) % mod;
        return ans;
    }
    if (a >= c || b >= c) {
        tmp = solve(a % c, b % c, c, n);
        ans.f = (tmp.f + (a / c) * n % mod * (n + 1) % mod * inv2 % mod + (b / c) * (n + 1) % mod) % mod;
        ans.g = (tmp.g + (a / c) * n % mod * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod + (b / c) * n % mod * (n + 1) % mod * inv2 % mod) % mod;
        ans.h = ((a / c) * (a / c) % mod * n % mod * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod + 
                (b / c) * (b / c) % mod * (n + 1) % mod + (a / c) * (b / c) % mod * n % mod * (n + 1) % mod + 
                tmp.h + 2 * (a / c) % mod * tmp.g % mod + 2 * (b / c) % mod * tmp.f % mod) % mod;
        return ans;
    }
    ll m = (a * n + b) / c;
    tmp = solve(c, c - b - 1, a, m - 1);
    ans.f = (n * (m % mod) % mod - tmp.f) % mod;
    ans.g = (n * (n + 1) % mod * (m % mod) % mod - tmp.f - tmp.h) % mod * inv2 % mod;
    ans.h = (n * (m % mod) % mod * ((m + 1) % mod) % mod - 2 * tmp.g - 2 * tmp.f - ans.f) % mod;
    return ans;
}


int main() {
	int T; scanf("%d", &T);
    ll n, a, b, c;
    while (T--) {
		scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
        Query ans = solve(a, b, c, n);
		ans.f = (ans.f + mod) % mod;
		ans.g = (ans.g + mod) % mod;
		ans.h = (ans.h + mod) % mod;
        printf("%lld %lld %lld\n", ans.f, ans.h, ans.g);
    }
    return 0;
}
