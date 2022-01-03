#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll p = 1e7 + 7;
const int N = 1e6 + 10;

int check[N];
int prime[N];

void Init() {
	check[1] = 1;
	*prime = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++*prime] = i;
		}
		for (int j = 1; j <= *prime; ++j) {
			if (i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

int n;

ll f(ll x) {
	ll res = 0;
	ll tmp = n;
	while (tmp) {
		res += tmp / x;
		tmp /= x;
	}
	return res;
}

int main() {
	Init();
	while (scanf("%d", &n) != EOF && n) {
		ll res = 1;
		for (int i = 1; i <= *prime && prime[i] <= n; ++i) {
			ll tmp = f(prime[i]);
			tmp++;
			tmp = tmp * (tmp + 1) / 2;
			tmp %= p;
			res = res * tmp % p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
