#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n;
vector <int> G[N];

void BFS()
{
	
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
			
	}
	return 0;
}
