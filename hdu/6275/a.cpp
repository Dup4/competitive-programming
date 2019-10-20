#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef long long ll;
ll n, up;

inline ll sum(ll n) {
	if (n & 1) {
		return ((n + 1) / 2 * n) % 2;
	} else {
		return (n / 2) * (n + 1) % 2;
	}
}

int gao(ll a, ll b, ll c, ll n) {
    if (a == 0) {
        return (n + 1) & (b / c) & 1; 
    }
    if (a >= c || b >= c) { 
        ll tmp = gao(a % c, b % c, c, n);
        ll res = (tmp + (a / c) * sum(n) % 2 + (b / c) * (n + 1) % 2) % 2;  
        return res;
    }
	ll m = (a * n + b) / c; 
    ll tmp = gao(c, c - b - 1, a, m - 1); 
    ll res = (n * m % 2 - tmp + 2) % 2;
    return res;
}
 
int gogogo(ll c) {
	int tot = 0; 
	for (ll i = up + 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		tot += gao(n / i, n % j, c, j - i);
	}
	return tot % 2;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%lld", &n);
		up = min(50000000ll, n);
		ll ans = 0; 
		for (int i = 1; i <= up; ++i) {
			ans ^= (n % i);
		}
		ll res = 0;
		for (int i = 48; i >= 0; --i) {
			if (gogogo(1ll << i)) 
				res |= 1ll << i;
		}
	//	dbg(ans, res);	
		printf("%lld\n", res ^ ans);
	}
    return 0;
}
