#include <bits/stdc++.h>
using namespace std;

#define N 20000010
int n, k, p;
int a[N], mul, add;
int fac[N], inv[110], S[N];   

int C(int n, int m) {
	int x = S[n];
	int y = S[m] + S[n - m];  
	if (x == y) {
		return fac[n] * inv[fac[m]] % p * inv[fac[n - m]] % p;     
	} else {
		return 0;
	}
}

int main() {
	while (scanf("%d%d%d", &n, &k, &p) != EOF) {
		scanf("%d%d%d", &a[1], &mul, &add);   
		for (int i = 2; i <= n; ++i) {
			a[i] = (1ll * (a[i - 1] * mul + add) ^ (i - 1)) % p;
		}
		fac[0] = 1;
		for (int i = 1; i <= n + k; ++i) { 
			int t = i;
			S[i] = 0; 
			while (t % p == 0) {
				t /= p;
				++S[i];
			}
			S[i] += S[i - 1]; 
			fac[i] = (1ll * fac[i - 1] * t % p);
		}
		inv[1] = 1;
		for (int i = 2; i < p; ++i) {
			inv[i] = 1ll * inv[p % i] * (p - p / i) % p;
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			(res += C(n + k - i - 1, k - 1) * a[i] % p) %= p; 
		}
		printf("%d\n", res);
	}
	return 0;
}
