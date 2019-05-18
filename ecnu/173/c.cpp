#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

int n, k;
int fa[11][maxn];
int cnt1[maxn];

void Init() {
	for (int i = 1; i <= n; ++i) {
		cnt1[i] = 0;
		fa[0][i] = 1;
		for (int j = 1; j <= k; ++j) {
			fa[j][i] = i;
		}
	}
}

int find(int i, int x) {
	return x == fa[i][x] ? fa[i][x] : fa[i][x] = find(i, fa[i][x]);
}

void mix(int i, int x, int y) {
	x = find(i, x), y = find(i, y);
	if(x != y) {
		fa[i][x] = y;
	}
}

int main() {
	while(~scanf("%d %d", &n, &k)) {
		Init();
		for (int i = 1, s, u, v; i <= k; ++i) {
			scanf("%d", &s);
			for (int j = 1; j <= s; ++j) {
				scanf("%d %d", &u, &v);
				if (find(i - 1, u) != find(i - 1, v)) continue;
				mix(i, u, v);
			}
		}
		for (int i = 1; i <= n; ++i) {
			int tmp = find(k, i);
			cnt1[tmp]++;
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d\n", cnt1[find(k, i)]);
		}
	}
	return 0;
}
