#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int f[N], g[N], n;


int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%d", f + i);
		for (int i = 0; i < n; ++i) scanf("%d", g + i);
		int Maxf = 0, Maxg = 0;
		for (int i = n - 1; i > 0; --i) {
			if (f[i]) {
				Maxf = max(Maxf, i);
			}
			if (g[i]) Maxg = max(Maxg, i);
		}
		if (Maxf < Maxg) puts("0/1");
		else if (Maxg < Maxf) puts("1/0");
		else {
			int F = f[Maxf], G = g[Maxg];
			int t = gcd(F, G);
			F /= t; G /= t;
			printf("%d/%d\n", F, G);
		}
	}
	return 0;
}
