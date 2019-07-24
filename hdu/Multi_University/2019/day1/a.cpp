#include <bits/stdc++.h>
using namespace std;

#define N 110
#define pii pair <int, int>
#define fi first
#define se second
int n, m;
vector <vector<pii>> vec;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		vec.clear(); vec.resize(n + 1);
		for (int i = 1, l, r, x; i <= m; ++i) {
			scanf("%d%d", &l, &r, &x);
			vec[r].push_back(pii(l, x));
		}

		
	}
	return 0;
}
