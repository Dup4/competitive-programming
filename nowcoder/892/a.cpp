#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, t, a[N], b[N];

int main() {
	while (scanf("%d%d", &n, &t) != EOF) {
		vector <int> vec;
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", a + i, b + i);
		}
		for (int i = 2; i <= n; ++i) {
			vec.push_back(a[i] - b[i - 1] + 1);
		}
		sort(vec.begin(), vec.end(), [&](int x, int y) {
			return x > y;
		});
		while (t >= 0 && !vec.empty()) {
			int x = vec.back();
			if (t >= x) {
				++res;
				t -= x;
				vec.pop_back();
			} else {
				break;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
