#include <bits/stdc++.h>
using namespace std;

#define N 30
#define pii pair <int, int>
#define fi first
#define se second
int G[N][N];
int used[N][N];
int n, m;
vector <pii> vec;
bool flag;

void DFS(int x, int y, int cur)
{
	if (cur == n * m)
	{
		flag = 1;
		return;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) if (!used[i][j] && i != x && j != y && i - j != x - y && i + j != x + y)
		{
			vec.emplace_back(i, j);
			used[i][j] = 1;
			DFS(i, j, cur + 1);
			if (flag) return;
			used[i][j] = 0;
			vec.pop_back();
		}
}

int main()
{
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase)
	{
		printf("Case #%d: ", kase);
		vec.clear(); flag = 0;
		memset(used, 0, sizeof used);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
			{
				vec.emplace_back(i, j);
				used[i][j] = 1;
				DFS(i, j, 1);
				if (flag) goto a;
				used[i][j] = 0;
				vec.pop_back();
			}
		a:
		if (!flag) puts("IMPOSSIBLE");
		else
		{
			puts("POSSIBLE");
			for (auto it : vec)
				printf("%d %d\n", it.fi, it.se);
		}
	}
	return 0;
}
