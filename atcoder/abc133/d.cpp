#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, a[N];
ll b[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		b[1] = 0;
		for (int i = 1; i <= n; ++i) {
			b[1] += a[i] * ((i & 1) ? 1 : -1);
		}
		b[n] = 2ll * a[n] - b[1]; 
		for (int i = n - 1; i > 1; --i) {
			b[i] = 2ll * a[i] - b[i + 1];
		}
		for (int i = 1; i <= n; ++i) printf("%lld%c", b[i], " \n"[i == n]);	
	}
	return 0;
}
