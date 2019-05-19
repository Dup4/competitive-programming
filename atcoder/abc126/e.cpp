#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, m;
int pre[N], sze[N];
int find(int x) {
	return pre[x] == 0 ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) {
		if (sze[x] > sze[y]) {
			swap(x, y);
		}	
		pre[x] = y;
		sze[y] += sze[x];
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			pre[i] = 0;
			sze[i] = 1;
		}
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			join(u, v);
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			if (find(i) == i) {
				++res;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
