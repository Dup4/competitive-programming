#include<iostream>
#include<string>
#include<cmath>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<queue>
#include<stack>
#include<sstream>
#include<cstdio>
#define INF 0x3f3f3f3f
const int maxn = 1e6 + 5;
const double PI = acos(-1.0);
typedef long long ll;
using namespace std;

int d[205];
int w[205][205];
int n, m;
bool vis[205];

int main() {
	//printf("%d",0x3f3f3f3f);
	std::ios::sync_with_stdio(0);
	cin.tie(0);
	int a, b, c;
    int xx,yy;

	while (cin >> n >> m) {
		memset(w, 0x3f, sizeof w);
		memset(d, 0, sizeof d);
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < m; i++) {
			cin >> a >> b >> c;
			w[a][b] = min(w[a][b], c);
			w[b][a] = min(w[b][a], c);
		}
		cin>>xx>>yy;
		if(xx==yy){
			printf("0\n");
			continue;
		}
		for (int i = 0; i < n; i++) i == xx ? d[i] = 0 : d[i] = INF;       //Dijstra
		for (int i = 0; i < n; i++) {
			int x = n, M = INF;
			for (int y = 0; y < n; y++) if (!vis[y] && d[y] < M) {
				x = y;
				M = d[x];
			}
			vis[x] = true;
			for (int y = 0; y < n; y++)   d[y] = min(d[y], d[x] + w[x][y]); 
		}
		if(d[yy] != INF) cout << d[yy] << "\n";  
		else  cout<<-1<<"\n";
	}
	return 0;
}
