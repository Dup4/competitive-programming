#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl;}
template<class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
using ll = long long;
#define fi first
#define se second
const int N = 210, mod = 78294349;
ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}
int n, m, id, a[N][N], b[4][N][N], mp[N * N]; char s[N][N]; 
vector <vector<int>> G;
inline int f(int x, int y) { return (x - 1) * m + y; }  
void getid() {
	memset(a, -1, sizeof a);
	id = 0;
	for (int i = 1; i <= n; ++i) { 
		for (int j = 1; j <= m; ++j) { 
			if (s[i][j] == '#')
				a[i][j] = ++id;
		}
	}
}

//往上走
void up(int a[N][N], int b[N][N]) {
	for (int j = 1; j <= m; ++j) { 
		int id = 1;
		for (int i = 1; i <= n; ++i) {  
			if (a[i][j] != -1) {
				b[id][j] = a[i][j];
			   	++id;	
			}
		}
	}
}

void right(int a[N][N], int b[N][N]) {
	for (int i = 1; i <= n; ++i) {
		int id = m;
		for (int j = m; j >= 1; --j) {
			if (a[i][j] != -1) {
				b[i][id] = a[i][j];
				--id;
			}
		}
	}
}

void down(int a[N][N], int b[N][N]) {
	for (int j = 1; j <= m; ++j) {
		int id = n;
		for (int i = n; i >= 1; --i) {
			if (a[i][j] != -1) {
				b[id][j] = a[i][j];
				--id;
			}
		}
	}
}

void left(int a[N][N], int b[N][N]) {
	for (int i = 1; i <= n; ++i) {
		int id = 1;
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] != -1) {
				b[i][id] = a[i][j];
				++id;
			}
		}
	}
}

void build(int b[N][N]) {
	memset(mp, -1, sizeof mp);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (b[i][j] != -1) {
				mp[b[i][j]] = f(i, j);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] != -1) {
				G[f(i, j)].push_back(mp[a[i][j]]);
			}
		}
	}
}

int fa[N * N], sze[N * N];
int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) {
		if (sze[x] > sze[y]) swap(x, y);
		fa[x] = y;
		sze[y] += sze[x]; 
	}
}


int main() {
	int _T; scanf("%d", &_T);
	for (int kase = 1; kase <= _T; ++kase) {
		printf("Case %d: ", kase);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n * m; ++i) fa[i] = 0, sze[i] = 1;
		G.clear(); G.resize(n * m + 10);
		for (int i = 1; i <= n; ++i)
			scanf("%s", s[i] + 1);
		memset(b, -1, sizeof b);
		getid();
		up(a, b[0]);
		right(b[0], b[1]);
		down(b[1], b[2]);
		left(b[2], b[3]);
		build(b[3]);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (a[i][j] != -1) {
					int p = f(i, j);
					merge(p, G[p][0]);
				}
			}
		}
		map <int, int> fac; 
		for (int i = 1; i <= n; ++i) { 
			for (int j = 1; j <= m; ++j) { 
				if (a[i][j] != -1) {
					int p = f(i, j);
					if (fa[p] == 0) { 
						int len = sze[p];
						for (int k = 2; k * k <= len; ++k) {
							int c = 0;
							while (len % k == 0) {
								len /= k;
								++c;
							}
							fac[k] = max(fac[k], c);
						}
						if (len > 1) fac[len] = max(fac[len], 1);
					}
				}
			}
		}
		ll res = 1;
		for (auto &it : fac) res = res * qpow(it.fi, it.se) % mod;
		printf("%lld\n", res);
	}
	return 0;
}
