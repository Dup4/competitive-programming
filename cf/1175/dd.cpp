#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define N 300010
int n, k;
ll a[N];


int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {  
			scanf("%lld", a + i);
		}
		for (int i = n - 1; i >= 0; --i) {
			a[i] += a[i + 1];
		}
		sort(a + 2, a + n + 1, [&](int x, int y) {
			return x > y;		
		});
		ll ans = 0;
		for (int i = 1; i <= k; ++i) {
			ans += a[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
