#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod = 1e9 + 7;
const int N = 1e5 + 10;
int n, m;
int fa[N], a[N], bit[32];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
	x = find(x); y = find(y);
	if (x != y) fa[x] = y;
}
vector <vector<int>> vec;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		vec.clear(); vec.resize(n + 1);
		for (int i = 1; i <= n; ++i) fa[i] = i;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			merge(u, v);
		}
		for (int i = 1; i <= n; ++i) vec[find(i)].push_back(i);
		ll res = 0;
		for (int i = 1; i <= n; ++i) if (!vec[i].empty()) {
			sort(vec[i].begin(), vec[i].end(), [&](int x, int y) {
				return a[x] < a[y]; 		
			});	
			memset(bit, 0, sizeof bit);
			for (auto it : vec[i]) {
				ll base = 0;
				for (int i = 0; i < 31; ++i) {
					if ((a[it] >> i) & 1) {
						base += 1ll * bit[i] * (1 << i) % mod;
						base %= mod;
						++bit[i]; 
					}
				}
				res += base * a[it];
				res %= mod;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
