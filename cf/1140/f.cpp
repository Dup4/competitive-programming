#include <bits/stdc++.h>
using namespace std;

/*
	CF 1140F
	每次给出一个点，如果该点不存在，就在平面中加入这个点
	否则，删去这个点
	
	每次加入一个点合并x和y，每个连通块的贡献是集合中x的个数乘y的个数
	对于每次操作后，输出当前所有连通块的贡献和
*/
#define ll long long
#define N 600010
#define pii pair <int, int>
#define fi first
#define se second
int n; 
vector <pii> Po;
map <pii, int> mp;  
int pre[N], sze[N];
ll cx[N], cy[N], ans[N], res;   
pii Sta[N << 2]; int Top;
//不要路径压缩，因为合并cx[]和cy[]的时候会有问题，用按秩合并或者启发式合并
int find(int x) {
	return pre[x] == 0 ? x : find(pre[x]);   
} 

struct SEG {
	vector < vector < pii> > a; 
	void init(int n) {
		a.resize(n * 4 + 10); 
	}
	//以时间轴建线段树
	//考虑一个点存在的时间区间为[ql, qr]，那么每个[l, l]这样的区间就是表示第l次操作后的答案
	void ins(int id, int l, int r, int ql, int qr, pii P) {
		if (l >= ql && r <= qr) {
			a[id].push_back(P);
			return;
		}	
		int mid = (l + r) >> 1;
		if (ql <= mid) ins(id << 1, l, mid, ql, qr, P);
		if (qr > mid) ins(id << 1 | 1, mid + 1, r, ql, qr, P);
	}
	void work(int id, int l, int r) {
		int T = Top; 
		for (auto it : a[id]) {
			int x = find(it.fi), y = find(it.se);
			if (x != y) { 
				//启发式合并 因为启发式合并具有前缀加减性质，方便回滚
				if (sze[x] > sze[y]) { 
					swap(x, y);
				}
				Sta[++Top] = pii(x, y);
				pre[x] = y;  
				res -= cx[x] * cy[x] + cx[y] * cy[y];
				sze[y] += sze[x]; cx[y] += cx[x]; cy[y] += cy[x];
				res += cx[y] * cy[y];
			}
		}
		if (l == r) {
			ans[l] = res;
		} else {
			int mid = (l + r) >> 1;
			work(id << 1, l, mid);
			work(id << 1 | 1, mid + 1, r);
		}
		//回滚操作 
		while (Top != T) {
			int x = Sta[Top].fi, y = Sta[Top].se; --Top;
			pre[x] = 0;
			res -= cx[y] * cy[y];
			sze[y] -= sze[x]; cx[y] -= cx[x]; cy[y] -= cy[x];
			res += cx[x] * cy[x] + cx[y] * cy[y];
		}
	}
}seg;

void init() {
	Po.resize(n + 1);
	seg.init(n);
	mp.clear(); 
	Top = 0; res = 0;
	memset(cx, 0, sizeof cx);
	memset(cy, 0, sizeof cy);
	for (int i = 1; i < N; ++i) {
		(i <= 300000 ? cx:cy)[i] = sze[i] = 1;
		pre[i] = 0;
	}
}
int main() {
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &Po[i].fi, &Po[i].se);
			Po[i].se += 300000; 
			if (mp.find(Po[i]) != mp.end()) {
				seg.ins(1, 1, n, mp[Po[i]], i - 1, Po[i]);
				mp.erase(Po[i]); 
			} else {
				mp[Po[i]] = i;
			}
		}
		for (auto it : mp) {
			seg.ins(1, 1, n, it.se, n, it.fi);
		}
		seg.work(1, 1, n);
		for (int i = 1; i <= n; ++i) {
			printf("%lld%c", ans[i], " \n"[i == n]);   
		}
	}
	return 0;
}
