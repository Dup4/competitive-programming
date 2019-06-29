#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define N 5010
int n, m;
char s[N], t[N];
vector<vector<int>> work(char *s) {
	int len = strlen(s + 1);
	vector <vector<int>> f(len + 2);
	vector <int> nx(2, len + 1);
	for (int i = len; i >= 1; --i) {
		f[i] = a;
		a[s[i] - '0'] = i;
	}
	return f;
}


int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		scanf("%s%s", s + 1, t + 1);
		vector <vector<int>> f = work(s), g = work(t);
		vector <vector<int>> dp(n + 2, vector <int> (m + 2, INF));
		vector <vector<int>> ok(n + 2, vector <int> (m + 2, 0));
		dp[0][0] = 0;
		for (int i = 0; i <= n + 1; ++i) {
			for (int j = 0; j <= m + 1; ++j) {
				for (int k = 0; k <= 1; ++k) {
					int _i = f[i][k];
					int _j = g[j][k];
					dp[_i][_j] = min(dp[_i][_j], dp[i][j] + 1);
				}
			}
		}
		for (int i = n + 1; i >= 1; --i) {
			for (int j = m + 1; j >= 1; --j) {
				
			}
		}
		
		
	}
	return 0;
}
