#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 +10;

int n, k;
int fa[11][maxn];
int cnt[maxn];

void Init() {
	for (int i = 0; i <= k; ++i) {
		for (int j = 1; j <= n; ++j) {
			fa[i][j] = j;		
		}
	}
	for (int i = 1; i <= n; ++i) {
		cnt[i] = 0;
	}
}

int find(int i, int x) {
	return fa[i][x] == x ? x : fa[i][x] = find(i, fa[i][x]);
}

void Unin(int i, int x, int y) {
	x = find(i - 1, x); 
	y = find(i, y);
	if(x != y) {
		fa[i - 1][x] = y;
	}
} 

int main() {
	while(~scanf("%d %d", &n, &k)) {
		Init();
		for (int i = 1, s, u, v; i <= k; ++i) {
			scanf("%d", &s);
			for (int j = 1; j <= s; ++j) {
				scanf("%d %d", &u, &v);
				Unin(i, u, v);
			}
		}
		for (int i = 1; i <= n; ++i) {
			cnt[find(k, i)]++;
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d\n", cnt[find(k, i)]);
		}
	}
	return 0;
}
