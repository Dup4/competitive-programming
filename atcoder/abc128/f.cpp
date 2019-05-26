#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, a[N];

ll f(int A, int B) {
	ll res = 0;
	int now = 0;
	set <int> s;
	while (1) {
		now += A;
		if (s.find(now) != s.end()) {
			return 0;
		}
		s.insert(now);
		res += a[now];
		if (now == n - 1) {
			return res;
		}
		now -= B;
		if (s.find(now) != s.end()) {
			return 0;
		}
		s.insert(now);
		res += a[now];
		if (now == n - 1) {
			return res;	
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", a + i);
		}
		ll res = 0;
		for (int A = 1; A < n - 1; ++A) {
			int m = n - 1 - A;
			for (int i = 1; 1ll * i * i <= m; ++i) { 
				if (m % i == 0) {
					int x = i, y = m / i;
					if (x < A) {
						res = max(res, f(A, A - x)); 
						//printf("%d %d %lld\n", A, A - x, res);
					}
					if (y < A && x != y) {
						res = max(res, f(A, A - y));
						//printf("%d %d %lld\n", A, A - y, res);
					}
				}
			}
		}
		printf("%lld\n", res); 
	}
	return 0;
}
