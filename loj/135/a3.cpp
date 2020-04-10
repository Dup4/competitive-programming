#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef long long ll;
const int N = 4e5 + 10, M = 2e3 + 100;
int n, m; ll ans[N];

struct BIT_2D {
    struct BIT {
        ll a[M];
		void init() { memset(a, 0, sizeof a); }
        void add(int x, ll v) { for (; x < M; a[x] += v, x += x & -x); }
        ll ask(int x) { ll res = 0; for (; x > 0; res += a[x], x -= x & -x); return res; }
    }bit1, bit2;
	void init() { bit1.init(); bit2.init(); }
    ll ask(int x) { return bit1.ask(x) * (x + 1) - bit2.ask(x); }
    void add(int x, ll v) { bit1.add(x, v); bit2.add(x, x * v); }
    ll ask(int l, int r) { return ask(r) - ask(l - 1); }
    void add(int l, int r, ll v) { add(l, v); add(r + 1, -v); }
}bit[2];

namespace CDQ {	
	struct node {
		int tp, opt, x, y, z1, z2, id, v;
		node() {}
		node(int tp, int opt, int x, int y, int z1, int z2, int id, int v) : tp(tp), opt(opt), x(x), y(y), z1(z1), z2(z2), id(id), v(v) {}
		bool operator < (const node &other) const { return x < other.x; } 
	}t[N], t1[N];
	bool cmp1(const node &a, const node &b) {
		if (a.y == b.y)
			return a.x < b.x;
		return a.y < b.y;
	}
	int tot, tot1;
	void init() { tot = 0; }
	void addQuery(int tp, int opt, int x, int y, int z1, int z2, int id) { t[++tot] = node(tp, opt, x, y, z1, z2, id, 0); }
	void addModify(int tp, int opt, int x, int y, int z1, int z2, int v) { t[++tot] = node(tp, opt, x, y, z1, z2, 0, v); }
	void calc() {
		for (int i = 1; i <= tot1; ++i) {
			if (t1[i].tp == 0) {
				bit[0].add(t1[i].z1, t1[i].z2, -1ll * (t1[i].y - 1) * t1[i].v * t1[i].opt);
				bit[1].add(t1[i].z1, t1[i].z2, t1[i].v * t1[i].opt);
			} else {
				ans[t1[i].id] += 1ll * t1[i].opt * (bit[0].ask(t1[i].z1, t1[i].z2) + 1ll * t1[i].y * bit[1].ask(t1[i].z1, t1[i].z2));
			}
		}
		for (int i = 1; i <= tot1; ++i) {
			if (t1[i].tp == 0) {
				bit[0].add(t1[i].z1, t1[i].z2, -1ll * (t1[i].y - 1) * t1[i].v * t1[i].opt * -1);
				bit[1].add(t1[i].z1, t1[i].z2, t1[i].v * t1[i].opt * -1);
			}
		}
	}
	void solve(int l, int r) {
		if (l == r) return;
		int mid = (l + r) >> 1;
		solve(l, mid); solve(mid + 1, r);
		tot1 = 0;
		for (int i = l; i <= mid; ++i) {
			if (t[i].tp == 0)
				t1[++tot1] = t[i];
		}
		for (int i = mid + 1; i <= r; ++i) {
			if (t[i].tp == 1)
				t1[++tot1] = t[i];
		}
		sort(t1 + 1, t1 + 1 + tot1, cmp1);
		calc();
	}
	void gao() {
		memset(ans, 0, sizeof (ans[0]) * (tot + 5));
		bit[0].init();
		bit[1].init();
		solve(1, tot);
	}
}


int main() {
	scanf("%d%d", &n, &m);
	int op, x[2], y[2], v;
	CDQ::init();
	int q = 0, _q = 0;
	while (scanf("%d", &op) != EOF) {
		++q;
		scanf("%d%d%d%d", x, y, x + 1, y + 1);
		if (op == 1) {
			scanf("%d", &v);
			CDQ::addModify(0, 1, q, x[0], y[0], y[1], v);	
			CDQ::addModify(0, -1, q, x[1] + 1, y[0], y[1], v);
		} else {
			++_q;
			CDQ::addQuery(1, -1, q, x[0] - 1, y[0], y[1], _q);
			CDQ::addQuery(1, 1, q, x[1], y[0], y[1], _q);
		}
	}
	CDQ::gao();
	for (int i = 1; i <= _q; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
