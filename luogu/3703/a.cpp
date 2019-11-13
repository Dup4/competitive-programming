#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m;
vector <vector<int>> G;



struct SEG {
	struct node {
		int Max, lazy;
		void init() { Max = lazy = 0; }
		void up(int x) {
			Max += x;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res; res.init();
			res.Max = max(Max, other.Max);
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) return;
		
	}
};

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		
	}
	return 0;
}
