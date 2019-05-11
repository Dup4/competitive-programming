#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2000010
int n, m, k, a[N]; 
int Sta[N << 1], top;

int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		m = -m;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		ll res = 0; top = 0;
		ll tot = 0;
		for (int i = 1; i < k; ++i) {
			tot += a[i];
			if (a[i] > m) {
				Sta[++top] = i; 
			}
		}
		for (int i = k; i <= n; ++i) {
			tot += a[i];
			if (a[i] > m) {
				Sta[++top] = i;
			}
			for (; top > 0 && tot >= 0; --top) {
				int j = Sta[top];
				if (a[j] - m < tot + 1) {
					tot -= a[j] - m;
					res += a[j] - m;
					a[j] = m;
				} else {
					res += tot + 1;
					a[j] -= tot + 1;
					tot = -1; 
					break;
				}
			}
			tot -= a[i - k + 1];
		}
		printf("%lld\n", res);
	}
	return 0;
}
