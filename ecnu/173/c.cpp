#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, k;
int fa[11][N];
int find(int id, int x) {
	return fa[id][x] == 0 ? x : fa[id][x] = find(id, fa[id][x]);
}
void join(int id, int x, int y) {
	x = find(id, x); y = find(id, y);
	if (x != y) {
		fa[id][x] = y;
	}
}
map < vector <int>, int> mp; 
vector < vector <int> > vec;

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		vec.resize(n + 1);
		memset(fa, 0, sizeof fa);
		mp.clear();
		for (int i = 1, s, u, v; i <= k; ++i) {
			scanf("%d", &s);
			for (int j = 1; j <= s; ++j) {
				scanf("%d%d", &u, &v);
				join(i, u, v);
			}
		}
		for (int i = 1; i <= n; ++i) {
			vec[i].clear();
			for (int j = 1; j <= k; ++j) {
				vec[i].push_back(find(j, i));
			}	
			++mp[vec[i]];
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d\n", mp[vec[i]]);
		}
	}
	return 0;
}
