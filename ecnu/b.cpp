#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 1e9 + 7;
ll a, b, c, d, limit, D;
int vis[100010];  
ll f[50];
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;  
}
ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}
ll solve() {
	ll res = 0;
	f[0] = 1;
	for (int j = 2; j <= D; ++j) {
		if (vis[j]) {
			continue;   
		}
		f[1] = j;
		for (int i = 2; i <= 30; ++i) {
			f[i] = f[i - 1] * j;
			if (f[i] > c) {  
				break;
			}
			for (int k = 1; k < i; ++k) { 
				if (f[k] > a) {
					break;
				}
				ll LCM = lcm(k, i);
				//printf("%lld %lld %lld %lld\n", f[i], f[k], b / (LCM / i), d / (LCM / k));
				(res += min(b / (LCM / k), d / (LCM / i))) %= p;
			}
		}
	}
	return res;	
}

int main() {
	memset(vis, 0, sizeof vis);
	for (int i = 2; i <= 1000; ++i) {
		for (ll j = 1ll * i * i; j <= 100000; j *= i) {
			vis[j] = 1;
		}
	}
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
		ll res = 0;
		res = min(a, c) * min(b, d) % p;
		(res += b * d % p + p - min(b, d)) %= p;
		limit = max(a, c); D = sqrt(limit) + 5;
		(res += solve()) %= p;
		swap(a, c);  
		swap(b, d);
		(res += solve()) %= p;
		printf("%lld\n", res);
	}
	return 0;
}
