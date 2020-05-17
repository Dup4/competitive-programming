#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
int n, m, K, h;
const int N = 15;
char g[N][N];
int a[N][N], vis[N * N];

inline int id(int x, int y) { return (x - 1) * m + y; }

unordered_map <ll, int> mp;

int fa[N * N], sze[N * N];
int find(int x) { return fa[x] == -1 ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) {
		fa[x] = y;
		sze[y] += sze[x];
	}
}

int Move[][2] = {
	-1, 0,
	0, -1,
	1, 0,
	0, 1, 
};

inline bool valid(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m)
		return 0;
	return 1;
}

inline bool ok(ll sta) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int ID = id(i, j);
			fa[ID] = -1;
			sze[ID] = (g[i][j] != '.');
			a[i][j] = ((sta >> ID) & 1);
			vis[ID] = a[i][j] ^ 1;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) if (a[i][j] == 0) {
			for (int k = 0; k < 2; ++k) {
				int ni = i + Move[k][0];
				int nj = j + Move[k][1];
				if (valid(ni, nj) && a[ni][nj] == 0) {
					merge(id(i, j), id(ni, nj));
					if (sze[find(id(i, j))] > 1)
						return false;
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) if (g[i][j] == 'o') {
			if (sze[find(id(i, j))] > 1) {
				return false;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) if (vis[id(i, j)] == 1) {
			for (int k = 0; k < 4; ++k) {
				int ni = i + Move[k][0];
				int nj = j + Move[k][1];
				if (!valid(ni, nj)) {
					vis[find(id(i, j))] = 0;
					vis[id(i, j)] = 0;
					break;
				}
			}		
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (fa[id(i, j)] == -1) {
				cnt += vis[id(i, j)];
			}
		}
	}
	return cnt == h;
}

void bfs() {
	int res = 0;
	queue <ll> que;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (g[i][j] == '.') {
				ll x = 1ll << id(i, j);
		//		dbg(i, j, x);
				que.push(x);
				mp[x] = 1;
			}
		}
	}
	while (!que.empty()) {
		ll sta = que.front(); que.pop();
		if (__builtin_popcountll(sta) == K) {
	//		if (ok(sta)) dbg(sta);
	//		for (int i = 1; i <= n; ++i)
	//			printf("%s\n", g[i] + 1);
			res += ok(sta);
			continue;
		}
		if (__builtin_popcountll(sta) > K) continue;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				int ID = id(i, j);
				if (g[i][j] == '.' && ((sta >> ID) & 1) == 0) {
					for (int k = 0; k < 4; ++k) {
						int ni = i + Move[k][0];
						int nj = j + Move[k][1];
						if (valid(ni, nj) && ((sta >> id(ni, nj)) & 1) == 1) {
							ll nx = sta ^ (1ll << ID);
							if (mp.count(nx) == 0) {
								que.push(nx);
								mp[nx] = 1;
							}
							break;
						}
					}
				}
			}
		}
	}
	printf("%d\n", res);
}


int main() {
	scanf("%d%d%d%d", &n, &m, &K, &h);
	for (int i = 1; i <= n; ++i) scanf("%s", g[i] + 1);
	bfs();
	return 0;
}
