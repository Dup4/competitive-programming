#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
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
	while (scanf("%lld", &n) != EOF) {
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
	//	dbg(ans, res);	
		printf("%lld\n", ans);
	}
    return 0;
}
