#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
char s[N], t[N]; int a[N][26], cnt[26], n, q, m;
inline int gao() {
	int res = 0;
	for (int i = 0; i < 26; ++i) if (cnt[i] > a[n][i]) return 0;
	for (int i = 1; i + m - 1 <= n; ++i) {
		int end = i + m - 1;
		if (s[i] != t[1] || s[end] != t[m]) continue;
		bool F = 1;
		for (int j = 0; j < 26; ++j) {
			if (a[end][j] - a[i - 1][j] != cnt[j]) {
				F = 0;
				if (a[n][j] - a[i - 1][j] < cnt[j]) return res;
				break; 
			}
		}
		res += F;
	}
	return res;
}
int main() {
	int T; cin >> T;
	while (T--) {
		scanf("%s", s + 1); n = strlen(s + 1);
		memset(a[0], 0, sizeof a[0]);
		scanf("%d", &q);
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 26; ++j)
				a[i][j] = a[i - 1][j];
			++a[i][s[i] - 'a'];  
		}
		while (q--) {
			scanf("%s", t + 1); m = strlen(t + 1);
			memset(cnt, 0, sizeof cnt);
			for (int i = 1; i <= m; ++i) ++cnt[t[i] - 'a'];
			printf("%d\n", gao());
		}
	}
	return 0;
}
