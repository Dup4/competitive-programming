#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, up;

inline int sum(ll n) {
	return (n % 4 == 0 || (n + 1) % 4 == 0) ^ 1;
}

int gao(ll a, ll b, ll c, ll n) {
    if (a == 0) {
        return ((n + 1) * (b / c)) & 1; 
    }
    if (a >= c || b >= c) { 
        int tmp = gao(a % c, b % c, c, n);
        int res = ((tmp + ((a / c) * sum(n) & 1) & 1) + ((b / c) * (n + 1) & 1)) & 1;  
        return res;
    }
	ll m = ((a * n + b) / c); 
    int tmp = gao(c, c - b - 1, a, m - 1); 
    return (((n * m) & 1) ^ tmp) & 1;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%lld", &n);
		up = min(25000000ll, n);
		ll ans = 0; 
		for (int i = 1; i <= up; ++i) {
			ans ^= (n % i);
		}
		for (ll i = up + 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
		   	ll lim = n - (n / j) * i;
			for (ll k = 1; k <= lim; k <<= 1)
				ans ^= gao(n / i, n % j, k, j - i) * k;
		}
		printf("%lld\n", ans);
	}
    return 0;
}
