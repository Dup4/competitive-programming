#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int n, q, k, a[N], t[N], pre[N];
vector <int> buc;

namespace Mo {
	int blo[N], ce, S;
	ll ans[N];
	struct E {
		int l, r, id;
		ll ans;
		bool operator < (const E &other) const {
			if (blo[l] == blo[other.l]) {
				return r < other.r;
			}
			return l < other.l;
		}
	}e[N];
	vector <vector<tuple<int, int, int>>> vec;
	void init(int n) {
		vec.clear(); vec.resize(n + 1);
		ce = 0; S = sqrt(n);
		for (int i = 1; i <= n; ++i) {
			blo[i] = (i - 1) / S + 1;
		}
	} 
	void addquery(int l, int r, int id) {
		e[++ce] = {l, r, id, 0};
	}
	void gao() {
		memset(t, 0, sizeof t);
		for (int i = 1; i <= n; ++i) {
			for (auto &x : buc) ++t[a[i] ^ x];
			pre[i] = t[a[i + 1]];
		}
		sort(e + 1, e + 1 + ce);
		//L右移：l正r负
     	//l左移：l负r正
     	//r右移：r正l负
     	//r左移：r负l正
		//预处理前缀贡献
		for (int i = 1, l = 1, r = 0; i <= ce; ++i) {
			int ql = e[i].l, qr = e[i].r;
			if (l < ql) vec[r].emplace_back(l, ql - 1, -i);
			while (l < ql) { e[i].ans += pre[l - 1]; ++l; }
			if (l > ql) vec[r].emplace_back(ql, l - 1, i);
			while (l > ql) { e[i].ans -= pre[l - 2]; --l; }
			if (r < qr) { vec[l - 1].emplace_back(r + 1, qr, -i); }
			while (r < qr) { e[i].ans += pre[r]; ++r; }
			if (r > qr) vec[l - 1].emplace_back(qr + 1, r, i);
			while (r > qr) { e[i].ans -= pre[r - 1]; --r; }
		}
		memset(t, 0, sizeof t);
		//模拟莫队，算出第一类贡献，对第二类贡献打标记
		for (int i = 1, id, ql, qr; i <= n; ++i) {
			for (auto &x : buc) ++t[a[i] ^ x];	
			for (auto &it : vec[i]) {
				tie(ql, qr, id) = it;
				for (int j = ql, tmp = 0; j <= qr; ++j) {
					tmp = t[a[j]];
					//k == 0的时候需要特判，因为x ^ x = 0，但是不产生贡献
					if (j <= i && k == 0) --tmp; 
					if (id < 0) e[-id].ans -= tmp;
					else e[id].ans += tmp;
				}
			}
		}
		for (int i = 1; i <= ce; ++i) {
			e[i].ans += e[i - 1].ans;
			ans[e[i].id] = e[i].ans;
		}
		for (int i = 1; i <= ce; ++i) {
			printf("%lld\n", ans[i]);
		}
	}
};

int main() {
	while (scanf("%d%d%d", &n, &q, &k) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		Mo::init(n);
		for (int i = 1, l, r; i <= q; ++i) {
			scanf("%d%d", &l, &r);
			Mo::addquery(l, r, i);
		}
		if (k > 14) {
			for (int i = 1; i <= q; ++i) 
				puts("0");
			continue;
		}
		buc.clear();
		for (int i = 0; i < (1 << 14); ++i) {
			if (__builtin_popcount(i) == k) {
				buc.push_back(i);
			}
		}
		Mo::gao();
	}
	return 0;
}
