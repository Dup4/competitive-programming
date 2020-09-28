#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 40000010
#define M 50010
#define pii pair <int, int>
#define fi first
#define se second
int n, m, a, p, cir;
int prime[M], check[M];
int mu[M];
void init() {
	memset(check, 0, sizeof check);
	prime[0] = 0;
	mu[1] = 1;
	for (int i = 2; i < M; ++i) {
		if (!check[i]) {
			prime[++prime[0]] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= prime[0]; ++j) {
			if (1ll * i * prime[j] >= M) {
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
	for (int i = 2; i < M; ++i) {
		(mu[i] += mu[i - 1] + p) %= p;
	}
}

int fib[N];
ll qmod(ll base, ll n, ll p) {
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
int F[M]; 
ll g(int n, int m) {
	if (n > m) {
		swap(n, m);
	}
	ll res = 0;
	for (int i = 1, j; i <= n; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		(res += 1ll * (mu[j] - mu[i - 1] + p) % p * (n / i) % p * (m / i) % p) %= p;
	}
	return res;	
}

int main() {
	while (scanf("%d%d%d%d", &n, &m, &a, &p) != EOF) {
		init();
		cir = 2;
		fib[1] = 1; fib[2] = 1; 
		for (int i = 3; ; ++i) {
			fib[i] = (fib[i - 1] + fib[i - 2]) % p;
			if (fib[i] == 1 && fib[i - 1] == 1) {
				cir = i - 2;
				break;
			}
		}
		if (n > m) {
			swap(n, m);
		}
		int b = a;
		for (int i = 1; i <= n; ++i) {
			F[i] = fib[(b - 1 + cir) % cir];
			F[i] = (F[i] + F[i - 1]) % p;
			b = (1ll * b * a) % cir; 
		}
		ll res = 0;
		for (int i = 1, j; i <= n; i = j + 1) { 
			j = min(n / (n / i), m / (m / i));
			(res += 1ll * (F[j] - F[i - 1] + p) % p * g(n / i, m / i) % p) %= p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
