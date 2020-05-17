#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
#define SZ(x) (int(x.size()))
const int N = 1e4 + 10;
int n, m;
struct E {
	string name;
	int u, v, w;	
	bool operator < (const E &other) const {
		if (w == other.w)
			return name < other.name;
		return w < other.w;
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


pII gao(vector <E> &vec) {
	vec.clear();
	ufs.init();
	int tot = 0;
	set <string> se;
	for (int i = 1; i <= m; ++i) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (ufs.merge(u, v)) {
			tot += w;
			vec.push_back(e[i]);
			se.insert(e[i].name);
		}
	}
	sort(vec.begin(), vec.end(), [&](E x, E y) {
		if (x.name != y.name)
			return x.name < y.name;
		return x.w < y.w;
	});
	return pII(SZ(se), tot);
}

void out(pII it, vector <E> &vec) {
	cout << it.fi << " " << it.se << endl;
	for (auto &it : vec) {
		cout << it.u << " " << it.v << " " << it.name << " " << it.w << "\n"; 
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> e[i].u >> e[i].v >> e[i].name >> e[i].w;
	}
	vector <E> A, B;
	sort(e + 1, e + 1 + m, [&](E x, E y){
		return x.w < y.w;			
	});
	pII _A = gao(A);
	sort(e + 1, e + 1 + m, [&](E x, E y) {
		if (x.w == y.w)
			return x.name < y.name;
		return x.w < y.w;		
	});
	pII _B = gao(B);
	if (_A.fi < _B.fi) out(_A, A);
	else out(_B, B);
	return 0;
}
