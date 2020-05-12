#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10, INF = 0x3f3f3f3f;
int t, n, cnt[N], f[N]; char s[110];
vector <int> g[N];

inline void chmin(int &x, int y) { if (x > y) x = y; }

int main() {
	freopen("tests.in", "r", stdin);
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &t, &n);
		for (int i = 0; i < (1 << t); ++i) cnt[i] = 0, f[i] = INF, g[i].clear(); 
		f[0] = 0;
		int more = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s);
			int res = 0;
			for (int j = 0; j < t; ++j) {
				if (s[j] == '1') {
					res |= 1 << j;
				}
			}
			if (res == (1 << t) - 1) more += t - 1; 
			else ++cnt[res];
		}
		for (int j = 0; j < t; ++j) {
			for (int i = 0; i < 1 << t; ++i) {
				if (!(i >> j & 1))
					cnt[i] += cnt[i ^ (1 << j)];
			}
		}
		for (int i = 1; i < 1 << t; ++i) {
			for (int j = 0; j < t; ++j) {
				if ((i >> j) & 1) {
					int nx = i ^ (1 << j);
					g[nx].push_back(j);
					if (f[nx] < f[i] || (f[nx] == f[i] && g[nx] < g[i])) {
						f[i] = f[nx];
						g[i] = g[nx];
					} 
					g[nx].pop_back();
				}
			}
			f[i] += cnt[i];
		}
		printf("%d\n", f[(1 << t) - 1] + n + more);
		for (int i = 0; i < t; ++i)
			printf("%d%c", g[(1 << t) - 1][i] + 1, " \n"[i == t - 1]);
	}
	return 0;
}
