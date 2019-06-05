#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, k;
ll a[N];


int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k); ++k;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
		}		
		if (k == 1) {
			printf("%lld\n", a[1]);
		} else {
			ll Min = 1e9, pos = -1; 
			for (int i = 1; i + k - 1 <= n; ++i) {
				ll mid = (a[i] + a[i + k - 1]) / 2;
				ll dis = max(mid - a[i], a[i + k - 1] - mid);
				if (dis < Min) {
					Min = dis;
					pos = mid;
				}
			}
			printf("%lld\n", pos);
		}
	}
	return 0;
}
