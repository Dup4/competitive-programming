#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
#define SZ(x) (int(x.size()))
const int N = 110; 
int n, m, w[N];
int best, Val; 
int x[N], path[N];
int num[N], val[N];
int g[N][N];

//点的标号[0, n - 1]
void dfs(int *adj, int total, int cnt, int cost) { // total: 与u相连的顶点数量, cnt表示当前团的大小
    int i, j, k;
    int t[N];
    if (total == 0) { 
		if (best < cnt || (best == cnt && cost < Val)) {
			for (i = 0; i < cnt; i++) path[i] = x[i]; 
            best = cnt; 
			Val = cost;
		}
    }    
    for (i = 0; i < total; i++) { 
        if (cnt + num[adj[i]] < best || (cnt + num[adj[i]] == best && cost + val[adj[i]] >= Val)) return;
        x[cnt] = adj[i];  
        for (k = 0, j = i + 1; j < total; j++) { 
            if (g[adj[i]][adj[j]]) {
                t[k++] = adj[j];
			}
		}
		dfs(t, k, cnt + 1, cost + w[adj[i]]);
    } 
} 

int MaximumClique(){
    int i, j, k;
    int adj[N];
    best = 0; Val = 1e9;
    for (i = n - 1; i >= 0; i--) {
        //保存方案
		x[0] = i; 
        for(k = 0, j = i + 1; j < n; j++)    // 遍历[i + 1, n]间顶点，  
            if (g[i][j]) adj[k++] = j;
        dfs(adj, k, 1, w[i]); // *adj, total, cnt
        num[i] = best;  
		val[i] = Val;
    }    
    return best;
}

map <int, int> id, fid;
int cntID;

int getID(int d) {
	if (id.count(d)) return id[d];
	id[d] = cntID;
	fid[cntID] = d;
	++cntID;
	return cntID - 1;
}

int main() {
	scanf("%d%d", &m, &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			g[i][j] = 1;
		}
		g[i][i] = 0;
	}
	cntID = 0;
	vector <pII> edge;
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		edge.push_back(pII(u, v));
	}
	for (int i = 1, u, _w; i <= n; ++i) {
		scanf("%d%d", &u, &_w);
		u = getID(u);
		w[u] = _w;
	}
	for (auto &it : edge) {
		int u = getID(it.fi), v = getID(it.se);
		if (u >= n || v >= n) continue;
		g[u][v] = g[v][u] = 0;
	}
	MaximumClique();
	vector <string> vec;
	for (int i = 0; i < best; ++i) {
		string s = "";
		int x = fid[path[i]];
		while (x) {
			s.push_back(x % 10 + '0');
			x /= 10;
		}
		while (SZ(s) < 3) s.push_back('0');
		reverse(s.begin(), s.end());
		vec.push_back(s);
	}
	sort(vec.begin(), vec.end());
	cout << best << "\n";
	for (int i = 0; i < best; ++i)
		cout << vec[i] << " \n"[i == best - 1];
	cout << Val << endl;
	return 0;
}
