#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e6 + 10, M = 20, INF = 0x3f3f3f3f; 
int n, q, rt; 

struct E { int to, nx, w; }e[N << 1]; int h[N]; 
void initE(int n) { for (int i = 0; i <= n; ++i) h[i] = 0; }
void addedge(int u, int v, int w = 0) { e[++*h] = { v, h[u], w }; h[u] = *h;} 

struct RMQ {
	const static int B = 10;  
	pII Min[20][N / B + 5];
	pII pre[N], suf[N], ori[N];  
	int mm[N], pos[N], posl[N], posr[N], maskUnit[N], maskMin[B + 1][1 << (B + 1)]; 	
	int allMask(int x) { return ((1 << x) - 1); }
	int getMask(int l) { return maskUnit[pos[l]] >> (l - posl[pos[l]]); }
	pII qryblock(int l, int r) {
		if (l > r) return pII(INF, INF);
		int k = mm[r - l + 1];
		return min(Min[k][l], Min[k][r - (1 << k) + 1]); 
	}
	pII queryMin(int l, int r) {
		if (l > r) swap(l, r);
		if (pos[l] == pos[r]) {
			return ori[l - 1 + maskMin[r - l + 1][getMask(l)]];
		} else {
			return min(qryblock(pos[l] + 1, pos[r] - 1), min(suf[l], pre[r]));
		}
	}
	void build(int n, pII *a) {
		for (int i = 1; i <= B; ++i) {
			for (int j = 0; j < (1 << B); ++j) { 
				maskMin[i][j] = maskMin[i - 1][j];
				int now = i - 2 * __builtin_popcount(j & allMask(i));
				int pre = i - 1 ? maskMin[i - 1][j] - 2 * __builtin_popcount(j & allMask(maskMin[i - 1][j])) : -INF;
				if (now > pre) maskMin[i][j] = i; 
			}
		}
		mm[0] = -1;
		for (int i = 1; i <= n; ++i) {
			mm[i] = ((i & (i - 1)) == 0 ? mm[i - 1] + 1 : mm[i - 1]);
			ori[i] = pre[i] = suf[i] = a[i];
			pos[i] = (i - 1) / B + 1;
			if (i == 1 || pos[i] != pos[i - 1]) posl[pos[i]] = i;
			posr[pos[i]] = i;
		}
		for (int i = 1; i <= pos[n]; ++i) {
			for (int j = posl[i] + 1; j <= posr[i]; ++j) pre[j] = min(pre[j], pre[j - 1]);
			for (int j = posr[i] - 1; j >= posl[i]; --j) suf[j] = min(suf[j], suf[j + 1]);
			maskUnit[i] = 0;
			for (int j = posl[i]; j <= posr[i]; ++j) {
				if (j > 1 && ori[j].fi - ori[j - 1].fi == 1) maskUnit[i] |= (1 << (j - posl[i]));	
			}
			Min[0][i] = suf[posl[i]];
		}
		for (int j = 1; j <= mm[pos[n]]; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= pos[n]; ++i) {
				Min[j][i] = min(Min[j - 1][i], Min[j - 1][i + (1 << (j - 1))]);
			}
		}
	}
}st;

struct LCA {
	pII rmq[N << 1];
	int low[N], cnt;
	void dfs(int u, int fa, int dep) {
		rmq[++cnt] = pII(dep, u);
		low[u] = cnt;
		for (int i = h[u]; i; i = e[i].nx) {
			int v = e[i].to;   
			if (v == fa) continue;	
			dfs(v, u, dep + 1);
			rmq[++cnt] = pII(dep, u);
		}
	}
	void init(int rt, int n) {
		cnt = 0;
		dfs(rt, rt, 0);
		st.build(2 * n - 1, rmq);
	}
	int querylca(int u, int v) { return st.queryMin(low[u], low[v]).se; }
}lca;

int main() {
	scanf("%d%d%d", &n, &q, &rt);
	initE(n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		addedge(u, v);
		addedge(v, u);
	}
	lca.init(rt, n);
	for (int i = 1, u, v; i <= q; ++i) {
		scanf("%d%d", &u, &v);
		printf("%d\n", lca.querylca(u, v));
	}
	return 0;
}
