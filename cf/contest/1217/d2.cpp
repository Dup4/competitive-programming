#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define endl "\n"
using pII = pair <int, int>;
constexpr int N = 5e3 + 10; 
int n, m, c[N], in[N], vis[N], Insta[N]; 
vector <vector<pII>> G;
//Topo判断有没有环
bool loop() {
	queue <int> q;
	for (int i = 1; i <= n; ++i) if (!in[i]) q.push(i);
	int cnt = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		++cnt;
		for (auto &it: G[u]) if (--in[it.fi] == 0) q.push(it.fi);
	}	
	return cnt < n;
}
//DFS找环
void DFS(int u) {
	vis[u] = 1;
	Insta[u] = 1;
	for (auto &it: G[u]) {
		int v = it.fi, id = it.se;
		if (Insta[v]) {
			c[id] = 2;
			continue;
		} 
		if (!vis[v]) DFS(v);
	}
	Insta[u] = 0;
}

void run() {
	G.clear(); G.resize(n + 1);
	memset(in, 0, sizeof in);
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v;
		G[u].push_back(pII(v, i));
		++in[v];
	}
	if (!loop()) {
		cout << 1 << endl;
		for (int i = 1; i <= m; ++i)
			cout << 1 << " \n"[i == m];
	} else {
		memset(vis, 0, sizeof vis);
		memset(Insta, 0, sizeof Insta);
		cout << 2 << endl;
		for (int i = 1; i <= m; ++i) c[i] = 1;
		for (int i = 1; i <= n; ++i) if (!vis[i]) DFS(i);
		for (int i = 1; i <= m; ++i)
			cout << c[i] << " \n"[i == m];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
	return 0;
}
