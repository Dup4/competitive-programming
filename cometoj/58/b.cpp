#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, w[N];
ll S1, S2;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", w + i);
		S1 = S2 = 0;
		for (int i = 1; i <= n; ++i) {
			S1 += 1ll * w[i] * w[i];
			S2 += 1ll * 2 * w[i];
		}
		for (int i = 1; i <= n; ++i) {
			printf("%lld%c", S1 - S2 * w[i] + 1ll * n * w[i] * w[i], " \n"[i == n]);
		}
	}
	return 0;
}
