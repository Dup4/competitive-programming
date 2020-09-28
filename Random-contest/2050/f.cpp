#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
int n, m;
ll f[N];

int main() {
	int T; cin >> T;
	while (T--) {
		scanf("%d%d", &n, &m);
		memset(f, -0x3f, sizeof f);
		f[0] = m;
		ll a, b, c;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld%lld", &a, &b, &c);
			for (int j = n; j >= 1; --j) {
				if (f[j] != -INFLL) {
					f[j] += c;
				}
				if (min(f[j - 1], b) > a) {  
					f[j] = max(f[j], min(f[j - 1], b) - a + c); 
				}
			}
			for (int j = n - 1; j >= 1; --j) {
				f[j] = max(f[j], f[j + 1]);
			}
			f[0] += c; 
		}
		int res = 0;
		for (int i = n; i >= 1; --i) {
			if (f[i] > 0) {
				res = i;
				break;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
