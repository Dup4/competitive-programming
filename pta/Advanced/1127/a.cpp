#include <bits/stdc++.h>
using namespace std;
const int N = 1100;
int n, rt, a[N], b[N], c[N], deep[N];
vector <vector<int>> vec;
struct E {
	int son[2];
	E() { son[0] = son[1] = 0; }
}e[N];
int gao(int al, int ar, int bl, int br) {
	if (al > ar || bl > br) return 0;
	int rt = a[ar], pos = -1; 
	for (int i = bl; i <= br; ++i) {
		if (b[i] == rt) {
			pos = i;
			break;
		}
	}
	if (al >= ar) return rt;
	int lsze = pos - bl;
	e[rt].son[0] = gao(al, al + lsze - 1, bl, pos - 1);
	e[rt].son[1] = gao(al + lsze, ar - 1, pos + 1, br);
	return rt;
}

void bfs(int S) {
	queue <int> que;
	que.push(S);
	deep[S] = 1; 
	while (!que.empty()) {
		int u = que.front(); que.pop();
		vec[deep[u]].push_back(c[u]); 
		int v = e[u].son[0];
		if (v) {
			deep[v] = deep[u] + 1;
			que.push(v);
		}
		v = e[u].son[1];
		if (v) {
			deep[v] = deep[u] + 1;
			que.push(v);
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(e, 0, sizeof e);
		memset(deep, 0, sizeof deep); 
		vec.clear(); vec.resize(n + 35);
		for (int i = 1; i <= n; ++i) scanf("%d", b + i), c[i] = b[i];
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		sort(c + 1, c + 1 + n);
		for (int i = 1; i <= n; ++i) {
			a[i] = lower_bound(c + 1, c + 1 + n, a[i]) - c;
			b[i] = lower_bound(c + 1, c + 1 + n, b[i]) - c;
		}
		int rt = gao(1, n, 1, n);
		bfs(rt);
		vector <int> res;
		for (int i = 1; i <= n + 30; ++i) {
			if (vec[i].empty()) break;
			if (i & 1) {
				reverse(vec[i].begin(), vec[i].end());
			}
			for (auto &it : vec[i]) res.push_back(it);
		}
		assert(res.size() == n);
		for (int i = 0; i < n; ++i)
			printf("%d%c", res[i], " \n"[i == n - 1]);
	}
	return 0;
}
