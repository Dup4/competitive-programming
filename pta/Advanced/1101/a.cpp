#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, a[N], f[N], g[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		f[0] = -1, g[n + 1] = 1e9;
		for (int i = 1; i <= n; ++i) {
			f[i] = max(f[i - 1], a[i]);
		}
		for (int i = n; i >= 1; --i) {
			g[i] = min(g[i + 1], a[i]);
		}
		int res = 0;
		vector <int> vec;
		for (int i = 1; i <= n; ++i) {
			if (f[i - 1] < a[i] && g[i + 1] > a[i])
				++res,
				vec.push_back(a[i]);
		}
		printf("%d\n", res);
		for (int i = 0; i < res; ++i)
			printf("%d%c", vec[i], " \n"[i == res - 1]);
		if (!res) cout << endl;
	}
	return 0;
}
