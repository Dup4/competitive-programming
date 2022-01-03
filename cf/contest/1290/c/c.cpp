#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
#define SZ(x) ((int)x.size())
const int N = 3e5 + 10, INF = 0x3f3f3f3f;
int n, k, res; char s[N]; 
vector <vector<int>> G;

struct UFS {
	struct node {
		int fa, rk, loc, sze[2];
		node() {}
		void init() { fa = 0; rk = 0; loc = 0; sze[0] = 1; sze[1] = 0; }
	}t[N];
	void init(int n) {
		for (int i = 1; i <= n; ++i)
			t[i].init(); 
	}
	pII find(int x) {
		if (t[x].fa == 0) return {x, t[x].loc};
		else {
			//尽量不要路径压缩 
			pII p = find(t[x].fa);
			p.se ^= t[x].loc;
			return p;
		}
	}
	//1 位于同一边
	//0 位于对立边
	void merge(int x, int y, int opt) {
		pII fx = find(x), fy = find(y);
		if (fx.fi == fy.fi) return;
		if (t[fx.fi].rk > t[fy.fi].rk) swap(fx, fy);
		t[fx.fi].fa = fy.fi;
		if (t[fx.fi].rk == t[fy.fi].rk) ++t[fy.fi].rk;
		res -= min(t[fx.fi].sze[0], t[fx.fi].sze[1]);
		res -= min(t[fy.fi].sze[0], t[fy.fi].sze[1]);
		//判断x和y的相对位置是否满足opt要求，不满足则改变x的位置
		if ((fx.se ^ t[fy.fi].loc ^ fy.se) == opt) {
			t[fx.fi].loc ^= 1;
			swap(t[fx.fi].sze[0], t[fx.fi].sze[1]);
		}
		t[fy.fi].sze[0] = min(INF, t[fy.fi].sze[0] + t[fx.fi].sze[0]);
		t[fy.fi].sze[1] = min(INF, t[fy.fi].sze[1] + t[fx.fi].sze[1]);
		res += min(t[fy.fi].sze[0], t[fy.fi].sze[1]);
	}
	//1 必选
	//0 必不选
	void set(int x, int opt) {
		pII fx = find(x);
		res -= min(t[fx.fi].sze[0], t[fx.fi].sze[1]);
		t[fx.fi].sze[fx.se ^ opt] = INF;
		res += min(t[fx.fi].sze[0], t[fx.fi].sze[1]);
	}
}ufs;

void run() {
	scanf("%s", s + 1);
	G.clear(); G.resize(n + 1); 
	ufs.init(k);
	for (int i = 1, x; i <= k; ++i) {
		scanf("%d", &x);
		for (int j = 0, y; j < x; ++j) {
			scanf("%d", &y);
			G[y].push_back(i); 
		}
	}
	res = 0;
	for (int i = 1; i <= n; ++i) {
		if (SZ(G[i]) == 1) {
			ufs.set(G[i][0], (s[i] - '0') ^ 1);
		} else if (SZ(G[i]) == 2) {	
			ufs.merge(G[i][0], G[i][1], (s[i] - '0'));
		} 
		printf("%d\n", res);
	}
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) run();
	return 0;
}
