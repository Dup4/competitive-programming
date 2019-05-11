#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define M 1200010
const ll p = (1e9) + 7;
int n, a[N], b[N];
ll f[M];
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			a[i] ^= a[i - 1];
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", a[i], " \n"[i == n]);
		}
		ll res = 0;
		if (a[n] == 0) {
			int tot = 0; 
			for (int i = 1; i < n; ++i) {  
				tot += a[i] == 0; 
			}
			res = qmod(2, tot);
		} else {
			int x = a[n];
			ll tot = 0;
			res = 1;
			for (int i = 1; i < n; ++i) {
				if (a[i] == x) {
					tot = (tot + res) % p;
				} else if (a[i] == 0) {
					res = (res + tot) % p;  
				}
			}
		}
		printf("%lld\n", res); 
	}
	return 0;
}
