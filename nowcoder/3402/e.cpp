#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int L, n, m, a[N];

bool ok(int x) {
	vector <int> vec;
	int del = 0;
	for (int i = 1; i <= n; ++i) { 
		if (L - a[i] >= x) {
			vec.push_back(a[i]);
		} else {
			++del;
		}
	}
	int pre = 0;
	for (auto &it : vec) {
		if (it - pre >= x) {
			pre = it;
		} else {
			++del;
		}
	}
	return del <= m;
}

int main() {
	while (scanf("%d%d%d", &L, &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) 
			scanf("%d", a + i);
		sort(a + 1, a + 1 + n);
		int l = 0, r = L, res = 0;
		while (r - l >= 0) {
			int mid = (l + r) / 2; 
			if (ok(mid)) {
				l = mid + 1;
				res = mid;
			} else {
				r = mid - 1;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
