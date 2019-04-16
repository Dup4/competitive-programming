#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10000010
int prime[N], f[N], g[N], h[N];  
bool check[N];  
void init() {
	memset(check, 0, sizeof check);
	prime[0] = 0; f[1] = 0; g[1] = 0; h[1] = 0;  
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++prime[0]] = i;        
			f[i] = 1;  
			g[i] = i;  
			h[i] = 1;  
		}
		for (int j = 1; j <= prime[0]; ++j) {
			if (1ll * i * prime[j] >= N) break; 
			check[i * prime[j]] = 1;  
			if (i % prime[j] == 0) {
				g[i * prime[j]] = g[i] * prime[j];
				h[i * prime[j]] = h[i] + 1;
				int rem = i / g[i];   
				if (rem == 1) {
					f[i * prime[j]] = 1;
				} else { 
					f[i * prime[j]] = h[rem] == h[i * prime[j]] ? -f[rem] : 0;
				}
				break;
			} else {
				g[i * prime[j]] = prime[j];
				h[i * prime[j]] = 1;
				f[i * prime[j]] = h[i] == 1 ? -f[i] : 0;
			}
		}
	}
	for (int i = 2; i < N; ++i) {
		f[i] += f[i - 1]; 
	}
}

int main() {
	init();
	int T, n, m; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		if (n > m) swap(n, m);
		ll res = 0;
		for (int i = 1, j; i <= n; i = j + 1) {
			j = min(n / (n / i), m / (m / i));
			res += 1ll * (n / i) * (m / i) * (f[j] - f[i - 1]);
		}
		printf("%lld\n", res);
	}
	return 0;
}
