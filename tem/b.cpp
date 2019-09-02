#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 1e7 + 10;
const int M = 1e7; 
int pri[N], check[N];
ll mu[N], f[N], g[N];
void sieve() {
	memset(check, 0, sizeof check);
	*pri = 0;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				break;
			} else mu[i * pri[j]] = -mu[i];
		}
	}
	for (int i = 1; i < N; ++i) f[i] = mu[i];
}

void get_g(int N, const ll *f, ll *g) {
  for (int i = 1; i <= N; i++) g[i] = f[i];
  for (int i = 1; i <= *pri; i++)
    for (int j = N / pri[i]; j >= 1; j--)
      g[j * pri[i]] = (g[j * pri[i]] - g[j]);
} // Magic! O(nloglogn)

int main() {
	sieve();
	get_g(M, f, g);
//	for (int i = 1; i <= M; ++i)
//		printf("%lld\n", g[i]);
	return 0;
}
