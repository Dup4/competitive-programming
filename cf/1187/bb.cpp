#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, m, q;
char s[N], t[N]; 
vector <vector<int>> G;
int cnt[30];

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(30);
		scanf("%s", s + 1);
		for (int i = 1; i <= n; ++i) {
			G[s[i] - 'a'].push_back(i);
		}
		scanf("%d", &q);
		while (q--) {
			scanf("%s", t + 1); m = strlen(t + 1);
			memset(cnt, 0, sizeof cnt);
			for (int i = 1; i <= m; ++i) ++cnt[t[i] - 'a'];
			int res = 0;
			for (int i = 0; i < 26; ++i) {
				if (cnt[i]) {
					res = max(res, G[i][cnt[i] - 1]);
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
