#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, k;
char s[N], mp[220], nx[220]; 
int fmp[220];
int S[3][3][N];
int res;

void solve(int x, int l, int r) {
	int tmp = 0;
	int tot, has;
	tot = (r - l) / 3 + 1;
	has = S[(l - 1) % 3][x][r] - S[(l - 1) % 3][x][l - 1];
   	tmp += tot - has;

	tot = (r - l - 1) / 3 + 1;
	has = S[l % 3][(x + 1) % 3][r] - S[l % 3][(x + 1) % 3][l - 1];
	tmp += tot - has;

	tot = (r - l - 2) / 3 + 1;
	has = S[(l + 1) % 3][(x + 2) % 3][r] - S[(l + 1) % 3][(x + 2) % 3][l - 1];
	tmp += tot - has;
	
	res = min(res, tmp);
}

int main() {
	mp[0] = 'R'; fmp['R'] = 0;
	mp[1] = 'G'; fmp['G'] = 1;
	mp[2] = 'B'; fmp['B'] = 2;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		scanf("%s", s + 1);
		if (k <= 10) {
			res = 1e9;
			for (int i = 1; i <= n - k + 1; ++i) {
				int tmp = 0;
				for (int j = 0; j < 3; ++j) {
					int pre = j;
					for (int o = i + 1; o <= i + k - 1; ++o) {
						if (s[o] != mp[(pre + 1) % 3]) {
							++tmp;
						}
						pre = (pre + 1) % 3;
					}
				}
				res = min(res, tmp);
			}
			printf("%d\n", res);
			continue;
		}
		for (int k = 1; k <= n; ++k) {
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					S[i][j][k] = 0;
				}
			}
		}
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = i + 1; k <= n; k += 3) {
					S[i][j][k] = s[i] == mp[j]; 
					S[i][j][k] += S[i][j][k - 1];
				}
			}
		}
		res = 1e9;
		for (int i = 1; i <= n - k + 1; ++i) {
			for (int j = 0; j < 3; ++j) {
				solve(mp[j], i, i + k - 1);
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
