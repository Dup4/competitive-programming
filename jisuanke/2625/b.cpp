#include <bits/stdc++.h>
using namespace std;

#define N 3000010
#define M 100010
#define ll long long
ll n, m, p;
int prime[N];
bool check[N], vis[M];
ll f[N], g[N], F[N];      
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
	memset(f, 0, sizeof f);
	memset(check, 0, sizeof check);
	memset(vis, 0, sizeof vis);
	prime[0] = 0;
	f[1] = 1;
	g[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++prime[0]] = i;
			g[i] = i;
			f[i] = 2 * i - 1;
		}
		for (int j = 1; j <= prime[0]; ++j) {
			if (1ll * i * prime[j] >= N) {
				break;
			}
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				g[i * prime[j]] = g[i] * prime[j];
				f[i * prime[j]] = f[i / g[i]] * (f[g[i]] * prime[j] % p + 1ll * (prime[j] - 1) * g[i] % p) % p;   
				break;
			} else {
				g[i * prime[j]] = prime[j]; 
				f[i * prime[j]] = f[i] * f[prime[j]] % p;
			}
		}
	}
	for (int i = 2; i < N; ++i) {
		add(f[i], f[i - 1]);  
	}
}

ll sumn(int n) {
	return (1ll * n * (n + 1) / 2) % p;
}

ll get_d(int n) {
	ll res = 0;
	for (int i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		add(res, 1ll * (sumn(j) - sumn(i - 1) + p) % p * sumn(n / i));
	}   
	return res;
}

ll get_f(int x) {
	if (x < N) return f[x];
	int t = n / x;
	if (vis[t]) return F[t]; vis[t] = 1; 
	F[t] = get_d(x);  
	for (int i = 2, j; i <= x; i = j + 1) {
		j = x / (x / i);
		sub(F[t], 1ll * (j - i + 1) % p * get_f(x / i) % p); 
	}
	return F[t];
}

ll qmod(ll base, ll n) {
	base %= p;  
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
		--p;
		init(); 
		ll res = 0;
		for (int i = 1, j; i <= n; i = j + 1) { 
			j = n / (n / i);
			add(res, 1ll * (n / i) * (n / i) % p * (get_f(j) - get_f(i - 1) + p) % p); 
		}
		++p; 
		printf("%lld\n", qmod(m, res));
	}
	return 0;
}
