#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
int n, m, p;
ll a[N], b[N], f[N];

ll lcm(ll a, ll b) {
	return a / __gcd(a, b) * b;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &p);
		for (int i = 0; i <= p; ++i) a[i] = 0, b[i] = 0;
		for (int i = 0; i < p; ++i) {
			a[i] = n / p + (n % p >= i); 
			b[i] = m / p + (m % p >= i);
		}
		--a[0]; --b[0];
		a[p] = a[0]; b[p] = b[0];  
		for (int i = 1; i <= p; ++i) {
			f[i] = 0;
			for (int j = i; j <= p; j += i) {
				f[i] += b[j];
			}
		}
		ll res = 0;
		for (int i = 1; i <= p; ++i) {
			ll LCM = lcm(i, p);
			ll base = LCM / i;
			res += a[i] * f[base];
		}
		printf("%lld\n", res);
	}
	return 0;
}
