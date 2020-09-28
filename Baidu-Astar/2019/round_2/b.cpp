#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int n, m, res[N]; 
char s[N][N], t[N][N];

bool check(int k, int i, int j) {
	return t[k][i] == s[k][j];
}

void gao() {
	memset(res, -1, sizeof res);
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= m; ++j) if (res[j] == -1) {
			bool F = 1;
			for (int k = 1; k <= n; ++k) {
				if (check(k, i, j) == 0) {
					F = 0;
					break;
				}
			}
			if (F) {
				res[j] = i;
				break;
			}
		}
	}
	for (int i = 1; i <= m; ++i) if (res[i] == -1) {
		puts("-1");
		return;
	}
	for (int i = 1; i <= m; ++i)
		printf("%d%c", res[i], " \n"[i == m]);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) scanf("%s%s", s[i] + 1, t[i] + 1);
		gao();
	}
	return 0;
}
