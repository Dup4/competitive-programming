#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
const ll p = 998244353;
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				for (int k = j + 1; k <= n; ++k) {
					(res += (a[i] ^ a[j]) % p * (a[j] ^ a[k]) % p * (a[i] ^ a[k]) % p) %= p;
				}
			}
		}
		printf("%lld\n", res);
	}	
	return 0;
}
