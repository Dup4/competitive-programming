#include <bits/stdc++.h>
using namespace std;
/*
	ZOJ 3820
	在一棵树上放置两点，定义其他点的权值为到这两点的距离的小的那个
	问选择哪两点，使得最大的其他点的权值最小

	考虑只放一个点的情况，那么显然是直径上的中点
	再考虑放两个点，那肯定以直径中点为界将树分成两半，一边放一个
	那么各自取各自直径的重点即可
*/

#define N 200010
int n;
vector <int> G[N];

/*
	获得直径，先以任意点为根，找出离它最远的点
    再以最远的点为根，找出离它最远的点，这两个点就是直径的两个端点	
*/
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
/*
	找直径的中点，直接从下端点往上找父亲找len/2次就好了 
*/
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
