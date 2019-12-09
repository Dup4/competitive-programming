#include <bits/stdc++.h>
using namespace std;
const int N = 110, INF = 0x3f3f3f3f; 
int n, res, w[N], g[N][N], a[N][N], cnt[N];
char s[N];
int pow(int x, int y) {
	if (y < 0) return 0;
	int res = 1;
	for (int i = 1; i <= y; ++i)
		res *= x;
	return res;
}

void dfs(int cur, int cost) {
	if (cost >= res) return;
	if (cur > n) {
		res = cost;
		return;
	}
	for (int i = 1; i <= cur; ++i) {
		if (g[i][cur] && a[i][cur] == 0 && cnt[i] < 3) {
			++cnt[i];
			dfs(cur + 1, cost - pow(w[i], cnt[i] - 1) + pow(w[i], cnt[i]));
			--cnt[i];
		}
	}
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) cnt[i] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s + 1);
			for (int j = 1; j <= n; ++j) {
				g[i][j] = s[j] - '0';
			}
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s + 1);
			for (int j = 1; j <= n; ++j) {
				a[i][j] = s[j] - '0';
			}
		}
		for (int i = 1; i <= n; ++i)
			scanf("%d", w + i);
		res = INF;
		dfs(1, 0); 
		if (res == INF) res = -1;
		printf("%d\n", res);
	}
	return 0;
}
