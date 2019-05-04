#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define pii pair <int, int>
#define fi first
#define se second
int n, m, x[N], y[N];
vector < vector <pii> > vec;

int dis(int x, int y) {
	int res = max(x, y) - min(x, y);
	return min(res, n - res);
}

bool solve() {
	int res = -1;
	for (int i = 1; i <= n; ++i) if (!vec[i].empty()) {
		sort(vec[i].begin(), vec[i].end(), [&](pii x, pii y) {
			return x.fi < y.fi;			
		});
		if (vec[i].size() == 1) {
			int tmp = dis((*vec[i].begin()).fi, (*vec[i].begin()).se);
			if (res == -1) {
				res = tmp;
			} else if (tmp % res == 0) {    
				res = tmp;
			} else {
				return false;
			}
		} else {
			for (int j = 0, sze = (int)vec[i].size(); j < sze - 1; ++j) {
				int tmp = dis(vec[i][j].fi, vec[i][j + 1].fi);
				if (res == -1) {
					res = tmp;
				} else if (tmp % res == 0) {
					res = tmp;
				} else {
					return false;
				}
			}
			int tmp = dis((*vec[i].begin()).fi, (*vec[i].rbegin()).fi);
			if (res == -1) {
				res = tmp;
			} else if (tmp % res == 0) {
				res = tmp;
			} else {
				return false;
			}
		}
	}
	return true;
}

void init() {
	vec.clear();
	vec.resize(n + 1);
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", x + i, y + i);
			int tmp = dis(x[i], y[i]);
			if (x[i] > y[i]) {
				swap(x[i], y[i]);
			}
			if (y[i] - x[i] > tmp) { 
				swap(x[i], y[i]);
			}
			vec[tmp].emplace_back(x[i], y[i]);  
		}
		puts(solve() ? "Yes" : "No");
	}
	return 0;
}
