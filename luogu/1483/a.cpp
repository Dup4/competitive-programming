#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
int n, q, a[N];
ll f[N];

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		int op, x, y; ll res;
		while (q--) {
			scanf("%d%d", &op, &x);
			switch (op) {
				case 1 :
					scanf("%d", &y);
					f[x] += y;
					break;
				case 2 :
					res = a[x];
					for (int i = 1; 1ll * i * i <= x; ++i) if (x % i == 0) {
						res += f[i];
						if (1ll * i * i != x) {
							res += f[x / i]; 
						}
					}
					printf("%lld\n", res);
					break;
				default :
					assert(0);
			}
		}

	}
	return 0;
}
