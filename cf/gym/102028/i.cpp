#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
int n, a[N];
inline int dis(int x, int y) {
	if (x > y) swap(x, y);
	return a[y - 1] - a[x - 1];
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i < n; ++i) {
			scanf("%d", a + i);
			a[i] += a[i - 1];
		}
		ll res = 0, add = 0; int pre = -1, now;
		int l = 1, r = n;
		for (int i = 1; i <= n; ++i) {
			if (i & 1) {
				pre = l; ++l;
				res += add;
			} else {
				now = r; --r;
				add += dis(pre, now);
				res += add;
			}
			printf("%lld%c", res, " \n"[i == n]);
		}
	}
	return 0;
}
