#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
#define SZ(x) (int(x.size()))
const int N = 110;
int n, a[N], b[N], c[N], v[N], cnt[N];
pII t[N];

inline int parseInt(string &s) {
	if (s == "-") return 0;
	int x = 0;
	for (int i = 0; i < SZ(s); ++i) {
		x = x * 10 + (s[i] - '0');
	}
	return x;
}

inline void scan(int &x) {
	string s;
	cin >> s;
	x = parseInt(s);
}

void IMP() { cout << "Impossible\n"; exit(0); } 

bool gao(int &rt, int al, int ar, int bl, int br, int cl, int cr) {
	if (al > ar) {
		rt = 0;
		return true;
	}
	int ok = 0;
	if (b[bl] && c[cr] && b[bl] != c[cr]) return false;
	for (int i = al; i <= ar; ++i) {
		if (a[i] && b[bl] && a[i] != b[bl])	continue;
		if (a[i] && c[cr] && a[i] != c[cr]) continue;
		int num = i - al; 
		if (gao(t[i].fi, al, i - 1, bl + 1, bl + num, cl, cl + num - 1) &&
			gao(t[i].se, i + 1, ar, bl + num + 1, br, cl + num, cr - 1)) {
		//	if (ok) return false; 
			rt = i;
			v[i] = max({a[i], b[bl], c[cr]});
			++ok;
			return true;
		}
	}
	return false;
//	return ok == 1;
}

void print(int rt, int tp, vector<int> &vec) {
	if (!rt) return;
	if (tp == 1) vec.push_back(v[rt]);
	print(t[rt].fi, tp, vec);
	if (tp == 2) vec.push_back(v[rt]);
	print(t[rt].se, tp, vec);
	if (tp == 3) vec.push_back(v[rt]);
}

void bfs(int rt, vector <int> &vec) {
	queue <int> que;
	que.push(rt);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		vec.push_back(v[u]);
		if (t[u].fi) que.push(t[u].fi);
		if (t[u].se) que.push(t[u].se);
	}
}

void out(vector <int> &vec) {
	for (int i = 0; i < SZ(vec); ++i)
		cout << vec[i] << " \n"[i == SZ(vec) - 1];
	vec.clear();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n) { 
		memset(cnt, 0, sizeof cnt);
		memset(v, 0, sizeof v);
		for (int *arr : { a, b, c }) {
			for (int i = 1; i <= n; ++i) {
				scan(arr[i]);
				++cnt[arr[i]];
			}
		}
		int pos = 0;
		for (int i = 1; i <= n; ++i) {
			if (!cnt[i]) {
				if (pos) IMP();
				pos = i;
			}
		}
		int rt = 0;
		if (!gao(rt, 1, n, 1, n, 1, n)) IMP();
		for (int i = 1; i <= n; ++i) {
			if (!v[i]) v[i] = pos;
		}
		vector <int> ans;
		for (int tp : {2, 1, 3}) {
			print(rt, tp, ans);
			out(ans);
		}
		bfs(rt, ans);
		out(ans);	
	}
	return 0;
}
