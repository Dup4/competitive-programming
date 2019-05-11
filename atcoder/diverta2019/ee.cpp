#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define M 1200010
const ll p = (1e9) + 7;
int n, a[N], b[N];
ll f[M], g[M];
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
		ll res = 0;
		if (a[n] == 0) {
			int tot = 0; 
			for (int i = 1; i < n; ++i) {  
				tot += a[i] == 0;  
			}
			res = qmod(2, tot);
		} 
		for (int i = 1; i <= n; ++i) {
			b[i] = a[i] == 0;
			b[i] += b[i - 1];  
		}
		for (int i = 1; i <= 1 << 20; ++i) {
			f[i] = 0;
			g[i] = 0;
		}	
		for (int i = 1; i <= n; ++i) {
			if (a[i]) {    
				(f[a[i]] += f[a[i]] * (b[i] - b[f[a[i]]]) % p) %= p;
				g[a[i]] = i;
			}
		}	
		if (a[n] == 0) {
			for (int i = 1; i <= 1 << 20; ++i) {
				(res += f[i]) %= p; 
			}
		} else {
			res = f[a[n]]; 
		}
		printf("%lld\n", res); 
	}
	return 0;
}
