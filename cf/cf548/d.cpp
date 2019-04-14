#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = (ll)1e9 + 7;
int n;
int prime[N], mu[N];
bool check[N];
vector <int> fac[N]; 
void init() {
	memset(check, 0, sizeof check);
	prime[0] = 0;
	mu[1] = 1; 
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++prime[0]] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= prime[0]; ++j) {
			if (1ll * i * prime[j] >= N) {
				break;
			}
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			} else {
				mu[i * prime[j]] = -mu[i]; 
			}
		}
	}
	for (int i = 2; i < N; ++i) {
		mu[i] = (mu[i - 1] + mu[i] + p) % p;
	}
	for (int i = 1; i < N; ++i) {
		for (int j = i * 2; j < N; j += i) {
			fac[j].push_back(i); 
		}
	}
	for (int i = 1; i < N; ++i) {
		sort(fac[i].begin(), fac[i].end()); 
	}
}
ll f[N], inv[N]; 
ll get(int n) {
	ll res = 0;
	for (int i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i); 
		res = (res + (1ll * (n / i) * (mu[j] - mu[i - 1] + p) % p) % p) % p;   
	}
	return res;
}
ll get2(int a, int b, int d) {
	if (a > b) swap(a, b);
	a /= d, b /= d;
	ll res = 0;
	for (int i = 1, j; i <= a; i = j + 1) {
		j = min(a / (a / i), b / (b / i)); 
		res = (res + (mu[j] - mu[i - 1] + p) % p * 1ll * (a / i) % p * (b / i) % p) % p;  
	}
	return res;
}

int main() {
	init();
	while (scanf("%d", &n) != EOF) {
		inv[1] = 1;
		for (int i = 2; i <= n; ++i) {
			inv[i] = inv[p % i] * (p - p / i) % p;
		}
		f[1] = 1;
		for (int i = 2; i <= n; ++i) {
			ll t = 0;
			for (auto it : fac[i]) { 
				t = (t + f[it] * ((get2(n, i, it) - get2(n, i - 1, it) + p) % p) % p) % p;
			}
			f[i] = (1 + t * inv[n] % p) % p;
			f[i] = f[i] * n % p * inv[n - n / i] % p;
		}
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			res = (res + f[i]) % p;
		}
		printf("%lld\n", res * inv[n] % p);
	}
	return 0;
}
