#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
#define SZ(x) (int(x.size()))
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 2e6 + 10, M = 2e5 + 10;
const int mod = 1e9 + 7, inv2 = (mod + 1) / 2;
int n, m, K;


struct UFS {
	int fa[N]; ll sze[N]; 
	int tot;
	void init() { tot = 0; }
	int newnode(ll _sze) {
		++tot;
		fa[tot] = 0;
		sze[tot] = _sze;
		return tot;
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (sze[fx] > sze[fy]) swap(fx, fy);
			fa[fx] = fy;
			sze[fy] += sze[fx];
			return true;
		}
		return false;
	}
}ufs;

inline ll C(ll n) {
	return (1ll * (n % mod) * ((n - 1) % mod) % mod * inv2 % mod + n % mod) % mod;  
}

struct E { 
	int l, r, id; 
	bool cross(const E &other) const {
		if ((l >= other.l && l <= other.r) ||
			(r >= other.l && r <= other.r) ||
		   	(other.l >= l && other.l <= r) ||
			(other.r >= l && other.r <= r))
			return 1;
		return 0;
	}
};

vector <vector<int>> vec(M);
vector <vector<E>> seg(M); 

vector <int> has;

void gao() {
	if (K == 0) {
		ll res = C(1ll * n * m);
		printf("%lld\n", res);
		return;
	}
	ufs.init();
	sort(has.begin(), has.end());
	has.erase(unique(has.begin(), has.end()), has.end());
	for (int i = 0; i < SZ(has); ++i) {
		int p = has[i];
		int pre = 0;
		sort(vec[p].begin(), vec[p].end());
		for (auto &it : vec[p]) {
			if (it - 1 > pre) { 
				E tmp = {pre + 1, it - 1, ufs.newnode(it - 1 - pre)};
		//		dbg(tmp.l, tmp.r, tmp.id, ufs.sze[tmp.id]);
				seg[p].push_back(tmp);
			}
			pre = it;
		}
		if (pre < m) {
			E tmp = {pre + 1, m, ufs.newnode(m - pre)};
			seg[p].push_back(tmp);
		}
	//	for (auto &it : seg[p]) {
	//		dbg(it.l, it.r);
	//	}
		if (i == 0) {
			if (p > 1) { 
				int node = ufs.newnode(1ll * (p - 1) * m);
				for (auto &it : seg[p]) {
					ufs.merge(node, it.id);
				}
			}
		} else {
			int preP = has[i - 1];
			if (preP + 1 < p) {
				int node = ufs.newnode(1ll * (p - preP - 1) * m);
				for (auto &it : seg[p]) {
					ufs.merge(node, it.id);
				}
				for (auto &it : seg[preP]) {
					ufs.merge(node, it.id);
				}
			} else {
				int pos = 0;
				for (auto &it : seg[p]) {
					while (pos < SZ(seg[preP])) {
						E it2 = seg[preP][pos];
						if (it.cross(it2)) {
							ufs.merge(it.id, it2.id);
						} 
						if (it2.r <= it.r) ++pos;
						else break;
					}
				}
			}
		} 
		if (i == SZ(has) - 1) {
			if (p < n) {
				int node = ufs.newnode(1ll * (n - p) * m);
			//	dbg(ufs.sze[node]);
				for (auto &it : seg[p]) {
					ufs.merge(node, it.id);
			//		dbg(it.l, it.r, it.id, ufs.sze[node]);
				}
			}
		}
		
	}
	for (auto &it : has) {
		vec[it].clear();
		seg[it].clear();
	}
	ll res = 0;
	for (int i = 1; i <= ufs.tot; ++i) {
		if (ufs.fa[i] == 0) {
			//dbg(i, ufs.sze[i]);
			res += C(ufs.sze[i]);
			res %= mod;
		}
	}
	printf("%lld\n", res);
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d%d", &n, &m, &K);
		has.clear();
		for (int i = 1, x, y; i <= K; ++i) {
			scanf("%d%d", &x, &y);
			has.push_back(x);
			vec[x].push_back(y);
		}
		gao();
	}
	return 0;
}
