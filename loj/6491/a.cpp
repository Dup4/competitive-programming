#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N = 1e7 + 10; 
const int M = 1e5 + 10;
ull n, m, d[N + 10]; 
int pri[N], check[N];
void sieve() {
	memset(check, 0, sizeof check);
	*pri = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
	for (int i = 1; i < N; ++i) d[i] = i;
	for (int i = 1; i <= *pri; ++i) {
		for (int j = N / pri[i]; j >= 1; --j) {
			d[j * pri[i]] -= d[j]; 
		}
	}
	for (int i = 1; i < N; ++i) d[i] += d[i - 1];
}
inline ull qpow(ull base, ull n) {
	ull res = 1;
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1; 
	}
	return res; 
}
inline ull sum_2(ull x) {
	ull a = x;
	ull b = x + 1;
	if (a % 2 == 0) a /= 2;
	else b /= 2;
	return a * b;
} 

bool vis[M]; ull D[M];
ull getd(ull x) {
	if (x < N) return d[x];
	int t = n / x; 
	if (vis[t]) return D[t];
	vis[t] = 1;
	D[t] = sum_2(x);  
	for (ull i, j = 1; j < x; ) {
		i = j + 1;
		j = x / (x / i);
		D[t] -= (j - i + 1) * getd(x / i);
	}
	return D[t];
}

ull S(ull n) {
	ull res = 0;
	for (ull i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i); 
		res += qpow(n / i, m) * (getd(j) - getd(i - 1));
	}
	return res;
}

int main() {
	sieve();
	cin >> m >> n;
	memset(vis, 0, sizeof vis);
	cout << S(n) << "\n";
	return 0;
}

