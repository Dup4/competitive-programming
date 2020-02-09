#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 1e3 + 10;
int n, m, q, g[N][N], res; 

struct UFS {
	vector <int> fa, right;
	void init(int n) { 
		fa.clear(); fa.resize(n + 5); 
		right.clear(); right.resize(n + 5);
		for (int i = 1; i <= n; ++i) {
			fa[i] = 0;
			right[i] = i;
		}
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	int join(int x, int y) { 
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			fa[fx] = fy;
			right[fy] = max(right[fx], right[fy]);
			return 1;		
		}
		return 0;
	}
}ufs[N], _ufs;

int Move[][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};

inline int id(int x, int y) { return (x - 1) * m + y; }
inline bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m || g[x][y] == 0)
		return false;
	return true;
}
inline void add(int x, int y) {
	g[x][y] = 1;
	++res;
	for (int j = 0; j < 4; ++j) {
		int nx = x + Move[j][0];
		int ny = y + Move[j][1];
		if (ok(nx, ny)) {
			res -= _ufs.join(id(x, y), id(nx, ny));
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(g, 0, sizeof g); res = 0;
		_ufs.init(n * m);
		for (int i = 1; i <= n; ++i) ufs[i].init(m);
		for (int i = 1; i <= n; ++i) {
			static char s[N];
			scanf("%s", s + 1); 
			for (int j = 1; j <= m; ++j) {
				g[i][j] = s[j] - '0';
				if (g[i][j] == 1) {
					add(i, j);
				}
			}
		}
		scanf("%d", &q); 
		for (int i = 1, x[2], y[2]; i <= q; ++i) { 
			scanf("%d%d%d%d", x, y, x + 1, y + 1); 
			for (int j = x[0]; j <= x[1]; ++j) {
				for (int k = y[0], o; k <= y[1]; k = o + 1) {
					o = ufs[j].right[ufs[j].find(k)];
					if (o > y[1]) break;  
					if (g[j][o] == 0) add(j, o);
					ufs[j].join(o, o + 1); 
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
