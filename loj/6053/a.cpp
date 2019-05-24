#include <bits/stdc++.h>
using namespace std;

#define N 101000
#define ll long long
const ll p = 1e9 + 7;
ll n;
int unit;
int prime[N], check[N], sum[N]; 
int g[N << 1], h[N << 1];  
void init(int n) {
	memset(check, 0, sizeof check);
	prime[0] = 0;
	for (int i = 2; i <= n; ++i) {
		if (!check[i]) {
			prime[++prime[0]] = i;
			sum[prime[0]] = (sum[prime[0] - 1] + i) % p;
		}
		for (int j = 1; j <= prime[0]; ++j) {
			if (1ll * i * prime[j] > n) {
				break;
			}
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				break;
			}
		}
	}
}

int main() {
	while (scanf("%lld", &n) != EOF) {
		init(unit = sqrt(n));


	}
	return 0;
}
