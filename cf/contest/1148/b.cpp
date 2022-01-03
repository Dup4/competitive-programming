#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
#define INFLL 0x3f3f3f3f3f3f3f3f
int n, m, k;
ll ta, tb, a[N], b[N], c[N]; 

int main() {
	while (scanf("%d%d%lld%lld%d", &n, &m, &ta, &tb, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%lld", b + i);
		}
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + m);
		ll Min = 0;
		for (int i = 0, j = 1; j <= m; ++j) {
			while (i < n && a[i + 1] + ta <= b[j]) {
				++i;
			}
			c[j] = i; 
		}
		c[0] = 0;
		b[m + 1] = INFLL; 
		for (int i = 0; i <= m; ++i) {
			if (c[i] > k) {
				break;
			}
			int remind = k - c[i];
			Min = max(Min, b[min(m + 1, i + remind + 1)] + tb);
		}
		if (Min >= INFLL) {
			Min = -1;
		}
		printf("%lld\n", Min);
	}
	return 0;
}
