#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
#define SZ(x) (int(x.size()))
const int N = 1e4 + 10; 

set <string> se;
int n, m;
struct E {
	string name;
	int u, v, w;	
	bool operator < (const E &other) const {
		if (w == other.w)
			return se.find(name) == se.end();
		return w > other.w;
	}
}e[N];

struct UFS {
	int fa[N];
	void init() { memset(fa, 0, sizeof fa); }
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x != y) return fa[x] = y, true;
		return false;
	}
}ufs;

void out(pII it, vector <E> &vec) {
	cout << it.fi << " " << it.se << endl;
	for (auto &it : vec) {
		cout << it.u << " " << it.v << " " << it.name << " " << it.w << "\n"; 
	}
}

void gao() {
	vector <E> vec;
	ufs.init();
	int tot = 0;
	priority_queue <E> pq;
	for (int i = 1; i <= m; ++i) pq.push(e[i]);	
	while (!pq.empty()) {
		E e = pq.top();
		pq.pop();
		if (ufs.merge(e.u, e.v)) {
			tot += e.w;
			vec.push_back(e);
			se.insert(e.name);
		}
	}
	sort(vec.begin(), vec.end(), [&](E x, E y) {
		if (x.name != y.name)
			return x.name < y.name;
		return x.w < y.w;
	});
	out(pII(SZ(se), tot), vec);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> e[i].u >> e[i].v >> e[i].name >> e[i].w;
	}
	gao();
	return 0;
}
