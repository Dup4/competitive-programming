#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n;
vector <int> G[N];

int fa[N], dep[N], far;
int get_far(int st)
{
	queue <int> q;		
	q.push(st);
	dep[st] = 1;
	fa[st] = -1;
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		far = u;
		for (auto v : G[u]) if (v != fa[u])
		{
			fa[v] = u;
			dep[v] = dep[u] + 1;
			q.push(v);
		}
	}
}

void get_center(int st)
{
	get_far(st);
	get_far(far);
	int shift = dep[far] / 2;
	if (dep[far] % 2 == 0) --shift; 
	while (shift--)
		far = fa[far];
}


int main()
{
	int T; cin >> T;
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			G[i].clear();
		for (int i = 1, u, v; i < n; ++i)
		{
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		get_center(1);
		int center = far;
		for (vector <int> ::iterator it = G[center].begin(); it != G[center].end(); ++it)
			if (*it == fa[center])
			{
				G[center].erase(it);
				break;
			}	
		for (vector <int> :: iterator it = G[fa[center]].begin(); it != G[fa[center]].end(); ++it)
			if (*it == center)
			{
				G[fa[center]].erase(it);
				break;
			}
		int p1, p2, dis;
		get_center(fa[center]);
		p1 = far;
		dis = dep[p1];
		get_center(center);
		p2 = far;
		dis = max(dis, dep[p2]) - 1;
		printf("%d %d %d\n", dis, p1, p2);
	}
	return 0;
}
