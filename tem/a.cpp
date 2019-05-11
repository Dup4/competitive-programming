#include <bits/stdc++.h>
using namespace std;

#define N 11
int n, res[N];
int used[N][N];
bool ok(int x, int y) {
	for (int i = 1; i < x; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i + j == x + y || i - j == x - y || j == y) {
				if (used[i][j]) {
					return false;
				}
			}
		}
	}
	return true;	
}
void DFS(int cur) {
	if (cur == n + 1) {
		++res[n];
		return;
	}
	for (int i = 1; i <= n; ++i) {
		if (ok(cur, i)) {
			used[cur][i] = 1;
			DFS(cur + 1); 
			used[cur][i] = 0;
		}
	}
}

int main() {
	memset(res, -1, sizeof res);
	while (scanf("%d", &n), n) {
		if (res[n] != -1) {
			printf("%d\n", res[n]);
		} else {
			memset(used, 0, sizeof used);
			res[n] = 0;
			DFS(1);
			printf("%d\n", res[n]); 
		}
	}
	return 0;
}
