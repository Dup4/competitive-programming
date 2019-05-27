#include <bits/stdc++.h>
using namespace std;

#define N 2000010
#define M 100010
#define ll long long
ll n, m, p;
int prime[N];
bool check[N], vis[M];
ll f[N], F[N], phi[N]; 
template <class T>
void add(T &x, T y) {
	x += y;
	if (x >= p) {
		x -= p;
	}
}
template <class T>
void sub(T &x, T y) {
	x -= y;
	if (x < 0) {
		x += p;
	}
}

void init() {
	memset(check, 0, sizeof check);
	prime[0] = 0;
	phi[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++prime[0]] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= prime[0]; ++j) {
			if (1ll * i * prime[j] >= N) {
				break;
			}
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = 1ll * phi[i] * prime[j] % p;
				break;
			} else {
				phi[i * prime[j]] = 1ll * phi[i] * phi[prime[j]] % p;
			}
		}
	}
	for (int i = 1; i < N; ++i) {
		for (int j = i; j < N; j += i) {
			add(f[j], 1ll * i * phi[j] % p);
		}
	}
	for (int i = 2; i < N; ++i) {
		add(f[i], f[i - 1]);
	}
}

ll get_f(int x) {
	if (x < N) {
		return f[x];
	} else {
		return F[n / x];
	}
}

ll get_one(int n) {
	return (1ll * n * (n - 1) / 2) % p;
}
ll get_two(int n) {
	return (1ll * (n - 1) * (n - 1) % p + 2ll * (n - 1) % p + 1) % p;
}

void work(int x) {
	if (x < N) return;
	int t = n / x;
	if (vis[t]) return; vis[t] = 1; 
	F[t] = get_two(x);  
	for (int i = 2, j; i <= x; i = j + 1) {
		j = x / (x / i);
		work(x / i);
		sub(F[t], (get_one(j) - get_one(i - 1) + p) % p * get_f(x / i) % p); 
	}
}

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
	while (scanf("%lld%lld%lld", &n, &m, &p) != EOF) {
		memset(vis, 0, sizeof vis);
		init(); 
		ll res = 0;
		--p;
		for (int i = 1, j; i <= n; i = j + 1) { 
			j = n / (n / i);
			work(j); work(i - 1);
			add(res, 1ll * (n / i) * (n / i) % p * (get_f(j) - get_f(i - 1) + p) % p); 
		}
		++p; 
		printf("%lld\n", qmod(m, res));
	}
	return 0;
}
