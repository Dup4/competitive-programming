#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
int pri[N], check[N], mu[N], fac[N];
ll n;
void sieve() {
	memset(check, 0, sizeof check); 
	*pri = 0;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				break;
			} else mu[i * pri[j]] = -mu[i];
		}
	}
}
void getfac(ll x) {
	*fac = 0;
	for (int i = 1; 1ll * i * i <= x; ++i) {
		if (x % i == 0) {
			fac[++*fac] = i;
			if (1ll * i * i != x) fac[++*fac] = x / i;	
		}
	}
	sort(fac + 1, fac + 1 + *fac); 
}

ll S(int b) {
	ll res = 0;
	getfac(b);
	for (int i = 1, j; i < b && 1ll * b * (i + b) <= n; i = j + 1) {
		j = min(n / (n / b / (i + b)) / b - b, 1ll * b - 1);
		ll cnt = 0;
		for (int k = 1; k <= *fac; ++k) {
			cnt += mu[fac[k]] * (j / fac[k] - (i - 1) / fac[k]); 
		}
		res += n / b / (i + b) * cnt;
	}
	return res;
}

int main() {
	sieve();
	while (scanf("%lld", &n) != EOF) {
		ll res = 0;
		for (int i = 1; 1ll * i * (i + 1) <= n; ++i) {
			res += S(i); 
		}
		printf("%lld\n", res);
	}
	return 0;
}
