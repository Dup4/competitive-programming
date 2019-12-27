#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 2e5 + 10;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m; int h[N];
vector <vector<pII>> vecl, vecr;
struct SEG {
	struct node {
		ll Min, lazy;
		node() {
			Min = 0;
			lazy = 0;
		}
		void up(ll x) {
			Min += x;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.Min = min(Min, other.Min);
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node(); 
		if (l == r) {
			t[id].Min = h[l];
			return;	
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void down(int id) {
		ll &lazy = t[id].lazy;
		if (lazy) {
			t[id << 1].up(lazy);
			t[id << 1 | 1].up(lazy);
			lazy = 0;
		}
	}
	void update(int id, int l, int r, int ql, int qr, ll v) {
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		down(id);
		int mid = (l + r) >> 1;
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1]; 
	}
}seg;

int main() {
	scanf("%d%d", &n, &m);	
	for (int i = 1; i <= n; ++i) {
		scanf("%d", h + i);		
	}
	vecl.clear(); vecl.resize(n + 1);
	vecr.clear(); vecr.resize(n + 1);
	for (int i = 1, l, r, w; i <= m; ++i) {
		scanf("%d%d%d", &l, &r, &w);
		vecl[l].push_back(pII(r, w));
		vecr[r].push_back(pII(l, w));
	}
	seg.build(1, 1, n);
	ll res = 0;
	for (int i = 1; i <= n; ++i) { 
		res = max(res, 1ll * h[i] - seg.t[1].Min); 
		for (auto &it : vecr[i]) {
			seg.update(1, 1, n, it.fi, i, -it.se);
		}
	}
	seg.build(1, 1, n);
	for (int i = n; i >= 1; --i) { 
		res = max(res, 1ll * h[i] - seg.t[1].Min);
		for (auto &it : vecl[i]) { 
			seg.update(1, 1, n, i, it.fi, -it.se); 
		}
	}
	printf("%lld\n", res); 
	return 0;
}
