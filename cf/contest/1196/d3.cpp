#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, k;
char s[N];
int R[N][3], G[N][3], B[N][3];

int work(int l, int r) {
	if (l == r) return 0;
	if (r - l + 1 == 2) {
		if (s[l] == 'R' && s[r] == 'G') return 0;
		if (s[l] == 'G' && s[r] == 'B') return 0;
		if (s[l] == 'B' && s[r] == 'R') return 0;
		return 1;
	}
	int res = 1e9, a, b, c;
	//R开头
	a = R[r][l % 3] - R[l - 1][l % 3];
	b = G[r][(l + 1) % 3] - G[l][(l + 1) % 3];
	c = B[r][(l + 2) % 3] - B[l + 1][(l + 2) % 3];
	res = min(res, a + b + c);

	//G开头
	a = G[r][l % 3] - G[l - 1][l % 3];
	b = B[r][(l + 1) % 3] - B[l][(l + 1) % 3];
	c = R[r][(l + 2) % 3] - R[l + 1][(l + 2) % 3];
	res = min(res, a + b + c);


	//B开头
	a = B[r][l % 3] - B[l - 1][l % 3];
	b = R[r][(l + 1) % 3] - R[l][(l + 1) % 3];
	c = G[r][(l + 2) % 3] - G[l + 1][(l + 2) % 3];
	res = min(res, a + b + c);
	return res;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		scanf("%s", s);
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j < 3; ++j) {
				R[i][j] = 0;
				G[i][j] = 0;
				B[i][j] = 0;
			}
		}
		for (int i = 0; i < n; ++i) {
			if (s[i] != 'R') ++R[i][i % 3];
			if (s[i] != 'G') ++G[i][i % 3];
			if (s[i] != 'B') ++B[i][i % 3];
			for (int j = 0; j < 3; ++j) {
				R[i][j] += R[i - 1][j];
				G[i][j] += G[i - 1][j];
				B[i][j] += B[i - 1][j];
			}
		}
		int res = 1e9;
		for (int i = 0; i + k - 1 < n; ++i) {
			res = min(res, work(i, i + k - 1));
		}
		printf("%d\n", res); 
	}
	return 0;
}
