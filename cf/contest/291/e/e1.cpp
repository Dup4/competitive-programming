#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
using namespace std;
typedef long long ll;
constexpr int N = 3e5 + 10; 
int n, fa[N]; string s[N], t; ll res;
vector <vector<int>> G;

struct KMP {
	int Next[N], nx[N][27], len;
	void get_Next(string &s) {
		len = SZ(s);
		int i, j;
		j = Next[0] = -1;
		i = 0;
		while (i < len) {
			while (-1 != j && s[i] != s[j]) j = Next[j];
			Next[++i] = ++j;
		}
		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < 26; ++j) {
				nx[i][j] = i;
				if (nx[i][j] != -1 && s[nx[i][j]] != 'a' + j) {
					nx[i][j] = Next[nx[i][j]];
					if (nx[i][j] != -1 && s[nx[i][j]] != 'a' + j) 
						nx[i][j] = nx[nx[i][j]][j];
				}
			}
		}
	}
	int Match(int &pos, string &s) {
		int cnt = 0;
		for (int i = 0; i < SZ(s); ++i) {
			int ch = s[i] - 'a';
			if (pos != -1) pos = nx[pos][ch];
			++pos;
			if (pos == len) {
				++cnt;
				pos = Next[pos];
			}
		}
		return cnt;
	}
}kmp;

void dfs(int u, int kmpPos) {
	for (auto &v : G[u]) {
		int pos = kmpPos;
		res += kmp.Match(pos, s[v]);
		dfs(v, pos);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n;
	G.clear(); G.resize(n + 1);
	for (int i = 2; i <= n; ++i) {
		cin >> fa[i] >> s[i];
		G[fa[i]].push_back(i);
	}	
	cin >> t;
	kmp.get_Next(t);
	res = 0;
	dfs(1, 0);
	cout << res << "\n";
	return 0;
}
