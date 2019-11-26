#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int n, m, fa[N], sze[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int u, int v) {
	int fu = find(u), fv = find(v);
	if (fu != fv) {
		fa[fu] = fv;
		sze[fv] += sze[fu];
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		m = n;
		for (int i = 1; i <= n; ++i) {
			fa[i] = i;
			sze[i] = 1;
		}
		for (int i = n + 1; i <= m + 1000; ++i) {
			fa[i] = i;
			sze[i] = 0;
		}
		for (int i = 1, sze; i <= n; ++i) {
			scanf("%d: ", &sze);
			int pre = -1;
			for (int j = 1, x; j <= sze; ++j) {
				scanf("%d", &x);
				m = max(m, n + x);
				merge(i, n + x);
				if (pre != -1) {
					merge(n + pre, n + x);
					pre = x;
				}
			}
		}
		vector <int> res;
		for (int i = 1; i <= m; ++i) {
			if (fa[i] == i && sze[i]) {
				res.push_back(sze[i]);
			}
		}
		sort(res.begin(), res.end());
		reverse(res.begin(), res.end());
		int sze = res.size();
		printf("%d\n", sze);
		for (int i = 0; i < sze; ++i) 
			printf("%d%c", res[i], " \n"[i == sze - 1]);
	}
	return 0;
}
