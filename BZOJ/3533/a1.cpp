#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef long long db;
typedef long long ll;
const db INF = 1e18;
const db eps = 1e-10;
const db PI = acos(-1.0); 
int sgn(db x) { if (x == 0) return 0; return x < 0 ? -1 : 1; }
const int N = 4e5 + 10;

bool __slp__x__;
template <typename T>
struct HULL {
	static const T INF = 1e18;
	struct node {
		T slp, x, y;
		node(T _slp = 0, T _x = 0, T _y = 0) : slp(_slp), x(_x), y(_y) {}
		bool operator < (const node &other) const { return __slp__x__ ? slp > other.slp : x < other.x; }
		T operator - (const node &other) const { return (y - other.y) / (x - other.x); }
	};
	set <node> Q;
	void init() { Q.clear(); }
	void ins(T x, T y) {
		__slp__x__ = 0;
		node t(0, x, y);
		typename set<node>::iterator it = Q.lower_bound(node(0, x, 0));
		if (it != Q.end()) {
			if ((it->x == x && it->y >= y) || (it->x != x && it->slp <= *it - t)) return;
			if (it->x == x) Q.erase(it);
		}
		it = Q.insert(t).first;
		typename set<node>::iterator it3 = it; it3--;
		while (it != Q.begin()) {
			typename set<node>::iterator it2 = it3;
			if (it2 != Q.begin() && t - *it2 >= *it2 - *--it3) Q.erase(it2);
			else break;
		}
		it3 = it; it3++;
		while (it3 != Q.end()) {
			typename set<node>::iterator it2 = it3;
			if (++it3 != Q.end() && *it2 - *it3 >= *it2 - t) Q.erase(it2);
			else break;
		}
		if (it == Q.begin()) const_cast<T&>(it->slp) = INF;
		else {
			typename set<node>::iterator it2 = it; it2--;
			const_cast<T&>(it->slp) = t - *it2;	
		}
		typename set <node>::iterator it2 = it; it2++;
		if (it2 != Q.end()) const_cast<T&>(it2->slp) = t - *it2;
	}
	T get(T a, T b) {
		//max(ax + by)
		if (Q.empty()) return -INF;
		__slp__x__ = 1;
		typename set<node>::iterator it = Q.lower_bound(node(-a / b, 0, 0));
		if (it != Q.begin()) it--;
		return it->x * a + it->y * b;
	}
};


struct SEG {
	HULL <db> upHull[N << 2], downHull[N << 2]; 
	void build(int id, int l, int r) {
		upHull[id].init();
		downHull[id].init();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void ins(int id, int l, int r, int pos, db x, db y) {
		upHull[id].ins(x, y);
		downHull[id].ins(x, -y);
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (pos <= mid) ins(id << 1, l, mid, pos, x, y);
		else ins(id << 1 | 1, mid + 1, r, pos, x, y);
	}	
	db query(int id, int l, int r, int ql, int qr, db x, db y) {
		if (l >= ql && r <= qr) {
			if (y > 0) return upHull[id].get(x, y);
			else return downHull[id].get(x, -y);
		}
		int mid = (l + r) >> 1;
		db Max = -INF;
		if (ql <= mid) Max = max(Max, query(id << 1, l, mid, ql, qr, x, y));
		if (qr > mid) Max = max(Max, query(id << 1 | 1, mid + 1, r, ql, qr, x, y));
		return Max;
	}
}seg;

int main() {
	ll lst = 0;
	int n = 0; 
	int q; char dataTp[10]; 
	scanf("%d%s", &q, dataTp);
	seg.build(1, 1, q);
	for (int i = 1; i <= q; ++i) {
		char op[5]; int l, r; ll x, y;
		scanf("%s", op);
		scanf("%lld%lld", &x, &y);
		x ^= lst; y ^= lst;
		if (op[0] == 'A') {
			++n;
			seg.ins(1, 1, q, n, x, y);
		} else {
			scanf("%d%d", &l, &r);
			l ^= lst; r ^= lst;
			lst = seg.query(1, 1, q, l, r, x, y);
			printf("%lld\n", lst);
			if (dataTp[0] == 'E') lst = 0;
			lst &= 0x7fffffff;
		}
	}
	return 0;
}
