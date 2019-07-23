#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define pii pair <int, int>
#define fi first
#define se second
int n, m;
int P[4][2];
vector <vector<pii>> G;
map <string, int> mp; int cnt;
int get(string s) {
	if (mp.find(s) == mp.end()) {
		return mp[s] = ++cnt;
	}
	return mp[s]; 
}

struct SteinerTree {
	int st[32], dp[32][1 << 8], endSt;
	bool vis[32][1 << 8];
	queue <int> que;	
	void init(int n, vector <int> &vec) {
		sort(vec.begin(), vec.end());
		vec.erase(unique(vec.begin(), vec.end()), vec.end());
		memset(dp, -1, sizeof dp);
		memset(vis, 0, sizeof vis);
		memset(st, 0, sizeof st);
		endSt = 1;
		for (auto it : vec) {
			st[it] = endSt;
			endSt <<= 1;
		}
		for (int i = 1; i <= n; ++i) {
			dp[i][st[i]] = 0;
		}
	}
	void update(int &a, int x) {
		a = (a > x || a == -1) ? x : a;
	}
	void SPFA(int state) {
		while (!que.empty()) {
			int u = que.front(); que.pop();
			vis[u][state] = false;
			for (auto it : G[u]) {
				int v = it.fi, w = it.se, y = st[v] | state;
				if (dp[v][y] == -1 || dp[v][y] > dp[u][state] + w) {
					dp[v][y] = dp[u][state] + w;
					if (y != state || vis[v][state]) 
						continue;
					vis[v][state] = true;
					que.push(v);
				}
			}
		}
	}
	int solve() {
		for (int j = 1; j < endSt; ++j) {
			for (int i = 1; i <= n; ++i) {
				if (st[i] && (st[i] & j) == 0) continue;
				for (int sub = (j - 1) & j; sub; sub = (sub - 1) & j) {
					int x = st[i] | sub, y = st[i] | (j - sub);
					if (dp[i][x] != -1 && dp[i][y] != -1) {
						update(dp[i][j], dp[i][x] + dp[i][y]);
					}
				}
				if (dp[i][j] != -1) {
					que.push(i), vis[i][j] = true;
				}
			}
			SPFA(j);
		}
		int res = 1e9;
		for (int i = 1; i <= n; ++i) if (dp[i][endSt - 1] != -1) {
			res = min(res, dp[i][endSt - 1]);
		}
		return res;
	}
}ST;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n >> m) {
		cnt = 0; mp.clear();
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			string s; cin >> s;
			get(s);
		}
		for (int i = 1, u, v, w; i <= m; ++i) {
			string s;
			cin >> s; u = get(s);
			cin >> s; v = get(s);
			cin >> w;
			G[u].push_back(pii(v, w));
			G[v].push_back(pii(u, w));
		}
		vector <int> vec;
		for (int i = 0; i < 4; ++i) {
			string s;
			cin >> s; P[i][0] = get(s);
			cin >> s; P[i][1] = get(s); 
		}
		ll res = 1e9, tmp;
		//1 + 1 + 1 + 1
		tmp = 0;
		for (int i = 0; i < 4; ++i) {
			vec.clear();
			vec.push_back(P[i][0]);
			vec.push_back(P[i][1]);
			ST.init(n, vec); tmp += ST.solve(); 
		}
		res = min(res, tmp);
		
		// 3 + 1
		for (int i = 0; i < 4; ++i) {
			tmp = 0;
			vec.clear();
			vec.push_back(P[i][0]);
			vec.push_back(P[i][1]);
			ST.init(n, vec); tmp += ST.solve();
			vec.clear();
		   	for (int j = 0; j < 4; ++j)	{
				if (i == j) continue;
				vec.push_back(P[j][0]);
				vec.push_back(P[j][1]);
				ST.init(n, vec); tmp += ST.solve(); 
			}
			res = min(res, tmp);
		}

		// 2 + 2
		for (int i = 0; i < 4; ++i) {
			for (int j = i + 1; j < 4; ++j) {
				tmp = 0;
				vec.clear();
				vec.push_back(P[i][0]);
				vec.push_back(P[i][1]);
				vec.push_back(P[j][0]);
				vec.push_back(P[j][1]);
				for (int k = 0; k < 4; ++k) if (k != i && k != j) {
					vec.push_back(P[k][0]);
					vec.push_back(P[k][1]);
				}
				ST.init(n, vec);
				tmp += ST.solve();
				res = min(res, tmp);
			}
		}

		vec.clear();
		for (int i = 0; i < 4; ++i) {
			vec.push_back(P[i][0]);
			vec.push_back(P[j][0]);
		}
		

		cout << ST.solve() << "\n";
	}
	return 0;
}

