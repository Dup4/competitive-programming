#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
ll n, k, a[N];
int m;

int main() {
	while (scanf("%lld%d%lld", &n, &m, &k) != EOF) {
		for (int i = 1; i <= m; ++i) scanf("%lld", a + i);
		ll lazy = 0;
		int res = 1, tot = 1;
		for (int i = 2; i <= m; ++i) {
			if ((a[i] - lazy - 1) / k != (a[i - 1] - lazy - 1) / k) {
				++res;
				lazy += tot; 
				tot = 1;
			} else {
				++tot;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
