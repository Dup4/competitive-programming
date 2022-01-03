#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, m, seed, vmax, a[N]; 

int rnd() {
	int ret = seed;
	seed = (1ll * seed * 7 + 13) % mod;
	return ret;
}

ll qpow(ll base, ll n, ll mod) {
	base %= mod;
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

struct ODT {
	struct node {
		int l, r;
		mutable ll v;
		node(int l, int r = -1, ll v = 0) : l(l), r(r), v(v) {}
		bool operator < (const node& other) const {
			return l < other.l; 
		}
	};
	using IT = set<node>::iterator;
	set <node> se;
	void init() { se.clear(); }
	IT split(int pos) {
		IT it = se.lower_bound(node(pos));
		if (it != se.end() && it->l == pos) 
			return it;
		--it;
		int l = it->l, r = it->r; ll v = it->v;
		se.erase(it);
		se.insert(node(l, pos - 1, v));
		return se.insert(node(pos, r, v)).first;
	}
	void assign(int l, int r, ll v) {
		IT itr = split(r + 1), itl = split(l);
		se.erase(itl, itr);
		se.insert(node(l, r, v));
	}
	void add(int l, int r, ll v) {
		IT itr = split(r + 1), itl = split(l);
		for (; itl != itr; ++itl) {
			itl->v += v;
		}
	}
	ll kth(int l, int r, int k) {
		vector<pair<ll, int>> vec;
		IT itr = split(r + 1), itl = split(l);
		for (; itl != itr; ++itl) {
			vec.push_back(pair<ll, int>(itl->v, itl->r - itl->l + 1));
		}
		sort(vec.begin(), vec.end());
		for (auto &it : vec) {
			k -= it.second;
			if (k <= 0)
				return it.first;
		}
	}
	ll sum(int l, int r, int ex, int mod) {
		IT itr = split(r + 1), itl = split(l);
		ll res = 0;
		for (; itl != itr; ++itl) {
			res = (res + 1ll * (itl->r - itl->l + 1) * qpow(itl->v, ex, mod) % mod) % mod;
		}
		return res;
	}
}odt;

int main() {
	while (scanf("%d%d%d%d", &n, &m, &seed, &vmax) != EOF) {
		odt.init();
		for (int i = 1; i <= n; ++i) {
			a[i] = (rnd() % vmax) + 1;
			odt.se.insert(ODT::node(i, i, a[i]));
		}
		odt.se.insert(ODT::node(n + 1, n + 1, 0));
		int op, l, r, x, y;
		for (int i = 1; i <= m; ++i) {
			op = (rnd() % 4) + 1;
			l = (rnd() % n) + 1;
			r = (rnd() % n) + 1;
			if (l > r) swap(l, r);
			if (op == 3) {
				x = (rnd() % (r - l + 1)) + 1;
			} else {
				x = (rnd() % vmax) + 1;
			}
			if (op == 4) {
				y = (rnd() % vmax) + 1;
			}
			if (op == 1) {
				odt.add(l, r, x);
			} else if (op == 2) {
				odt.assign(l, r, x);
			} else if (op == 3) {
				printf("%lld\n", odt.kth(l, r, x));
			} else {
				printf("%lld\n", odt.sum(l, r, x, y));
			}
		}
	}
	return 0;
}
