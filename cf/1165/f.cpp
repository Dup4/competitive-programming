#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define pii pair <int, int>
#define fi first
#define se second
int n, m, tot, a[N], b[N];
vector < vector <int> > vec;

bool check(int x) {
	int cnt = tot;
	int now = x;
	int remind = 0;
	for (int i = 1; i <= n; ++i) {
		b[i] = a[i];
	}
	for (int i = min(200000, x); i >= 1; --i) {
		if (now > i) {
			remind += now - i;
			now = i;
		}
		for (auto it : vec[i]) {
			while (now > 0 && b[it] > 0) {
				--now;
				--b[it];
				--cnt;
			}
		}
	}
	remind += now;
	return remind >= 2 * cnt;
}

void init() {
	vec.clear();
	vec.resize(N);
	tot = 0;
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			tot += a[i];
		}
		for (int i = 1, d, t; i <= m; ++i) {
			scanf("%d%d", &d, &t);
			vec[d].push_back(t); 
		} 
		int l = 0, r = 400000, res = tot * 2;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				res = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}

