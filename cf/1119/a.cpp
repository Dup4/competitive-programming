#include <bits/stdc++.h>
using namespace std;

#define N 300010
int n, c[N];
vector <int> G[N];

int main()
{
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 1; i <= n; ++i)
			G[i].clear();
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", c + i);
			G[c[i]].push_back(i);
		}
		int res = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (G[i].empty()) continue;
			int j = *G[i].begin();
			int len = G[i].size();
			int last = n;
			for (int k = len - 1; k >= 0; --k, --last)
			{
				if (G[i][k] != last)
					break;
			}
			res = max(res, last - j);
			j = *G[i].rbegin();
			last = 1;
			for (int k = 0; k < len; ++k, ++last)
			{
				if (G[i][k] != last)
					break;
			}
			res = max(res, j - last);
		}
		printf("%d\n", res);
	}
	return 0;
}
