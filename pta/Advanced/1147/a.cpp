#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, a[N];
vector <int> vec;

void dfs(int u) {
	if (u > n) return;
	dfs(u << 1);
	dfs(u << 1 | 1);
	vec.push_back(a[u]);
}

int main() {
	int _T; cin >> _T >> n;
	while (_T--) {
		int l = 0, g = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if (i > 1) {
				if (a[i] > a[i >> 1]) ++l;
				else ++g;
			}
		}
		if (l && g) puts("Not Heap");
		else if (l) puts("Min Heap");
		else puts("Max Heap");
		vec.clear();
		dfs(1);	
		for (int i = 0; i < n; ++i)
			printf("%d%c", vec[i], " \n"[i == n - 1]);
	}
	return 0;
}
