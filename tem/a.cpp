#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
int prime[N], check[N], mu[N], tot;
void init() {
	memset(check, 0, sizeof check);
	tot = 0;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++tot] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
			} else {
				mu[i * prime[j]] = mu[i] * mu[prime[j]];
			}
		}
	}
}
int x, m;

int f(int d) {
	int res = 0;
	for (int i = 1; i <= m; ++i) {
		res += __gcd(i, x) == d;
	}
	return res;
}

int g(int d) {
	int res = 0;
	int y = x / d;
	for (int i = 1; i <= y; ++i) {
		if (y % i == 0) {
			res += mu[i] * (m / (i * d));
		}
	}
	return res;
}

int h(int d) {
	int res = 0;
	int y = x / d;
	for (int i = 1; i <= m; ++i) {
		if (i % d == 0 && )
	}
}



int main() {
	init();
	cin >> x >> m;
	for (int i = 1; i <= x; ++i) {
		if (x % i == 0) {
			printf("%d %d\n", f(i), g(i));
		}
	}
	return 0;
}
