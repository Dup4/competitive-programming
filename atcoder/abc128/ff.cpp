#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n;
ll s[N];
int used[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i) {
			scanf("%lld", s + i);
		}
		memset(used, 0, sizeof used); 
		ll res = 0;
		for (int C = 1; C <= n; ++C) {
			ll tmp = 0; 
			for (int k = 1; 1ll * k * C < n; ++k) { 	
				int a = k * C;
				int b = n - 1 - k * C;
				int A = b, B = b - C;
				if (A <= 0 || B <= 0) break;
				if (a < 0 || a >= n || b < 0 || b >= n || a == b) break; 
				if (used[a] == C || used[b] == C) {
					break;
				}
				used[a] = C;
				used[b] = C;
				tmp += s[a];
				tmp += s[b];
				res = max(res, tmp);
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
