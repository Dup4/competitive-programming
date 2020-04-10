#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n;
vector <vector<int>> G;
/*
	ZOJ 3820
	在一棵树上放置两点，定义其他点的权值为到这两点的距离的小的那个
	问选择哪两点，使得最大的其他点的权值最小

	考虑只放一个点的情况，那么显然是直径上的中点
	再考虑放两个点，那肯定以直径中点为界将树分成两半，一边放一个
	那么各自取各自直径的中点即可
*/

namespace DiameterTree {
	//获得直径，先以任意点为根，找出离它最远的点
	//再以最远的点为根，找出离它最远的点，这两个点就是直径的两个端点	
	int fa[N], dep[N], far;
	void get_far(int st) {
		queue <int> q;		
		q.push(st);
		dep[st] = 1;
		fa[st] = -1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			far = u;
			for (auto v : G[u]) {
				if (v == fa[u]) continue;
				fa[v] = u;
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
	}
	//找直径的中点，直接从下端点往上找父亲找len / 2次就好了 
	int get_center(int st) {
		get_far(st);
		get_far(far);
		int shift = dep[far] / 2;
		if (dep[far] % 2 == 0) --shift; 
		while (shift--)
			far = fa[far];
		return far;
	}
};

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		int center = DiameterTree::get_center(1);
		for (vector <int>::iterator it = G[center].begin(); it != G[center].end(); ++it)
			if (*it == DiameterTree::fa[center]) {
				G[center].erase(it);
				break;
			}	
		for (vector <int>::iterator it = G[DiameterTree::fa[center]].begin(); it != G[DiameterTree::fa[center]].end(); ++it)
			if (*it == center) {
				G[DiameterTree::fa[center]].erase(it);
				break;
			}
		int p1, p2, dis;
		p1 = DiameterTree::get_center(DiameterTree::fa[center]);
		dis = DiameterTree::dep[p1];
		p2 = DiameterTree::get_center(center);
		dis = max(dis, DiameterTree::dep[p2]) - 1;
		printf("%d %d %d\n", dis, p1, p2);
	}
	return 0;
}
