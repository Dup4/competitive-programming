#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define SZ(x) (int((x).size()))
const int N = 110;
int n, m, l, tot, a[N], vis[N], f[2][N]; 

//f[0][i] i human num of liers
//f[1][i] i warewolf num of liers

vector <int> vec, res;

void dfs(int cur, int cost, int fcost) {
//	dbg(cur, cost, fcost);
	if (cost > l) return;
	if (SZ(vec) == m) {
		if (cost + tot - fcost == l) {
			int cnt = 0;
			for (int _ = 0; _ < m; ++_) {
				int i = vec[_];
				if (a[i] < 0 && vis[-a[i]] == 0) ++cnt;
				if (a[i] > 0 && vis[a[i]]) ++cnt;
			}
			if (cnt == 0 || cnt == m) return;
			for (int i = 0; i < m; ++i) {
				printf("%d%c", vec[i], " \n"[i == m - 1]);
			}
			exit(0);
		}
		return;
	}
	if (cur <= 0) return;
	vis[cur] = 1;
	vec.push_back(cur);
	dfs(cur - 1, cost + f[1][cur], fcost + f[0][cur]);
	vec.pop_back();
	vis[cur] = 0;
	dfs(cur - 1, cost, fcost);
}

int main() {
	scanf("%d%d%d", &n, &m, &l);
	memset(f, 0, sizeof f);
	tot = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		if (a[i] < 0) ++f[0][-a[i]];
		else ++f[1][a[i]];
	}
	for (int i = 1; i <= n; ++i) {
		tot += f[0][i];
	}
	dfs(n, 0, 0);
	if (res.empty()) puts("No Solution");
	else {
		for (int i = 0; i < m; ++i)
			printf("%d%c", res[i], " \n"[i == m - 1]);
	}
	return 0;
}
